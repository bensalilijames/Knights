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
    
    int getExperience() { return m_experience; }
    void addExperience(int delta) { m_experience += delta; }

	int getSelectedWeapon() { return m_selectedWeapon; }
    void setSelectedWeapon(int selectedWeapon) { m_selectedWeapon = selectedWeapon; }
    
    Inventory& getInventory() { return *inventory; }

private:
    int m_experience = 0;
    int m_selectedWeapon = -1;
    
    std::unique_ptr<Inventory> inventory;
};

#endif