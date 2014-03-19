#ifndef MAPSQUARES_H
#define MAPSQUARES_H

#include "MapSquare.h"
#include <vector>

class MapSquares {
    public:
    static std::vector<MapSquare*> treeSquare;
    static std::vector<MapSquare*> rockSquare;
    static std::vector<MapSquare*> polarSquare;
    static std::vector<MapSquare*> grassSquare;
    
    static void setMapSquares();
};

#endif