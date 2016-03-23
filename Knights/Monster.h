#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include <vector>
#include "GameState.h"

class GameState;

class Monster: public Character
{
public:
	void handleMovement(GameState* game);
	void doCombat(GameState* game);
	void killed(GameState* game);
	void reduceHealth(int maxReduction, GameState* game);
	void spawn(int ID);
    
    bool isSpawned() { return m_spawned; }
    void setInCombat(bool inCombat) { m_inCombat = inCombat; }
    
private:
    bool m_inCombat = false;
    bool m_spawned;
    bool m_isMoving;
};

#endif