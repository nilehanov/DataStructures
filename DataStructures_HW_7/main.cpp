// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  map< string, map<string, int> > MY_MAP;

typedef map < string, map <string, map < string, int> > > MY_MAP_Thee_D;

MY_MAP data;
MY_MAP_Thee_D big_data;
int window;
 bool changed =false;

vector<string> words;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
    char c;
    word.clear();
    while (istr) {
        // just "peek" at the next character in the stream
        c = istr.peek();
        if (isspace(c))
        {
            // skip whitespace before a word starts
            istr.get(c);
            if (word != "")
            {
                // break words at whitespace
                return true;
            }
        } else if (c == '"')
        {
            // double quotes are a delimiter and a special "word"
            if (word == "")
            {
                istr.get(c);
                word.push_back(c);
            }
            return true;
        } else if (isalpha(c))
        {
            // this a an alphabetic word character
            istr.get(c);
            word.push_back(tolower(c));
        } else
        {
            // ignore this character (probably punctuation)
            istr.get(c);
        }
    }
    return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
    // returns a vector of strings of the different words
    std::vector<std::string> answer;
    std::string word;
    bool open_quote = false;
    while (ReadNextWord(istr,word))
    {
        if (word == "\"")
        {
            if (open_quote == false)
            {
                open_quote=true;
            }
            else
            {
                break;
            }
        }
        else
        {
            // add each word to the vector
            answer.push_back(word);
        }
    }
    return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method)
{
    // open the file stream
    std::ifstream istr(filename.c_str());
    if (!istr)
    {
        std::cerr << "ERROR cannot open file: " << filename << std::endl;
        //exit(1);
    }
    // verify the window parameter is appropriate
    if (window < 2)
    {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
    // verify that the parse method is appropriate
    bool ignore_punctuation = false;
    if (parse_method == "ignore_punctuation") {
        ignore_punctuation = true;
    } else {
        std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
        //exit(1);
    }



    string word ="";
    while (ReadNextWord(istr,word))
    {
        // skip the quotation marks (not used for this part)
        if (word == "\"") continue;
        words.push_back(word);


    }

    if(window==2)
    {
        cout<<"Loaded "<<filename;
        cout<<" with window = "<<window<<" and parse method = "<<parse_method<<endl<<endl;

    }

    for(int i=0;i<words.size();i++)
    {

        if(data.find(words[i])==data.end())//if not there
        {
            map <string, int> tmp_map;
            data.insert(make_pair(words[i],tmp_map));
        }
        if(i!=words.size()-1)
        {
            MY_MAP::iterator itr= data.find(words[i]);
            if((itr->second).find(words[i+1])== (itr->second).end() )// see if second word already exists
            {
                (itr->second).insert(make_pair(words[i+1],1));//if not, create a new pair
            }
            else
            {
                ((itr->second).find(words[i+1]))->second++;//increment occurence
            }
        }

    }



}
void LoadSampleText(MY_MAP_Thee_D &big_data, const std::string &filename, int window, const std::string &parse_method)
{
    /*
    // open the file stream
    std::ifstream istr(filename.c_str());
    if (!istr)
    {
        std::cerr << "ERROR cannot open file: " << filename << std::endl;
        //exit(1);
    }
    // verify the window parameter is appropriate
    if (window < 2)
    {
        std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
    // verify that the parse method is appropriate
    bool ignore_punctuation = false;
    if (parse_method == "ignore_punctuation") {
        ignore_punctuation = true;
    } else {
        std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
        //exit(1);
    }

*/

    string word ="";

    if(window==3)
    {
        cout<<"Loaded "<<filename;
        cout<<" with window = "<<window<<" and parse method = "<<parse_method<<endl<<endl;
    }

    map <string, int> tmp_map;
    string dummy_str="";//
    //data.insert()
    for(int i=0;i<words.size()-2;i++)
    {
        (big_data[words[i]][words[i+1]][words[i+2]])++;
        /* if(i==0)
            {
                cout<<"Loaded "<<filename;
                cout<<" with window = "<<window<<" and parse method = "<<parse_method<<endl<<endl;
            }
            if(big_data.find(words[i])==data.end())//if not there
            {
                //big_data.insert(make_pair(words[i],data.insert(make_pair(words[i+1],tmp_map))));
                big_data.insert(make_pair(words[i],data));
            }
            if(i!=words.size()-1 && i!=words.size()-2)
            {
                 //MY_MAP_Thee_D::iterator itr= big_data.find(words[i]);
                 if((itr->second).find(words[i+1])==(itr->second).end())
                 {
                     (itr->second).insert(make_pair(words[i+1],tmp_map));
                 }
                 if(i!=words.size()-1)
                 {

                 }
                 else
                 {

                 }

                 MY_MAP::iterator itr= data.find(words[i]);
            }
            //MY_MAP data;
            //MY_MAP_Thee_D big_data;
           // MY_MAP_Thee_D
           */
    }




}


int main () {

    // ASSIGNMENT: THE MAIN DATA STRUCTURE
    // MY_MAP data;
    // MY_MAP_Thee_D big_data;

    // Parse each command
    std::string command;

    while (std::cin >> command)
    {

        // load the sample text file

        if (command == "load")
        {
            std::string filename;
            std::string parse_method;
            std::cin >> filename >> window >> parse_method;
            ifstream istr(filename.c_str());

            LoadSampleText(data,filename, window, parse_method);

            LoadSampleText(big_data,filename, window, parse_method);

        }

        // print the portion of the map structure with the choices for the
        // next word given a particular sequence.
        else if (command == "print")
        {
            vector<string> sentence = ReadQuotedWords(std::cin);
            //work of if sentence.size() ==1  make window = 2
            if(changed==true)
            {
                window=3;
            }
            if(window==3 && sentence.size()!=2)
            {
                window=2;
                 changed =true;
            }
            if(window==2)
            {
                for(int i=0;i<sentence.size();i++)
                {
                    map <string,int>::iterator sub_itr;
                    MY_MAP::iterator itr=data.find(sentence[i]);
                    cout<<sentence[i]<<" (";//<<(itr->second).size()<<")\n";
                    int num_appeared=0;
                    /* for(sub_itr=(itr->second).begin();sub_itr!=(itr->second).end();sub_itr++)
                    {
                    num_appeared=num_appeared + sub_itr->second;
                    }*/
                    for(int j=0;j<words.size();j++)
                    {
                        if(words[j]==sentence[i])
                            num_appeared++;
                    }

                    cout<<num_appeared<<")\n";
                    itr=data.find(sentence[i]);
                    for(sub_itr=(itr->second).begin();sub_itr!=(itr->second).end();sub_itr++)
                    {
                        cout<<itr->first<<" "<<sub_itr->first<<" ("<<sub_itr->second<<")"<<endl;

                    }
                    cout<<endl;
                }
                if( changed ==true)
                {
                    //window=3;
                }

            }
            if(window==3)
            {

                for(int i=0;i<sentence.size();i++)
                {
                    cout<<sentence[i]<<" ";
                }

                MY_MAP_Thee_D::iterator itr= big_data.find(sentence[0]);
                MY_MAP::iterator itr_sub=(itr->second).find(sentence[1]);
                cout<<"("<<(itr_sub->second).size()<<")\n";
                map<string,int>::iterator tmp;
                tmp=(itr_sub->second).begin();
                for(int k=0;k<(itr_sub->second).size();k++)
                {
                    cout<<itr->first<<" "<<itr_sub->first<<" "<<tmp->first<<" ("<<tmp->second<<")\n";
                    if(k!=(itr->second).size()-1)
                    {
                        tmp++;
                    }
                }
                cout<<endl;


                /*
            for(MY_MAP::iterator itr=data.begin();itr!=data.end();itr++)
            {
                map <string,int>::iterator sub_itr;
                for(sub_itr=(itr->second).begin();sub_itr!=(itr->second).end();sub_itr++)
                {
                    cout<<itr->first<<"\t"<<sub_itr->first<<"\t"<<sub_itr->second<<endl;

                }
            }


            //
            // ASSIGNMENT: ADD YOUR COMMANDS HERE
            //
            */


            }
        }

        // generate the specified number of words
        else if (command == "generate")
        {
            std::vector<std::string> sentence = ReadQuotedWords(std::cin);
            // how many additional words to generate
            int length;
            std::cin >> length;
            std::string selection_method;
            std::cin >> selection_method;
            bool random_flag;
            if (selection_method == "random")
            {
                random_flag = true;
            }
            else
            {
                assert (selection_method == "most_common");
                random_flag = false;
            }

            if(!random_flag)
            {
                for(int i=0;i<sentence.size();i++)
                {
                    string base_word; //search stats of this word
                    base_word=sentence[i];
                    cout<<base_word<<" ";
                    for(int k=0;k<length;k++)
                    {
                        MY_MAP::iterator itr= data.find(base_word);
                        map <string,int>::iterator sub_itr;
                        int max=0;
                        string next_word;
                        for(sub_itr=(itr->second).begin();sub_itr!=(itr->second).end();sub_itr++)
                        {
                            if(sub_itr->second>max)
                            {
                                max=sub_itr->second;
                                next_word=sub_itr->first;

                            }
                        }

                        if(k==length-1)
                        {
                            cout<<((itr->second).find(next_word))->first;
                            continue;
                        }
                        cout<<((itr->second).find(next_word))->first<<" ";
                        base_word=((itr->second).find(next_word))->first;
                    }
                }

                cout<<endl<<endl;
            }


            //
            // ASSIGNMENT: ADD YOUR COMMANDS HERE
            //


        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            std::cout << "WARNING: Unknown command: " << command << std::endl;
        }
    }
}

