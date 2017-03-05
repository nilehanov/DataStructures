#include <cassert>
#include <iostream>
#include <vector>
#include "MersenneTwister.h"
#include "person.h"
#include "city.h"
#include "graph.h"
#include <iostream>

City* MY_EVADER_STRATEGY(const Person& p, const Graph& city_graph)
{
    const std::vector<City*>& neighbors = p.getLocation()->getNeighbors();
    std::vector<City*> possible_moves;//used to store each logical move
    bool in_list=false;//helper//for checking if the next city is already in the possible_moves vector
    for(int i=0;i<neighbors.size();i++)//go through all possible moves
    {
        for(int k=0;k<city_graph.getPursuers().size();k++)//consider each pursuer
        {
            for(int j=0;j<city_graph.getPursuers()[k]->getLocation()->getNeighbors().size();j++)//consider each possible
                //next move of the pursuer
            {
                if(neighbors[i]!=(city_graph.getPursuers())[k]->getLocation()->getNeighbors()[j]
                        && neighbors[i]!=city_graph.getPursuers()[k]->getLocation())//if neighbor city is not pursuer's
                    //current city's neighbor and not pursuer's current city go ahead and add it to possible moves
                {
                    for(int n=0;n<possible_moves.size();n++)//see if option is already in the list
                    {
                        if(possible_moves[n]==city_graph.getPursuers()[k]->getLocation()->getNeighbors()[j])
                            in_list=true;
                    }
                    if(!in_list)//push back if all tests are passed
                    {
                        possible_moves.push_back((city_graph.getPursuers())[k]->getLocation()->getNeighbors()[j]);
                    }
                    in_list=false;//reset to false
                }
            }
        }
    }
    //Now find the city that has most number of neighbors
    int max=0;
    City* next_city;
    for(int n=0;n<possible_moves.size();n++)
    {
        if(possible_moves[n]->getNeighbors().size()>max)
        {
            max=possible_moves[n]->getNeighbors().size();
            next_city=possible_moves[n];
        }
    }
    if(max!=0)
    {
        return next_city;
    }
    //If no such city exists move to a neighbor city that is first on the list
    return neighbors[0];
}

