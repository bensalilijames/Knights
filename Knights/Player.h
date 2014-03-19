#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include "Character.h"
#include "Inventory.h"

class Inventory;

class Player: public Character
{
public:
	Player(void);
	~Player(void);

	void handleAnimation();
	void reduceHealth(int maxReduction);
	void increaseHealth(int increment);

	bool isDead;

	int selected_weapon;
	int is_moving;
	int health;
	int experience;
	int max_health;
    
    Inventory* inventory;
};

#endif