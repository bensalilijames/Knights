#ifndef STATE_H
#define STATE_H

#include "GameEngine.h"

class GameEngine;

class State
{
public:
    virtual ~State() {};
    
    virtual void Init() {};
    virtual void Cleanup() {};
    
    virtual void Pause() {};
    virtual void Resume() {};
    
    virtual void HandleEvents(GameEngine* gameEngine) {};
    virtual void Update(GameEngine* gameEngine) {};
    virtual void Draw(GameEngine* gameEngine) = 0;
};

#endif