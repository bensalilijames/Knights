#include "MapSquares.h"

void MapSquares::setMapSquares(void) {
    treeSquare.push_back(new MapSquare("tree.bmp", true));
    treeSquare.push_back(new MapSquare("tree2.bmp", true));
    treeSquare.push_back(new MapSquare("tree3.bmp", true));

    grassSquare.push_back(new MapSquare("grass.bmp", false));
 
    rockSquare.push_back(new MapSquare("rock.bmp", true));
    rockSquare.push_back(new MapSquare("rock2.bmp", true));
    rockSquare.push_back(new MapSquare("rock3.bmp", true));
    rockSquare.push_back(new MapSquare("rock4.bmp", true));

    polarSquare.push_back(new MapSquare("polar.bmp", false));
    polarSquare.push_back(new MapSquare("polarBLC.bmp", false));
    polarSquare.push_back(new MapSquare("polarBRC.bmp", false));
    polarSquare.push_back(new MapSquare("polarDU.bmp", false));
    polarSquare.push_back(new MapSquare("polarIBLC.bmp", false));
    polarSquare.push_back(new MapSquare("polarIBRC.bmp", false));
    polarSquare.push_back(new MapSquare("polarITLC.bmp", false));
    polarSquare.push_back(new MapSquare("polarITRC.bmp", false));
    polarSquare.push_back(new MapSquare("polarLR.bmp", false));
    polarSquare.push_back(new MapSquare("polarRL.bmp", false));
    polarSquare.push_back(new MapSquare("polarTLC.bmp", false));
    polarSquare.push_back(new MapSquare("polarTRC.bmp", false));
    polarSquare.push_back(new MapSquare("polarUD.bmp", false));
    
}

std::vector<MapSquare*> MapSquares::treeSquare;
std::vector<MapSquare*> MapSquares::rockSquare;
std::vector<MapSquare*> MapSquares::polarSquare;
std::vector<MapSquare*> MapSquares::grassSquare;

