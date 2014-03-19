#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include "Monster.h"
#include "Player.h"
#include "MapSquare.h"
#include "Inventory.h"
#include "Item.h"
#include <vector>
#include "GameLevel.h"

class Monster;
class Player;
class GameLevel;

class GameState : public State
{
public:
    GameState(void);
    ~GameState(void);
    
    void Init();
	void Cleanup();
    
	void Pause();
	void Resume();
    
	void HandleEvents(GameEngine* gameEngine);
	void Update(GameEngine* gameEngine);
	void Draw(GameEngine* gameEngine);
    
    ALLEGRO_BITMAP *hp_red;
    ALLEGRO_BITMAP *hp_green;
    ALLEGRO_BITMAP *portal;
    
    ALLEGRO_FONT *mainFont;
    
	Player* mainCharacter;
    
	int currentWave;
    
	double ratio;
    
	void createMonsters(void);
	void drawScreen(void);
	void createMap(void);
	void createItems(void);
	void doCombat(void);
	void loadExternalData(void);
    
    GameLevel* currentLevel;
    
    ALLEGRO_TIMER *combatTimer;
    ALLEGRO_EVENT_QUEUE *combatEventQueue;
    ALLEGRO_EVENT *combatEvent;
    
    ALLEGRO_KEYBOARD_STATE keyboardState;
};

#endif