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
	void handleCombat(GameState* game);
	void killed(GameState* game);
	void spawn(CharacterType type);
    
    bool isSpawned() { return m_spawned; }
    void setInCombat(bool inCombat) { m_inCombat = inCombat; }
    
    void moveRandomly(GameState* game);
    void moveTowardsPlayer(GameState* game);
    
    virtual void onKill(GameState* game) override;
    
private:
    bool m_inCombat = false;
    bool m_spawned;
    bool m_isMoving;
    double m_timeSinceLastAttack = 0.5;
};

#endif