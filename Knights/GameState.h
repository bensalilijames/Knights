#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <allegro5/allegro.h>
#include "Monster.h"
#include "Player.h"
#include "MapSquares.h"
#include "Inventory.h"
#include "Item.h"
#include <vector>
#include "GameLevel.h"

class Monster;
class GameLevel;
class Player;

class GameState : public State
{
public:
    virtual void Init() override;
	virtual void Cleanup() override;
    
	virtual void HandleEvents(GameEngine* gameEngine) override;
	virtual void Update(GameEngine* gameEngine) override;
	virtual void Draw(GameEngine* gameEngine) override;
    
    void createMonsters(void);
    void drawScreen(void);
    void createMap(void);
    void createItems(void);
    void doCombat(void);
    void loadExternalData(void);
    
    Player& getPlayer() { return *m_player; }
    GameLevel& getCurrentLevel() { return *m_currentLevel; }
    
private:
    ALLEGRO_BITMAP *hp_red;
    ALLEGRO_BITMAP *hp_green;
    ALLEGRO_BITMAP *portal;
    
    std::unique_ptr<Player> m_player;
    
	int m_currentWave = 1;
    
	std::unique_ptr<GameLevel> m_currentLevel;
    
    ALLEGRO_KEYBOARD_STATE keyboardState;
};

#endif