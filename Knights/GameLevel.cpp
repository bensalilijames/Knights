#include "GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MapSquares.h"

void GameLevel::loadLevel(int level, Player* player) {
    
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            levelMapItems[i][j] = NULL;
        }
    }

    levelMap.resize(50);
    levelMapUnderlay.resize(50);
    
	for(int i = 0; i <= 49; i++)
	{
		for(int j = 0; j <=49; j++)
		{
			levelMap[i].push_back(MapSquares::grassSquare[0]); //Sets up all squares to grassSquare initally
            levelMapUnderlay[i].push_back(MapSquares::grassSquare[0]);
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
                mapHeight = std::atoi(line.substr(0,line.find(",")).c_str());
                mapWidth = std::atoi(line.substr(line.find(",")+1).c_str());
                empty_content_map = al_create_bitmap(mapWidth*50,mapHeight*50);
                monster_overlay = al_create_bitmap(mapWidth*50,mapHeight*50);
            }
            
            int column = 0;
            
            for (char& letter : line)
			{
				if(letter == 'T') //Tree squares randomised between 3 images
				{
					levelMap[row][column] = MapSquares::treeSquare[rand() % 3];
				}
				else if(letter == 'R') //Rock squares randomised between 4 images
				{
					levelMap[row][column] = MapSquares::rockSquare[rand() % 4];
				}
				else if(letter == 'A') //Monster ID 1
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(1);
					monsters.push_back(monsterToAdd);
					monsterCount++;
				}
				else if(letter == 'B') //Monster ID 2
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->setPosition(column * 50, row * 50);
                    monsterToAdd->spawn(2);
					monsters.push_back(monsterToAdd);
					monsterCount++;
				}
				else if(letter == 'P') //Portal position
				{
					portalX = column * 50;
					portalY = row * 50;
				}
				else if(letter == 'C') //Player character start position
				{
                    player->setPosition(column * 50, row * 50);
				}
                
                column++;
            }
            
            column = 0;
            
            for (char& letter : line_underlay)
            {
				if(letter == 'N') //Various underlay options of polar or grass
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[0];
				}
				else if(letter == 'O')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[1];
				}
				else if(letter == 'P')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[2];
				}
				else if(letter == 'Q')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[3];
				}
				else if(letter == 'R')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[4];
				}
				else if(letter == 'S')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[5];
				}
				else if(letter == 'T')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[6];
				}
				else if(letter == 'U')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[7];
				}
				else if(letter == 'V')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[8];
				}
				else if(letter == 'W')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[9];
				}
				else if(letter == 'X')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[10];
				}
				else if(letter == 'Y')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[11];
				}
				else if(letter == 'Z')
				{
					levelMapUnderlay[row][column] = MapSquares::polarSquare[12];
				}
				else if(letter == 'G')
				{
					levelMapUnderlay[row][column] = MapSquares::grassSquare[0];
				}
                column++;
			}
			row++;
		}
		map_data.close();
		map_data_underlay.close();
	}
    
	for(int i = 0; i < mapHeight; i++)
	{
		for(int j = 0; j < mapWidth; j++) //Draw the underlay image and the overlay image if it isnít grass
		{
            al_set_target_bitmap(empty_content_map);
			al_draw_bitmap(levelMapUnderlay[i][j]->getImage(),j*50,i*50,0);
            if (levelMap[i][j] != MapSquares::grassSquare[0])
                al_draw_bitmap(levelMap[i][j]->getImage(),j*50,i*50,0);
		}
	}

}