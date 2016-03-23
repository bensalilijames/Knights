#include "GameState.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MenuState.h"
#include "Items.h"
#include "MapSquares.h"

GameState::GameState() {
    
}

GameState::~GameState(void) {
    
}

void GameState::Init() {
    mainCharacter = new Player();
    
    combatTimer = al_create_timer(1);
    combatEventQueue = al_create_event_queue();
    al_register_event_source(combatEventQueue, al_get_timer_event_source(combatTimer));
    al_start_timer(combatTimer);
    
    mainFont = al_load_font("PTS75F.ttf", 16, 0);
    
    hp_green = al_load_bitmap("hp_green.bmp");
    hp_red = al_load_bitmap("hp_red.bmp");
    portal = al_load_bitmap("portal.bmp");
    al_convert_mask_to_alpha(portal, al_map_rgb(255, 0, 255));
    
    Items::setItems(); //Initialises the items ñ sets up images, weapon damage, healing potential
    MapSquares::setMapSquares(); //Initialises the map squares ñ sets up images
    
    currentWave = 0;
    currentLevel = new GameLevel();
    currentLevel->loadLevel(currentWave, mainCharacter); //Procedure that takes the data from a text file and stitches map, inputting player, monster and portal co-ordinates
    
    mainCharacter->inventory->populateInventory();
}
void GameState::Cleanup() {
    delete mainCharacter;
    
    al_destroy_font(mainFont);
    
    al_destroy_timer(combatTimer);
    al_destroy_event_queue(combatEventQueue);
    
    al_destroy_bitmap(hp_green);
    al_destroy_bitmap(hp_red);
    al_destroy_bitmap(portal);
}

void GameState::Pause() {
    
}
void GameState::Resume() {
    
}

void GameState::HandleEvents(GameEngine* gameEngine) {
    if(al_is_event_queue_empty(combatEventQueue)) {
        al_stop_timer(combatTimer);
        al_flush_event_queue(combatEventQueue);
    }
    
    al_get_keyboard_state(&keyboardState);
    
    bool hasMoved = false;
    
    auto doMovement = [&hasMoved, this](int key, int altKey, Direction direction, int deltaX, int deltaY) {
        if(al_key_down(&keyboardState, key) ||
           al_key_down(&keyboardState, altKey)) {
            if(!mainCharacter->isCollision(direction, currentLevel->levelMap))
                mainCharacter->move(deltaX, deltaY);
            if(!hasMoved)
            {
                mainCharacter->updateDirection(direction);
                hasMoved = true;
            }
        }
    };
    
    doMovement(ALLEGRO_KEY_UP, ALLEGRO_KEY_W, North, 0, -1);
    doMovement(ALLEGRO_KEY_DOWN, ALLEGRO_KEY_S, South, 0, 1);
    doMovement(ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_D, East, 1, 0);
    doMovement(ALLEGRO_KEY_LEFT, ALLEGRO_KEY_A, West, -1, 0);
    
    if(!hasMoved)
    {
        mainCharacter->updateDirection(None);
    }
    
    while(gameEngine->pollEvent()) {
        
        if(gameEngine->getEvent().type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                doCombat();
            }
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                gameEngine->Quit();
            }
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                mainCharacter->inventory->useSelectedItem(mainCharacter);
            }
        
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_E) {
                mainCharacter->inventory->moveSelectorRight();
            }
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_Q) {
                mainCharacter->inventory->moveSelectorLeft();
            }
            
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_P) {
                mainCharacter->inventory->dropSelectedItem(this);
            }

            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
                
                if(currentLevel->levelMapItems[(mainCharacter->getX()+15)/50][(mainCharacter->getY()+20)/50] != NULL)
				{
                    if(mainCharacter->inventory->addToInventory(currentLevel->levelMapItems[(mainCharacter->getX()+15)/50][(mainCharacter->getY()+20)/50]))
                            //If there is, then add that item to inventory ñ this function returns 0 if no space and 1 if there is space for item
                    {
                        currentLevel->levelMapItems[(mainCharacter->getX()+15)/50][(mainCharacter->getY()+20)/50] = NULL; //Gets rid of item from map
                    }
                }

                
                if(currentLevel->monsterCount == 0) {
                    if(abs(mainCharacter->getX() - currentLevel->portalX) + abs(mainCharacter->getY() - currentLevel->portalY) < 30) //Checks if user is near a portal
                    {
                        currentWave++;  //Goes to the next level
                        delete currentLevel;  //Loads up all the data for the next level
                        
                        if(currentWave == 11) //When the user reaches the end of wave 10, display congratulations message
                        {
                            gameEngine->ChangeState(new MenuState);
                        }
                        else {
                            currentLevel = new GameLevel();
                            currentLevel->loadLevel(currentWave, mainCharacter);
                        }
                    }

                }
            }
            
        }
    }
}

