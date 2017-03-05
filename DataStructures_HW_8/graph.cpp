
#include "graph.h"

bool IsLessThan(City* a, City* b)//sort function helper
{
    return (a->getName() < b->getName() );
}

bool Graph::addCity(const std::string& city_name)
{
    for(std::vector<City*>::iterator p=cities.begin();p!=cities.end();++p)//test if exist
    {
        if((*p)->getName()==city_name)
            return false;
    }
    City* new_city = new City (city_name);
    cities.push_back(new_city);
    sort(cities.begin(),cities.end(),IsLessThan);
    return true; //only when city doesnt exist
}

City* Graph::getCityWithName(const std::string& name) const
{
    for(int i=0;i<cities.size();i++)
    {
        if( (cities[i])->getName()== name)
        {
            return cities[i];
        }
    }
    return NULL;
}

bool Graph::addLink(const std::string& city_name1, const std::string& city_name2)
{

    City* city_name_1=getCityWithName(city_name1);
    City* city_name_2=getCityWithName(city_name2);
    if(city_name_1==NULL || city_name_2==NULL)//test for existance
    {
        return false;
    }
    for(std::vector<City*>::const_iterator p=(city_name_1->getNeighbors()).begin();
        p!=(city_name_1->getNeighbors()).end();++p)
    {
        if((*p)->getName()==city_name2)//test for existance of the link
        {
            return false;
        }
    }
    for(std::vector<City*>::const_iterator p=city_name_2->getNeighbors().begin();
        p!=city_name_2->getNeighbors().end();++p)
    {
        if((*p)->getName()==city_name1)//test for existance of the link
        {
            return false;
        }
    }
    city_name_1->getNeighbors().push_back(city_name_2);
    city_name_2->getNeighbors().push_back(city_name_1);
    sort(city_name_1->getNeighbors().begin(),city_name_1->getNeighbors().end(),IsLessThan);//sort
    sort(city_name_2->getNeighbors().begin(),city_name_2->getNeighbors().end(),IsLessThan);//sort

    return true;

}

std::ostream& operator<<(std::ostream &ostr, const Graph &city_graph)
{

    int k=(city_graph.cities).size();
    for(int i=0;i<k;i++)
    {
        std::cout<<"\n";
        if((city_graph.cities[i])->getNeighbors().size()==0)
        {
            std::cout<<"Neighbors for city "<<(city_graph.cities[i])->getName()<<": ";
        }
        else
        {
            std::cout<<"Neighbors for city "<<(city_graph.cities[i])->getName()<<":  ";
        }
        for(int j=0;j< (city_graph.cities[i])->getNeighbors().size(); j++)
        {
            if(j==(city_graph.cities[i])->getNeighbors().size()-1)
            {
                ostr<<(city_graph.cities[i])->getNeighbors()[j]->getName();
                continue;
            }
            ostr<<(city_graph.cities[i])->getNeighbors()[j]->getName()<<" ";
        }

    }
    /////////GAME OUTPUT BEGIN////

    if(city_graph.getEvader()!=NULL)
    {
        std::cout<<"\n";
        std::cout<<"Evader student is in "<<(city_graph.getEvader()->getLocation())->getName()<<"\n";
    }
    if(city_graph.getPursuers().size()!=0)
    {
        for(int i=0;i<city_graph.getPursuers().size();i++)
        {
            if(city_graph.getPursuers().size()==1)
            {
                std::cout<<"Pursuer "<<(city_graph.pursuers[i])->getName()<<" is in "
                        <<(city_graph.pursuers[i]->getLocation())->getName();
                continue;
            }
            if(city_graph.getPursuers().size()!=1 && i==city_graph.getPursuers().size()-1)
            {
                std::cout<<"Pursuer "<<(city_graph.pursuers[i])->getName()<<" is in "
                        <<(city_graph.pursuers[i]->getLocation())->getName();
                continue;
            }
            std::cout<<"Pursuer "<<(city_graph.pursuers[i])->getName()<<" is in "
                    <<(city_graph.pursuers[i]->getLocation())->getName()<<"\n";//<<endl;
        }
    }
    /////////GAME OUTPUT END////
    std::cout<<"\n"<<"\n";
    return ostr;
}
Graph::~Graph()//destructor
{
    for(int i=0; i<cities.size();i++)
    {
        delete cities[i];
        cities[i]==NULL;
    }
    if(evader!=NULL)
    {
        delete evader;
        evader=NULL;
    }
    if(pursuers.size()!=0)
    {
        for(int i=0;i<pursuers.size();i++)
        {
            delete pursuers[i];
            pursuers[i]=NULL;
        }
    }
}

