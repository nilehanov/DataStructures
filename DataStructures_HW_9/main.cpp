#include <cstdlib>
#include "image.h"
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
#include <algorithm>
// ===================================================================================================
// ===================================================================================================

using namespace std;

//helper function: to generate offset structure
void offset_setup(const Image<Color> &input, int offset_s, map< pair<int,int>,vector<pair<int,int> > > &offset_coords)
{
    for (int i = 0; i < input.Width(); i++)
    {
        for (int j = 0; j < input.Height(); j++)
        {
            if(!input.GetPixel(i,j).isWhite())//if there is a non-white pixel push it back into a vector of pairs
            {
                pair<int,int> offset_x_y=make_pair(i%offset_s,j%offset_s);
                pair<int,int> input_x_y=make_pair(i,j);
                
                ( offset_coords[offset_x_y] ).push_back(input_x_y);
            }
        }
    }
}
//helper function: to locate place in hash table
void find_place_in_hash
(const Image<Color> &input, map<pair<int,int>, pair<int,int> > &hash_coords,int &hash_s,int &hash_width,
 int &hash_height,int &offset_s,map< pair<int,int>,vector<pair<int,int> > > &offset_coords,Image<Offset> &offset,int &max_num_of_pairs)
{
    bool no_collision=true;
    map< pair<int,int> , vector<pair<int,int> > >::iterator itr_offset;
    bool can_find_match=true;
    //starting with a square for hash table with possibel expention of one side at a time
    hash_width=hash_s;
    hash_height=hash_s;
    
    bool increment_width=true;
    bool increment_offset=true;
    bool offset_has_changed=false;
    
    bool common_factor=true;
    //find values that dont share common factors
    while(common_factor)
    {
        for(int mod=2;mod<=offset_s;mod++)
        {
            if(offset_s%mod==0 && (hash_width%mod==0 || hash_height%mod==0))
            {
                if(increment_width)
                {
                    hash_width++;
                }
                else
                {
                    hash_height++;
                }
                increment_width = !increment_width;
                break;
            }
            if(mod==offset_s)
            {
                common_factor=false;
            }
        }
    }
    
    int max_original=max_num_of_pairs;
    
    //Search for a perfect hash table until you find one.
    while(hash_width<input.Width() && hash_height<input.Height())
    {
        
        //Assume we can find a match at this hash table size until proven otherwise
        can_find_match=true;
        for(int z=max_num_of_pairs;z>0;z--)
        {
            for(itr_offset=offset_coords.begin();itr_offset!=offset_coords.end();itr_offset++)
            {
                if(itr_offset->second.size()==max_num_of_pairs)
                {
                    //offset increments
                    for(int dx=0;dx<hash_width;dx++)
                    {
                        //offset increments
                        for(int dy=0;dy<hash_height;dy++)
                        {
                            //Assume the current (dx,dy) offsets work until proven otherwise
                            no_collision=true;
                            map<pair<int,int>, pair<int,int> > hash_coords_temp=hash_coords;
                            
                            //number of coord pairs stored in the cell of offset
                            for(int k=0;k<itr_offset->second.size();k++)
                            {
                                pair<int,int> hash_x_y=make_pair( (itr_offset->second[k].first+dx)%hash_width, (itr_offset->second[k].second+dy)%hash_height );
                                if(hash_coords_temp.find(hash_x_y)==hash_coords_temp.end())
                                {
                                    no_collision=true;
                                    hash_coords_temp[hash_x_y]=make_pair(itr_offset->second[k].first,itr_offset->second[k].second);
                                }
                                else
                                {
                                    no_collision=false;
                                    break;
                                }
                            }
                            if(no_collision)
                            {
                                hash_coords=hash_coords_temp;
                                //set unique dx and dy for offset
                                Offset tmp(dx,dy);
                                offset.SetPixel(itr_offset->first.first,itr_offset->first.second,tmp);
                                break;
                            }
                        }
                        if(no_collision)
                            break;
                    }
                    
                    if(!no_collision)
                    {
                        can_find_match=false;
                    }
                    //need to increment hash table size
                    if(!can_find_match)
                    {
                        int mod_limit=min(hash_width,min(hash_height,offset_s));
                        for(int mod=2;mod<=mod_limit;mod++)
                        {
                            if(offset_s%mod==0 && (hash_width%mod==0 || hash_height%mod==0))
                            {
                                if(!increment_offset)
                                {
                                    if(increment_width)
                                    {
                                        hash_width++;
                                        
                                    }
                                    else
                                    {
                                        hash_height++;
                                        
                                    }
                                    increment_width = !increment_width;
                                }
                                else
                                {
                                    offset_s++;
                                    offset_has_changed=true;
                                }
                                increment_offset=!increment_offset;
                                break;
                            }
                        }
                        if(offset_has_changed)
                        {
                            offset_coords.clear();
                            offset_setup(input,offset_s,offset_coords);
                            //find max num of elements
                            map< pair<int,int> , vector<pair<int,int> > >::iterator itr_off;
                            for(itr_off=offset_coords.begin();itr_off!=offset_coords.end();itr_off++)
                            {
                                if(itr_off->second.size() >max_num_of_pairs)
                                {
                                    max_num_of_pairs=itr_off->second.size();
                                }
                                
                            }//end find max num of elements
                            offset_has_changed=false;
                            max_original=max_num_of_pairs;
                        }
                        hash_coords.clear();
                        offset.Allocate(offset_s,offset_s);
                        break;
                    }
                }
            }
            if(!can_find_match)
            {
                max_num_of_pairs=max_original;
                break;
            }
        }
        if(can_find_match)//if found perfect hash placement
            break;
        
    }
}
void Compress(const Image<Color> &input, 
              Image<bool> &occupancy, Image<Color> &hash_data, Image<Offset> &offset)
{
    map< pair<int,int> , vector<pair<int,int> > > offset_coords;
    map<pair<int,int>, pair<int,int> > hash_coords;
    int non_white=0;
    int hash_width;
    int hash_height;
    int max_num_of_pairs=0;
    //count non-white pixels
    for (int i = 0; i < input.Width(); i++)
    {
        for (int j = 0; j < input.Height(); j++)
        {
            if(input.GetPixel(i,j).isWhite())
            {}
            else  non_white++;
        }
    }
    float hash_side=sqrt(1.01*non_white);
    float offset_side=sqrt(non_white/4.);
    //convert to int
    int hash_s=ceil(hash_side);
    int offset_s=ceil(offset_side);
    occupancy.Allocate(input.Width(),input.Height());
    //create occupancy table
    for (int i = 0; i < input.Width(); i++)
    {
        for (int j = 0; j < input.Height(); j++)
        {
            if(!input.GetPixel(i,j).isWhite())
            {
                occupancy.SetPixel(i,j,true);
            }
            else
                occupancy.SetPixel(i,j,false);
        }
    }
    
    //offset setup
    offset_setup(input,offset_s,offset_coords);
    //end offset setup
    
    //find max num of elements
    map< pair<int,int> , vector<pair<int,int> > >::iterator itr_off;
    for(itr_off=offset_coords.begin();itr_off!=offset_coords.end();itr_off++)
    {
        if(itr_off->second.size() >max_num_of_pairs)
        {
            max_num_of_pairs=itr_off->second.size();
        }
        
    }//end find max num of elements
    
    
    //allocate space for offset
    offset.Allocate(offset_s,offset_s);
    //end allocate
    
    //FIND PLACE IN HASH AND SET UNIQUE DX DY
    find_place_in_hash(input,hash_coords,hash_s,hash_width,hash_height, offset_s,offset_coords,offset,max_num_of_pairs);
    //END FIND PLACE IN HASH AND SET UNIQUE DX DY
    
    hash_data.Allocate(hash_width,hash_height);//allocate space for hash
    
    map<pair<int,int>, pair<int,int> >::iterator itr_hash;
    for(int i=0;i<hash_width;i++)//width of hash table
    {
        for(int j=0;j<hash_height;j++)//height of has table
        {
            pair<int,int> hash_x_y=make_pair(i,j);
            if(hash_coords.find(hash_x_y)!=hash_coords.end())
            {
                //set colors in hash
                itr_hash=hash_coords.find(hash_x_y);
                unsigned char r,g,b;
                r=input.GetPixel(itr_hash->second.first,itr_hash->second.second).r;
                g=input.GetPixel(itr_hash->second.first,itr_hash->second.second).g;
                b=input.GetPixel(itr_hash->second.first,itr_hash->second.second).b;
                Color tmp(r,g,b);
                hash_data.SetPixel(i,j,tmp);
            }
            else
            {
                Color tmp;
                hash_data.SetPixel(i,j,tmp);//set to white
            }
        }
    }
}


