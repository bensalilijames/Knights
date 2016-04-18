#include <allegro5/allegro.h>
#include "MenuState.h"
#include "GameState.h"

void MenuState::Init() {
    m_splashUI = std::make_unique<ImageUIElement>("splash_screen_space_to_continue.bmp");
    m_instructionsUI = std::make_unique<ImageUIElement>("instructions.bmp");
}

void MenuState::HandleEvents(GameEngine* gameEngine)
{
    while(gameEngine->pollEvent())
    {
        if(gameEngine->getEvent().type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                if(!showInstructions)
                {
                    showInstructions = true;
                }
                else
                {
                    gameEngine->ChangeState(std::make_unique<GameState>());
                }
            }
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                gameEngine->Quit();
            }
        }
    }
}

void MenuState::Draw(GameEngine* gameEngine) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (!showInstructions)
    {
        m_splashUI->DrawToScreen();
    }
    else
    {
        m_instructionsUI->DrawToScreen();
    }
}