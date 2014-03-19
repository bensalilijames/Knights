#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"
#include <vector>
#include "GameState.h"

class GameState;

class Monster: public Character
{
public:
	Monster(void);
	~Monster(void);

	int collision[4];
	bool isMoving;
	bool inCombat;
	bool spawned;
	int health;
	int max_health;

	void handleMovement(GameState* game);
	void doCombat(GameState* game);
	void killed(GameState* game);
	void reduceHealth(int maxReduction, GameState* game);
	void spawn(int ID);
};

#endif