bool Graph::removeCity(const std::string& city_name)
{

    City* to_be_removed= getCityWithName(city_name);
    if(to_be_removed==NULL)
    {
        return false;
    }

    for(int i=0; i<(to_be_removed->getNeighbors()).size();i++)
        //go through the neightbors and set their pointers to null
    {
        std::string neighbor = (to_be_removed->getNeighbors()[i])->getName();
        City* neighbor_of_city= getCityWithName(neighbor);
        for(int j=0; j<(neighbor_of_city->getNeighbors()).size();j++)
        {
            if((neighbor_of_city->getNeighbors()[j])==to_be_removed)
            {
                neighbor_of_city->getNeighbors().erase( neighbor_of_city->getNeighbors().begin()+j);//erase this name from the neighbor
            }
        }
    }
    if(evader!=NULL)
    {
        if(evader->getLocation()==to_be_removed)
        {
            std::cout<<"Evader "<<evader->getName()<<" removed from the game"<<"\n";
            delete evader;
            evader=NULL;
        }
    }
    for(int i=0;i<pursuers.size();i++)
    {
        if(pursuers[i]->getLocation()==to_be_removed)
        {
            std::cout<<"Pursuer "<<pursuers[i]->getName()<<" removed from the game"<<"\n";
            delete pursuers[i];
            pursuers.erase(pursuers.begin()+i);
            i--;
        }
    }
    for(int i=0; i<cities.size();i++)
    {
        if(cities[i]==to_be_removed)
        {
            cities.erase(cities.begin()+i);
        }
    }

    delete to_be_removed;
    to_be_removed=NULL;

    return true;

}

bool Graph::removeLink(const std::string& city_name1, const std::string& city_name2)
{
    City* city_name_1=getCityWithName(city_name1);
    City* city_name_2=getCityWithName(city_name2);
    if(city_name_1==NULL || city_name_2==NULL)
    {
        return false;
    }
    bool no_link_1=true;
    bool no_link_2=true;

    for(std::vector<City*>::iterator p=city_name_1->getNeighbors().begin();
        p!=city_name_1->getNeighbors().end();++p)//link test
    {
        if((*p)->getName()==city_name2)
        {
            no_link_1=false;
        }
    }
    for(std::vector<City*>::iterator p=city_name_2->getNeighbors().begin();
        p!=city_name_2->getNeighbors().end();++p)//link test
    {
        if((*p)->getName()==city_name1)
        {
            no_link_2=false;
        }
    }
    if(no_link_1==true || no_link_2==true)
    {
        return false;
    }
    for(int i=0; i<(city_name_1->getNeighbors()).size();i++)//go through the neightbors and set their pointers to null
    {
        if((city_name_1->getNeighbors()[i])==city_name_2)
        {
            city_name_1->getNeighbors().erase( city_name_1->getNeighbors().begin()+i);
        }
    }
    for(int i=0; i<(city_name_2->getNeighbors()).size();i++)//go through the neightbors and set their pointers to null
    {
        if((city_name_2->getNeighbors()[i])==city_name_1)
        {
            city_name_2->getNeighbors().erase( city_name_2->getNeighbors().begin()+i);
        }
    }
    return true;
}
bool Graph::placePursuer(const std::string& person_name, const std::string& city_name)
{
    for(std::vector<Person*>::iterator p=pursuers.begin();p!=pursuers.end();++p)
    {
        if((*p)->getName()==person_name)
            return false;
    }
    City* city_location=getCityWithName(city_name);
    Person* new_ta= new Person (person_name,city_location);
    pursuers.push_back(new_ta);

    return true;
}
bool Graph::placeEvader(const std::string& person_name, const std::string& city_name)
{
    if(evader!=NULL)
    {
        return false;
    }
    City* city_location=getCityWithName(city_name);
    evader=new Person (person_name,city_location);
    return true;
}
