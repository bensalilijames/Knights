#include "Monster.h"
#include <stdio.h>
#include <stdlib.h>
#include "Items.h"

void Monster::handleMovement(GameState* game)
{
	if(spawned == true)
	{
        last_direction = current_direction;
		if(inCombat == false) //If Monster isn’t in combat then make it move randomly
		{
			if(isMoving == false)
			{
				if((rand() % 200)==1)
				{
					isMoving = true;
					current_direction = 2 * (rand() % 4) + 1;
				}
			}
			else
			{
				if (!isCollision(current_direction,49,49,game->currentLevel->levelMap))
				{	
					if(current_direction == 1) //UP
					{
						y_position--;
					}
		
					if(current_direction == 5) //DOWN
					{
						y_position++;
					}

					if(current_direction == 3) //RIGHT
					{
						x_position++;
					}

					if(current_direction == 7) //LEFT
					{
						x_position--;
					}
		
					if((rand() % 70)==1)
					{
						isMoving = false;
					}
				}
				else
				{
					isMoving = false;
				}
			}
		}
		else //Otherwise move in direction of player
		{
			if(game->mainCharacter->x_position - 30 > x_position && !isCollision(3,49,49,game->currentLevel->levelMap))
			{
				x_position++;
				last_direction = 3;
			}
			if(game->mainCharacter->x_position + 20 < x_position && !isCollision(7,49,49,game->currentLevel->levelMap))
			{
				x_position--;
				last_direction = 7;
			}
			if(game->mainCharacter->y_position - 30 > y_position && !isCollision(5,49,49,game->currentLevel->levelMap))
			{
				y_position++;
				last_direction = 5;
			}
			if(game->mainCharacter->y_position + 20 < y_position && !isCollision(1,49,49,game->currentLevel->levelMap))
			{
				y_position--;
				last_direction = 1;
			}
            
            //todo:: fix combat on monsters
            /*if(internal_animation_timer > 1)
			{
				internal_animation_timer = 0;
				doCombat(game);
			}*/
		}
	}
}

void Monster::doCombat(GameState* game) //If player is within range of Monster then reduce the main character health
{
	if(abs(game->mainCharacter->x_position - x_position) + abs(game->mainCharacter->y_position - y_position) < 50)
	{
		game->mainCharacter->reduceHealth(offencePotential);
	}
}

void Monster::killed(GameState* game) //When killed drop a random item
{
    if(game->mainCharacter->selected_weapon == -1) { //Checks if the player already has a weapon equipped
        switch(rand() % 3)
        {
            case 0:
                game->currentLevel->levelMapItems[(x_position+25)/50][(y_position+25)/50] = Items::fishItem;
                break;
            case 1:
                game->currentLevel->levelMapItems[(x_position+25)/50][(y_position+25)/50] = Items::potionItem;
                break;
            case 2:
                game->currentLevel->levelMapItems[(x_position+25)/50][(y_position+25)/50] = Items::swordItem;
                break;
        }
	}
    else
    {
        switch(rand() % 2)
        {
            case 0:
                game->currentLevel->levelMapItems[(x_position+25)/50][(y_position+25)/50] = Items::fishItem;
                break;
            case 1:
                game->currentLevel->levelMapItems[(x_position+25)/50][(y_position+25)/50] = Items::potionItem;
                break;
        }
	}


	health = 0;
	x_position = 0;
	y_position = 0;
	spawned = false;
	inCombat = false;

	game->mainCharacter->experience ++;

	game->currentLevel->monsterCount--;

}

void Monster::reduceHealth(int maxReduction, GameState* game)
{
	health -= rand() % maxReduction;
	if(health <= 0)
	{
		killed(game);
	}
}

void Monster::spawn(int ID)
{
	if(ID == 1)
	{
		spawned = true;
		health = 100;
		max_health = 100;
		loadImages(1);
		offencePotential = 10;
		inCombat = false;
	}
	if(ID == 2)
	{
		spawned = true;
		health = 150;
		max_health = 150;
		loadImages(2);
		offencePotential = 20;
		inCombat = false;
	}
}
