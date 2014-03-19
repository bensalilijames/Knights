#include "GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MapSquares.h"

GameLevel::GameLevel() {
    monsterCount = 0;
}

GameLevel::~GameLevel() {
    
}

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
	
	std::string line; //Sets up string manipulation techniques
	std::string line_underlay;
	std::ifstream map_data;
	std::ifstream map_data_underlay;
	switch(level) //Loads up the correct text files depending on which wave the user is on
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
	if(map_data.is_open()) //Checks file has been loaded correctly
	{
		int j = 0;
		while(std::getline(map_data,line) && std::getline(map_data_underlay,line_underlay)) //While data left in file, assign line of text to the string constructs
		{
			for(int i = 0; i <= line.length(); i++) //For each letter in the string
			{
				if(line.find(",") != std::string::npos) //If a comma is found then set map height and width to the values on this line
				{
					mapHeight = std::atoi(line.substr(0,line.find(",")).c_str());
					mapWidth = std::atoi(line.substr(line.find(",")+1).c_str());
					empty_content_map = al_create_bitmap(mapWidth*50,mapHeight*50);
					monster_overlay = al_create_bitmap(mapWidth*50,mapHeight*50);
				}
                
				if(line.substr(i,1) == "T") //Tree squares randomised between 3 images
				{
					levelMap[j][i] = MapSquares::treeSquare[rand() % 3];
				}
				else if(line.substr(i,1) == "R") //Rock squares randomised between 4 images
				{
					levelMap[j][i] = MapSquares::rockSquare[rand() % 4];
				}
				else if(line.substr(i,1) == "A") //Monster ID 1
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->x_position = i*50;
                    monsterToAdd->y_position = j*50;
                    monsterToAdd->spawn(1);
					monsters.push_back(monsterToAdd);
					monsterCount++;
				}
				else if(line.substr(i,1) == "B") //Monster ID 2
				{
                    Monster* monsterToAdd = new Monster();
                    monsterToAdd->x_position = i*50;
                    monsterToAdd->y_position = j*50;
                    monsterToAdd->spawn(2);
					monsters.push_back(monsterToAdd);
					monsterCount++;
				}
				else if(line.substr(i,1) == "P") //Portal position
				{
					portalX = i*50;
					portalY = j*50;
				}
				else if(line.substr(i,1) == "C") //Player character start position
				{
					player->x_position = i*50;
					player->y_position = j*50;
				}
                
				if(line_underlay.substr(i,1) == "N") //Various underlay options ñ polar or grass
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[0];
				}
				else if(line_underlay.substr(i,1) == "O")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[1];
				}
				else if(line_underlay.substr(i,1) == "P")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[2];
				}
				else if(line_underlay.substr(i,1) == "Q")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[3];
				}
				else if(line_underlay.substr(i,1) == "R")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[4];
				}
				else if(line_underlay.substr(i,1) == "S")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[5];
				}
				else if(line_underlay.substr(i,1) == "T")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[6];
				}
				else if(line_underlay.substr(i,1) == "U")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[7];
				}
				else if(line_underlay.substr(i,1) == "V")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[8];
				}
				else if(line_underlay.substr(i,1) == "W")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[9];
				}
				else if(line_underlay.substr(i,1) == "X")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[10];
				}
				else if(line_underlay.substr(i,1) == "Y")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[11];
				}
				else if(line_underlay.substr(i,1) == "Z")
				{
					levelMapUnderlay[j][i] = MapSquares::polarSquare[12];
				}
				else if(line_underlay.substr(i,1) == "G")
				{
					levelMapUnderlay[j][i] = MapSquares::grassSquare[0];
				}
                
			}
			j++;
		}
		map_data.close(); //Closes data files
		map_data_underlay.close();
	}
    
	for(int i = 0; i < mapHeight; i++)
	{
		for(int j = 0; j < mapWidth; j++) //Draw the underlay image and the overlay image if it isnít grass
		{
            al_set_target_bitmap(empty_content_map);
			al_draw_bitmap(levelMapUnderlay[i][j]->mapImage,j*50,i*50,0);
            if (levelMap[i][j] != MapSquares::grassSquare[0])
                al_draw_bitmap(levelMap[i][j]->mapImage,j*50,i*50,0);
		}
	}

}