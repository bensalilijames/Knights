#include "GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MapSquares.h"

void GameLevel::loadLevel(int level, Player& player) {

    levelMap.resize(50);
    levelMapUnderlay.resize(50);
    
	for(int i = 0; i <= 49; i++)
	{
		for(int j = 0; j <=49; j++)
		{
			levelMap[i].push_back(MapSquares::grassSquare[0].get()); //Sets up all squares to grassSquare initally
            levelMapUnderlay[i].push_back(MapSquares::grassSquare[0].get());
		}
	}
    
    monsters.clear();
	
	std::string line;
	std::string line_underlay;
	std::ifstream map_data;
	std::ifstream map_data_underlay;
	switch(level)
	{
        case 1:
            map_data.open("map_data.txt");
            map_data_underlay.open("map_data_underlay.txt");
            break;
        case 2:
        case 10:
            map_data.open("map_data2.txt");
            map_data_underlay.open("map_data_underlay2.txt");
            break;
        case 3:
        case 7:
            map_data.open("map_data3.txt");
            map_data_underlay.open("map_data_underlay3.txt");
            break;
        case 4:
            map_data.open("map_data4.txt");
            map_data_underlay.open("map_data_underlay4.txt");
            break;
        case 5:
            map_data.open("map_data5.txt");
            map_data_underlay.open("map_data_underlay5.txt");
            break;
        case 6:
        case 8:
            map_data.open("map_data6.txt");
            map_data_underlay.open("map_data_underlay6.txt");
            break;
        case 9:
            map_data.open("map_data7.txt");
            map_data_underlay.open("map_data_underlay7.txt");
            break;
        default:
            map_data.open("map_data.txt");
            map_data_underlay.open("map_data_underlay.txt");
            break;
	}
	if (map_data.is_open())
	{
		int row = 0;
		while (std::getline(map_data,line) && std::getline(map_data_underlay,line_underlay))
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
				if(letter == 'T') //Tree squares randomised between 3 images
				{
					levelMap[row][column] = MapSquares::treeSquare[rand() % 3].get();
				}
				else if(letter == 'R') //Rock squares randomised between 4 images
				{
					levelMap[row][column] = MapSquares::rockSquare[rand() % 4].get();
				}
				else if(letter == 'A') //Monster ID 1
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(CharacterType::Froggy);
					monsters.push_back(monsterToAdd);
					m_monsterCount++;
				}
				else if(letter == 'B') //Monster ID 2
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(CharacterType::Globby);
					monsters.push_back(monsterToAdd);
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
            
            for (char& letter : line_underlay)
            {
				if(letter == 'N') //Various underlay options of polar or grass
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[0].get();
				}
				else if(letter == 'O')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[1].get();
				}
				else if(letter == 'P')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[2].get();
				}
				else if(letter == 'Q')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[3].get();
				}
				else if(letter == 'R')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[4].get();
				}
				else if(letter == 'S')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[5].get();
				}
				else if(letter == 'T')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[6].get();
				}
				else if(letter == 'U')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[7].get();
				}
				else if(letter == 'V')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[8].get();
				}
				else if(letter == 'W')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[9].get();
				}
				else if(letter == 'X')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[10].get();
				}
				else if(letter == 'Y')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[11].get();
				}
				else if(letter == 'Z')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[12].get();
				}
				else if(letter == 'G')
				{
					levelMapUnderlay[row][column] = MapSquares::grassSquare[0].get();
				}
                column++;
			}
			row++;
		}
		map_data.close();
		map_data_underlay.close();
	}
    
	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapWidth; j++) //Draw the underlay image and the overlay image if it isnít grass
		{
            al_set_target_bitmap(m_emptyContentMap);
			al_draw_bitmap(levelMapUnderlay[i][j]->getImage(),j*50,i*50,0);
            if (levelMap[i][j] != MapSquares::grassSquare[0].get())
                al_draw_bitmap(levelMap[i][j]->getImage(),j*50,i*50,0);
		}
	}

}

void GameLevel::dropItem(Item *item, int x, int y)
{
    m_itemsMap.push_back(std::make_pair(item, Coord(x, y)));
}