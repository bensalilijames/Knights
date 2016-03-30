#include "GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MapSquares.h"

void GameLevel::loadLevel(int level, Player& player) {

    m_map.resize(50);
    m_mapUnderlay.resize(50);
    
	for(int i = 0; i <= 49; i++)
	{
		for(int j = 0; j <=49; j++)
		{
            m_map[i].push_back(MapRegistry::getRegisteredSquare("grass")); //Sets up all squares to grassSquare initally
            m_mapUnderlay[i].push_back(MapRegistry::getRegisteredSquare("grass"));
		}
	}
    
    std::string line;
	std::string lineUnderlay;
	std::ifstream mapData;
	std::ifstream mapDataUnderlay;
    
    std::string mapFile = "map_data";
    mapFile += std::to_string(level);
    mapFile += ".txt";
    
    std::string mapUnderlayFile = "map_data_underlay";
    mapUnderlayFile += std::to_string(level);
    mapUnderlayFile += ".txt";
    
    mapData.open(mapFile);
    mapDataUnderlay.open(mapUnderlayFile);
    
	if (mapData.is_open())
	{
		int row = 0;
		while (std::getline(mapData, line) && std::getline(mapDataUnderlay, lineUnderlay))
		{
            if(line.find(",") != std::string::npos)
            {
                m_mapHeight = std::atoi(line.substr(0,line.find(",")).c_str());
                m_mapWidth = std::atoi(line.substr(line.find(",")+1).c_str());
                m_emptyContentMap = al_create_bitmap(m_mapWidth * 50, m_mapHeight * 50);
                m_monsterOverlay = al_create_bitmap(m_mapWidth * 50, m_mapHeight * 50);
            }
            
            int column = 0;
            
            for (char& letter : line)
			{
				if(letter == 'T') //Tree squares
				{
                    m_map[row][column] = MapRegistry::getRandomSquareInGroup(MapSquareGroup::Tree);
				}
				else if(letter == 'R') //Rock squares
				{
					m_map[row][column] = MapRegistry::getRandomSquareInGroup(MapSquareGroup::Rock);
				}
				else if(letter == 'A') //Monster ID 1
				{
                    auto monsterToAdd = std::make_unique<Monster>();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(CharacterType::Froggy);
                    m_monsters.push_back(std::move(monsterToAdd));
					m_monsterCount++;
				}
				else if(letter == 'B') //Monster ID 2
				{
                    auto monsterToAdd = std::make_unique<Monster>();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(CharacterType::Globby);
					m_monsters.push_back(std::move(monsterToAdd));
					m_monsterCount++;
				}
				else if(letter == 'P') //Portal position
				{
					m_portalX = column * 50;
					m_portalY = row * 50;
				}
				else if(letter == 'C') //Player character start position
				{
                    player.setPosition(column * 50, row * 50);
				}
                
                column++;
            }
            
            column = 0;
            
            for (char& letter : lineUnderlay)
            {
				if(letter == 'N') //Various underlay options of polar or grass
				{
                    m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polar");
				}
				else if(letter == 'O')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarBLC");
				}
				else if(letter == 'P')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarBRC");
				}
				else if(letter == 'Q')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarDU");
				}
				else if(letter == 'R')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarIBLC");
				}
				else if(letter == 'S')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarIBRC");
				}
				else if(letter == 'T')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarITLC");
				}
				else if(letter == 'U')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarITRC");
				}
				else if(letter == 'V')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarLR");
				}
				else if(letter == 'W')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarRL");
				}
				else if(letter == 'X')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarTLC");
				}
				else if(letter == 'Y')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarTRC");
				}
				else if(letter == 'Z')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("polarUD");
				}
				else if(letter == 'G')
				{
					m_mapUnderlay[row][column] = MapRegistry::getRegisteredSquare("grass");
				}
                column++;
			}
			row++;
		}
		mapData.close();
		mapDataUnderlay.close();
	}
    
    //Cache the empty map image in m_emptyContentMap (no need to redraw every frame)
	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapWidth; j++)
		{
            al_set_target_bitmap(m_emptyContentMap);
			al_draw_bitmap(m_mapUnderlay[i][j]->getImage(),
                           j * 50,
                           i * 50,
                           0);
            
            //Only add the overlay image if it isn't grass
            if (m_map[i][j] != MapRegistry::getRegisteredSquare("grass"))
            {
                al_draw_bitmap(m_map[i][j]->getImage(),
                               j * 50,
                               i * 50,
                               0);
            }
		}
	}

}

void GameLevel::dropItem(Item *item, int x, int y)
{
    m_mapItems.push_back(std::make_pair(item, Coord(x, y)));
}