#include "city.h"

bool City::isNeighbor(City* city) const
{
    return true;

}

// MODIFIERS
bool City::addNeighbor(City* city)
{
    return true;
}
bool City::removeNeighbor(City* city)
{
    return true;
}

// Tell the neighboring cities to remove this City* from its vector of neighbors.
void removeCityFromItsNeighbors() {}//remove implemented in graph.cpp
