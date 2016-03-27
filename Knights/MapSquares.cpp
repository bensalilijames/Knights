#include "MapSquares.h"

void MapSquares::setMapSquares(void) {
    treeSquare.push_back(std::make_unique<MapSquare>("tree.bmp", true));
    treeSquare.push_back(std::make_unique<MapSquare>("tree2.bmp", true));
    treeSquare.push_back(std::make_unique<MapSquare>("tree3.bmp", true));

    grassSquare.push_back(std::make_unique<MapSquare>("grass.bmp", false));
 
    rockSquare.push_back(std::make_unique<MapSquare>("rock.bmp", true));
    rockSquare.push_back(std::make_unique<MapSquare>("rock2.bmp", true));
    rockSquare.push_back(std::make_unique<MapSquare>("rock3.bmp", true));
    rockSquare.push_back(std::make_unique<MapSquare>("rock4.bmp", true));

    polarSquare.push_back(std::make_unique<MapSquare>("polar.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarBLC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarBRC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarDU.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarIBLC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarIBRC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarITLC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarITRC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarLR.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarRL.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarTLC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarTRC.bmp", false));
    polarSquare.push_back(std::make_unique<MapSquare>("polarUD.bmp", false));
    
}

std::vector<MapSquarePtr> MapSquares::treeSquare;
std::vector<MapSquarePtr> MapSquares::rockSquare;
std::vector<MapSquarePtr> MapSquares::polarSquare;
std::vector<MapSquarePtr> MapSquares::grassSquare;

