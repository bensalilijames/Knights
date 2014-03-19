#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <allegro5/allegro.h>
#include <vector>
#include "State.h"

class State;

class GameEngine
{
public:
    void Init();
    void Cleanup();
    
    void ChangeState(State* state);
    void PushState(State* state);
    void PopState();
    
    void HandleEvents();
    void Update();
    void Draw();
    
    bool Running() { return running; }
    void Quit() { running = false; }
    
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT_QUEUE *redrawQueue;

    bool pollEvent() { return al_get_next_event(eventQueue, &event); }
    ALLEGRO_EVENT getEvent() { return event; }
    void WaitForEvent() { al_wait_for_event(eventQueue, &event); }
    
    ALLEGRO_DISPLAY *display;
    
    const int scrx = 800;
    const int scry = 600;
    
private:
    std::vector<State*> states;
    
    bool running;
    
    const float FPS = 120.0f;
    
    ALLEGRO_TIMER *redrawTimer;
    
};

#endif