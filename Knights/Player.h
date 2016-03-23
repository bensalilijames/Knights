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
    
    int getExperience() { return m_experience; }
    void addExperience(int delta) { m_experience += delta; }

	void reduceHealth(int maxReduction);
	void increaseHealth(int increment);

	bool isDead = false;

	int selected_weapon = -1;
	
    Inventory* inventory;

private:
    int m_experience = 0;
};

#endif