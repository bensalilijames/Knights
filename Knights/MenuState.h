#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "GameEngine.h"

class MenuState : public State {

public:
    
    MenuState();
    ~MenuState();
    
    void Init();
	void Cleanup();
    
	void Pause();
	void Resume();
    
	void HandleEvents(GameEngine* gameEngine);
	void Update(GameEngine* gameEngine);
	void Draw(GameEngine* gameEngine);
    
private:
    ALLEGRO_BITMAP* splash;
    ALLEGRO_BITMAP* instructions;
    
    bool showInstructions;
    
};

#endif