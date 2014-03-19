#ifndef STATE_H
#define STATE_H

#include "GameEngine.h"

class GameEngine;

class State
{
public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;
    
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    
    virtual void HandleEvents(GameEngine* gameEngine) = 0;
    virtual void Update(GameEngine* gameEngine) = 0;
    virtual void Draw(GameEngine* gameEngine) = 0;
        
protected: State() { }
};

#endif