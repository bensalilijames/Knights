#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
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
    void Init();
	void Cleanup();
    
	void Pause();
	void Resume();
    
	void HandleEvents(GameEngine* gameEngine);
	void Update(GameEngine* gameEngine);
	void Draw(GameEngine* gameEngine);
    
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
    
    ALLEGRO_FONT *mainFont;
    
    std::unique_ptr<Player> m_player;
    
	int m_currentWave = 0;
    
	double ratio;
    
    std::unique_ptr<GameLevel> m_currentLevel;
    
    ALLEGRO_TIMER *combatTimer;
    ALLEGRO_EVENT_QUEUE *combatEventQueue;
    ALLEGRO_EVENT *combatEvent;
    
    ALLEGRO_KEYBOARD_STATE keyboardState;
};

#endif