void UnCompress(const Image<bool> &occupancy, const Image<Color> &hash_data, const Image<Offset> &offset, Image<Color> &output)
{
    unsigned char off_x;
    unsigned char off_y;
    unsigned char hash_x;
    unsigned char hash_y;
    
    output.Allocate(occupancy.Width(),occupancy.Height());
    for(int i=0;i<occupancy.Width();i++)
    {
        for(int j=0;j<occupancy.Height();j++)
        {
            if(occupancy.GetPixel(i,j))//if black
            {
                off_x=i%(offset.Width());
                off_y=j%(offset.Height());
                Offset o=offset.GetPixel(off_x,off_y);
                
                hash_x=(i+o.dx)%hash_data.Width();
                hash_y=(j+o.dy)%hash_data.Height();
                
                Color c=hash_data.GetPixel(hash_x,hash_y);
                
                output.SetPixel(i,j,c);
            }
            else
            {
                Color c;//this is default white
                output.SetPixel(i,j,c);
                
            }
        }
        
    }
    
    
    
}


// ===================================================================================================
// ===================================================================================================

void Compare(const Image<Color> &input1, const Image<Color> &input2, Image<bool> &output) {
    
    // confirm that the files are the same size
    if (input1.Width() != input2.Width() ||
            input1.Height() != input2.Height()) {
        std::cerr << "Error: can't compare images of different dimensions: "
                  << input1.Width() << "x" << input1.Height() << " vs "
                  << input2.Width() << "x" << input2.Height() << std::endl;
    } else {
        
        // confirm that the files are the same size
        output.Allocate(input1.Width(),input1.Height());
        int count = 0;
        for (int i = 0; i < input1.Width(); i++) {
            for (int j = 0; j < input1.Height(); j++) {
                Color c1 = input1.GetPixel(i,j);
                Color c2 = input2.GetPixel(i,j);
                if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
                    output.SetPixel(i,j,true);
                else {
                    count++;
                    output.SetPixel(i,j,false);
                }
            }
        }
        
        // confirm that the files are the same size
        if (count == 0) {
            std::cout << "The images are identical." << std::endl;
        } else {
            std::cout << "The images differ at " << count << " pixel(s)." << std::endl;
        }
    }
}

