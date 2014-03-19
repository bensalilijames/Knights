#include "GameEngine.h"
#include "MenuState.h"

GameEngine gameEngine; //Creates a new instance of the game

int main(int argc, char* argv[]) {
    
	gameEngine.Init(); //Sets up allegro libraries and implements drivers

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