void GameState::Update(GameEngine* gameEngine) {
    mainCharacter->updateAnimation();
    
    auto monsters = currentLevel->monsters;
    
    for (auto &monster : monsters) {
        if(monster->isSpawned())
        {
            monster->handleMovement(this);
            monster->handleCombat(this);
            monster->updateAnimation();
        }
    }
    
    if (mainCharacter->isDead) {
        gameEngine->ChangeState(new MenuState);
    }
}

void GameState::Draw(GameEngine* gameEngine) {
    
    al_set_target_bitmap(currentLevel->monster_overlay);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
	al_draw_bitmap_region(currentLevel->empty_content_map, mainCharacter->getX()-400, mainCharacter->getY()-300, gameEngine->scrx, gameEngine->scry, mainCharacter->getX()-400, mainCharacter->getY()-300, 0); //Draws the empty_content_map to the monster_overlay where the monsters will be added ñ only a segment (the visible screen) will be drawn
    
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if(currentLevel->levelMapItems[i][j] != NULL)
                al_draw_bitmap(currentLevel->levelMapItems[i][j]->getImage(), 50 * i, 50 * j, 0);
        }
    }
    

    for (auto &monster : currentLevel->monsters)
    {
        if((monster->getX() != 0) && (monster->getY() != 0)) //If monster is spawned draw monster and HP bars
        {
            al_draw_bitmap(monster->getImage(), monster->getX(), monster->getY(), 0);
            al_draw_bitmap(hp_red, monster->getX(), monster->getY(), 0);
            ratio = ((double)monster->getHealth() / monster->getMaxHealth());
            al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, monster->getX(), monster->getY(), ratio * 44, 6, 0);
        }
    }
    
    al_draw_bitmap(hp_red, mainCharacter->getX()-10, mainCharacter->getY()-10, 0);
    ratio = ((double)mainCharacter->getHealth() / mainCharacter->getMaxHealth());
    al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, mainCharacter->getX()-10, mainCharacter->getY()-10, ratio * 44, 6, 0);
    
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
	al_draw_bitmap(currentLevel->monster_overlay, 385-mainCharacter->getX(), 280-mainCharacter->getY(), 0); //Draw the overlay_to the buffer
    
	if(currentLevel->monsterCount == 0) //If there are no monsters left, issue a message and show the portal
	{
        al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 35, 0, "Wave complete! Enter the portal to move on.");
		al_draw_bitmap(portal, 385 - mainCharacter->getX() + currentLevel->portalX, 280 - mainCharacter->getY() + currentLevel->portalY, 0);
	}
    
	al_draw_bitmap(mainCharacter->getImage(), (gameEngine->scrx/2)-25, (gameEngine->scry/2)-25, 0); //Draws the player to the screen
    
	al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 20, 0, "Kill all the monsters to go to the next wave!");
    
	mainCharacter->inventory->drawInventory(gameEngine, mainCharacter->selected_weapon, mainFont); //Draws the inventory based on a method in inventory class
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_draw_bitmap(mainCharacter->inventory->getDrawnInventory(), 0, 450, 0);
    
	al_flip_display();
    
    
    if(mainCharacter->isDead) //Display death message on death
    {
        gameEngine->PushState(new MenuState);
    }

}


// Called when space is pressed and combat timer is a certain value
void GameState::doCombat(void)
{
    for (auto &monster : currentLevel->monsters)
    {
        if ((monster->getX() != 0) && (monster->getX() != 0))
        {
            // If monster is in range, set the monster to 'in combat' to follow the player around
            if (abs(mainCharacter->getX() - monster->getX() - 10) + abs(mainCharacter->getY() - monster->getY() - 5) < 60)
            {
                monster->setInCombat(true);
                monster->reduceHealth(mainCharacter->getOffencePotential() + mainCharacter->getExperience(), this);
            }
        }
    }
}

