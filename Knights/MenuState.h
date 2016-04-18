#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "GameEngine.h"
#include "UI.hpp"

class MenuState : public State {

public:
    virtual ~MenuState() {};
    
    virtual void Init() override;
    
	virtual void HandleEvents(GameEngine* gameEngine) override;
    virtual void Draw(GameEngine* gameEngine) override;
    
private:
    ImageUIElementPtr m_splashUI;
    ImageUIElementPtr m_instructionsUI;
    
    bool showInstructions;
};

#endif