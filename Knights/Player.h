#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include "Character.h"
#include "Inventory.h"

class Inventory;

class Player: public Character
{
public:
    Player();
    
    ~Player()
    {
        delete inventory;
    }
    
	void reduceHealth(int maxReduction);
	void increaseHealth(int increment);

	bool isDead = false;

	int selected_weapon = -1;
	int is_moving;
	int experience = 0;
	
    Inventory* inventory;
};

#endif