#include "MapSquares.h"
#include <string>

void MapRegistry::registerDefaultSquares() {
    MapRegistry::registerSquare("tree1", "tree.bmp", true, MapSquareGroup::Tree);
    MapRegistry::registerSquare("tree2", "tree2.bmp", true, MapSquareGroup::Tree);
    MapRegistry::registerSquare("tree3", "tree3.bmp", true, MapSquareGroup::Tree);

    MapRegistry::registerSquare("grass", "grass.bmp", false, MapSquareGroup::Grass);
 
    MapRegistry::registerSquare("rock1", "rock.bmp", true, MapSquareGroup::Rock);
    MapRegistry::registerSquare("rock2", "rock2.bmp", true, MapSquareGroup::Rock);
    MapRegistry::registerSquare("rock3", "rock3.bmp", true, MapSquareGroup::Rock);
    MapRegistry::registerSquare("rock4", "rock4.bmp", true, MapSquareGroup::Rock);

    MapRegistry::registerSquare("polar", "polar.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarBLC", "polarBLC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarBRC", "polarBRC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarDU", "polarDU.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarIBLC", "polarIBLC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarIBRC", "polarIBRC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarITLC", "polarITLC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarITRC", "polarITRC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarLR", "polarLR.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarRL", "polarRL.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarRLC", "polarTLC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarTRC", "polarTRC.bmp", false, MapSquareGroup::Polar);
    MapRegistry::registerSquare("polarUD", "polarUD.bmp", false, MapSquareGroup::Polar);
}

std::vector<std::pair<std::string, MapSquarePtr>> MapRegistry::s_registeredSquares;

void MapRegistry::registerSquare(const std::string& id,
                                 const std::string& imageFile,
                                 bool collidable,
                                 MapSquareGroup group)
{
    auto pair = std::make_pair(id, std::make_unique<MapSquare>(imageFile.c_str(), collidable, group));
    s_registeredSquares.push_back(std::move(pair));
}

MapSquare* MapRegistry::getRegisteredSquare(const std::string& id)
{
    return std::find_if(s_registeredSquares.begin(),
                        s_registeredSquares.end(),
                        [&](std::pair<std::string, MapSquarePtr>& item)
                            {
                                if (item.first == id)
                                    return true;
                                return false;
                            })->second.get();
}

MapSquare* MapRegistry::getRandomSquareInGroup(MapSquareGroup group)
{
    std::vector<MapSquare*> validSquares;
    
    for(const auto& pair : s_registeredSquares)
    {
        if(pair.second->getGroup() == group)
        {
            validSquares.push_back(pair.second.get());
        }
    }
    
    const int randomInt = rand() % validSquares.size();
    
    return validSquares.at(randomInt);
}
