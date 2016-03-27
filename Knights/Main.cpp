#include "GameEngine.h"
#include "MenuState.h"

int main(int argc, char* argv[]) {
    
    GameEngine gameEngine = GameEngine::getInstance();
    
    gameEngine.PushState(new MenuState);
    
	while(gameEngine.Running())
	{
        gameEngine.HandleEvents();
        gameEngine.Update();
        gameEngine.Draw();
        
        al_wait_for_event(gameEngine.redrawQueue, NULL);
        al_flush_event_queue(gameEngine.redrawQueue);
    }
    
    gameEngine.Cleanup();
 
    return 0;
}
