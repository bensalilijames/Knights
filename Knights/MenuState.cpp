#include <allegro5/allegro.h>
#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(void) {
    
}

MenuState::~MenuState(void) {
    
}

void MenuState::Init() {
    
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "Resources");
    al_change_directory(al_path_cstr(path, '/'));  // change the working directory
    al_destroy_path(path);
    
    splash = al_load_bitmap("splash_screen_space_to_continue.bmp");
    instructions = al_load_bitmap("instructions.bmp");
}
void MenuState::Cleanup() {
    al_destroy_bitmap(splash);
    al_destroy_bitmap(instructions);
}

void MenuState::Pause() {
    
}
void MenuState::Resume() {
    
}

void MenuState::HandleEvents(GameEngine* gameEngine) {
    while(gameEngine->pollEvent()) {
        if(gameEngine->getEvent().type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                if(!showInstructions) showInstructions = true;
                else gameEngine->ChangeState(std::make_unique<GameState>());
            }
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                gameEngine->Quit();
            }
        }
    }
}
void MenuState::Update(GameEngine* gameEngine) {
    
}
void MenuState::Draw(GameEngine* gameEngine) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (!showInstructions) {
        al_draw_bitmap(splash, 0, 0, 0);
        al_flip_display();
    }
    else {
        al_draw_bitmap(instructions, 0, 0, 0);
        al_flip_display();
    }
}