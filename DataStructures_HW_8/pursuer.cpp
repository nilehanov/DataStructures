#include <cassert>
#include <iostream>
#include <vector>
#include "MersenneTwister.h"
#include "person.h"
#include "city.h"
#include "graph.h"
#include <iostream>

using namespace std;

City* MY_PURSUER_STRATEGY(const Person& p, const Graph& city_graph)
{
    const std::vector<City*>& neighbors = p.getLocation()->getNeighbors();
    bool another_pursuers_city=false;//helper//for checking if there is another pursuer in the next city
    vector<int> common_cities_count(neighbors.size(),0);//common heighbors count
    int max_count=0;//helper//for counting neighbors in common
    City* next_city;

    //corner case
    if(city_graph.getEvader()->getLocation()->getNeighbors().size()==1 &&
            city_graph.getEvader()->getLocation()->getNeighbors()[0] == p.getLocation())//if the evader is in the corner
    {
        for(int k=0;k<city_graph.getPursuers().size();k++)//consider each pursuer
        {
            if(city_graph.getPursuers()[k]->getLocation()==p.getLocation() &&
                    city_graph.getPursuers()[k]->getName()!=p.getName())//if there is other pursuer in the same city
            {
                next_city=city_graph.getEvader()->getLocation();
                return next_city;
            }
            else
            {
                return p.getLocation();
            }
        }

    }

    //base case
    for(int i=0;i<neighbors.size();i++)//go through all neighbors(possible moves)
    {
        for(int j=0;j<neighbors[i]->getNeighbors().size();j++)//go through all neighbors of each neighbor
        {
            for(int k=0;k<city_graph.getEvader()->getLocation()->getNeighbors().size();k++)//consider all moves
                //that the evader can make
            {
                if(neighbors[i]->getNeighbors()[j]==city_graph.getEvader()->getLocation()->getNeighbors()[k])
                {
                    max_count++;
                }
            }
        }
        common_cities_count[i]=max_count;
        max_count=0;
    }
    int position_in_neighbors_vector=0;
    for(int i=0;i<common_cities_count.size();i++)
    {
        if(common_cities_count[i]>max_count)
        {
            for(int k=0;k<city_graph.getPursuers().size();k++)//consider each pursuer
            {
                if(neighbors[i]==city_graph.getPursuers()[k]->getLocation())
                    another_pursuers_city=true;
            }
            if(!another_pursuers_city)
            {
                max_count=common_cities_count[i];
                position_in_neighbors_vector=i;
            }
        }
    }

    return neighbors[position_in_neighbors_vector];

}