// ===================================================================================================
// ===================================================================================================


// to allow visualization of the custom offset image format
void ConvertOffsetToColor(const Image<Offset> &input, Image<Color> &output) {
    // prepare the output image to be the same size as the input image
    output.Allocate(input.Width(),input.Height());
    for (int i = 0; i < output.Width(); i++) {
        for (int j = 0; j < output.Height(); j++) {
            // grab the offset value for this pixel in the image
            Offset off = input.GetPixel(i,j);
            // set the pixel in the output image
            int dx = off.dx;
            int dy = off.dy;
            assert (dx >= 0 && dx <= 15);
            assert (dy >= 0 && dy <= 15);
            // to make a pretty image with purple, cyan, blue, & white pixels:
            int red = dx * 16;
            int green = dy *= 16;
            int blue = 255;
            assert (red >= 0 && red <= 255);
            assert (green >= 0 && green <= 255);
            output.SetPixel(i,j,Color(red,green,blue));
        }
    }
}


// ===================================================================================================
// ===================================================================================================

void usage(char* executable) {
    std::cerr << "Usage:  4 options" << std::endl;
    std::cerr << "  1)  " << executable << " compress input.ppm occupancy.pbm data.ppm offset.offset" << std::endl;
    std::cerr << "  2)  " << executable << " uncompress occupancy.pbm data.ppm offset.offset output.ppm" << std::endl;
    std::cerr << "  3)  " << executable << " compare input1.ppm input2.ppm output.pbm" << std::endl;
    std::cerr << "  4)  " << executable << " visualize_offset input.offset output.ppm" << std::endl;
}


// ===================================================================================================
// ===================================================================================================

int main(int argc, char* argv[]) {
    if (argc < 2) { usage(argv[1]); exit(1); }
    
    if (argv[1] == std::string("compress")) {
        if (argc != 6) { usage(argv[1]); exit(1); }
        // the original image:
        Image<Color> input;
        // 3 files form the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        input.Load(argv[2]);
        Compress(input,occupancy,hash_data,offset);
        // save the compressed representation
        occupancy.Save(argv[3]);
        hash_data.Save(argv[4]);
        offset.Save(argv[5]);
        
    } else if (argv[1] == std::string("uncompress")) {
        if (argc != 6) { usage(argv[1]); exit(1); }
        // the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        occupancy.Load(argv[2]);
        hash_data.Load(argv[3]);
        offset.Load(argv[4]);
        // the reconstructed image
        Image<Color> output;
        UnCompress(occupancy,hash_data,offset,output);
        // save the reconstruction
        output.Save(argv[5]);
        
    } else if (argv[1] == std::string("compare")) {
        if (argc != 5) { usage(argv[1]); exit(1); }
        // the original images
        Image<Color> input1;
        Image<Color> input2;
        input1.Load(argv[2]);
        input2.Load(argv[3]);
        // the difference image
        Image<bool> output;
        Compare(input1,input2,output);
        // save the difference
        output.Save(argv[4]);
        
    } else if (argv[1] == std::string("visualize_offset")) {
        if (argc != 4) { usage(argv[1]); exit(1); }
        // the 8-bit offset image (custom format)
        Image<Offset> input;
        input.Load(argv[2]);
        // a 24-bit color version of the image
        Image<Color> output;
        ConvertOffsetToColor(input,output);
        output.Save(argv[3]);
        
    } else {
        usage(argv[0]);
        exit(1);
    }
}
