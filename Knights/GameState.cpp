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
    
    mainCharacter->is_moving = false;
    
    al_get_keyboard_state(&keyboardState);
    if(al_key_down(&keyboardState, ALLEGRO_KEY_UP) ||
       al_key_down(&keyboardState, ALLEGRO_KEY_W)) {
        if(!mainCharacter->isCollision(1,40,30,currentLevel->levelMap))
            mainCharacter->y_position --;
        mainCharacter->last_direction = 1;
        mainCharacter->is_moving = true;
    }
    if(al_key_down(&keyboardState, ALLEGRO_KEY_DOWN) ||
       al_key_down(&keyboardState, ALLEGRO_KEY_S)) {
        if(!mainCharacter->isCollision(5,40,30,currentLevel->levelMap))
            mainCharacter->y_position ++;
        mainCharacter->last_direction = 5;
        mainCharacter->is_moving = true;
    }
    if(al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT) ||
       al_key_down(&keyboardState, ALLEGRO_KEY_D)) {
        if(!mainCharacter->isCollision(3,40,30,currentLevel->levelMap))
            mainCharacter->x_position ++;
        mainCharacter->last_direction = 3;
        mainCharacter->is_moving = true;
    }
    if(al_key_down(&keyboardState, ALLEGRO_KEY_LEFT) ||
       al_key_down(&keyboardState, ALLEGRO_KEY_A)) {
        if(!mainCharacter->isCollision(7,40,30,currentLevel->levelMap))
            mainCharacter->x_position --;
        mainCharacter->last_direction = 7;
        mainCharacter->is_moving = true;
    }
    if(mainCharacter->is_moving) mainCharacter->internal_animation_timer++;
    
    while(gameEngine->pollEvent()) {
        
        if(gameEngine->getEvent().type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                //if(!al_get_timer_started(combatTimer)) {
                    doCombat();
                //    al_start_timer(combatTimer);
                //}
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
                
                
                if(currentLevel->levelMapItems[(mainCharacter->x_position+15)/50][(mainCharacter->y_position+20)/50] != NULL)
				{
                    if(mainCharacter->inventory->addToInventory(currentLevel->levelMapItems[(mainCharacter->x_position+15)/50][(mainCharacter->y_position+20)/50]))
                            //If there is, then add that item to inventory ñ this function returns 0 if no space and 1 if there is space for item
                    {
                        currentLevel->levelMapItems[(mainCharacter->x_position+15)/50][(mainCharacter->y_position+20)/50] = NULL; //Gets rid of item from map
                    }
                }

                
                if(currentLevel->monsterCount == 0) {
                    if(abs(mainCharacter->x_position - currentLevel->portalX) + abs(mainCharacter->y_position - currentLevel->portalY) < 30) //Checks if user is near a portal
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
    mainCharacter->handleAnimation(); //Causes playerís sprite to change while they move
    mainCharacter->is_moving = false;
    
    for (std::vector<Monster*>::iterator itMonster = currentLevel->monsters.begin() ; itMonster != currentLevel->monsters.end(); ++itMonster) {
        if((*itMonster)->spawned == true)
        {
            (*itMonster)->handleMovement(this);
        }
    }
    
    if (mainCharacter->isDead) {
        gameEngine->ChangeState(new MenuState);
    }
}

void GameState::Draw(GameEngine* gameEngine) {
    
    al_set_target_bitmap(currentLevel->monster_overlay);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
	al_draw_bitmap_region(currentLevel->empty_content_map, mainCharacter->x_position-400, mainCharacter->y_position-300, gameEngine->scrx, gameEngine->scry, mainCharacter->x_position-400, mainCharacter->y_position-300, 0); //Draws the empty_content_map to the monster_overlay where the monsters will be added ñ only a segment (the visible screen) will be drawn
    
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if(currentLevel->levelMapItems[i][j] != NULL)
                al_draw_bitmap(currentLevel->levelMapItems[i][j]->getImage(), 50 * i, 50 * j, 0);
        }
    }
    

    for (std::vector<Monster*>::iterator itMonster = currentLevel->monsters.begin() ; itMonster != currentLevel->monsters.end(); ++itMonster) {
        if(((*itMonster)->x_position != 0) && ((*itMonster)->y_position != 0)) //If monster is spawned draw monster and HP bars
		{
			al_draw_bitmap((*itMonster)->getImage(), (*itMonster)->x_position, (*itMonster)->y_position, 0);
            al_draw_bitmap(hp_red, (*itMonster)->x_position, (*itMonster)->y_position, 0);
            ratio = ((double)(*itMonster)->health / (*itMonster)->max_health);
            al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, (*itMonster)->x_position, (*itMonster)->y_position, ratio * 44, 6, 0);
		}
    }
    
    al_draw_bitmap(hp_red, mainCharacter->x_position-10, mainCharacter->y_position-10, 0);
    ratio = ((double)mainCharacter->health / mainCharacter->max_health);
    al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, mainCharacter->x_position-10, mainCharacter->y_position-10, ratio * 44, 6, 0);
    
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
	al_draw_bitmap(currentLevel->monster_overlay, 385-mainCharacter->x_position, 280-mainCharacter->y_position, 0); //Draw the overlay_to the buffer
    
	if(currentLevel->monsterCount == 0) //If there are no monsters left, issue a message and show the portal
	{
        al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 35, 0, "Wave complete! Enter the portal to move on.");
		al_draw_bitmap(portal, 385 - mainCharacter->x_position + currentLevel->portalX, 280 - mainCharacter->y_position + currentLevel->portalY, 0);
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





void GameState::doCombat(void) //Called when space is pressed and when combat timer is a certain value ñ checks if monster is nearby and reduces their health if there is
{
    
    
    for (std::vector<Monster*>::iterator itMonster = currentLevel->monsters.begin() ; itMonster != currentLevel->monsters.end(); ++itMonster) {
        if(((*itMonster)->x_position != 0) && ((*itMonster)->y_position != 0)) //If monster is spawned draw monster and HP bars
		{
            if(abs(mainCharacter->x_position - (*itMonster)->x_position - 10) + abs(mainCharacter->y_position - (*itMonster)->y_position - 5) < 60) //Checks if within range
            {
                (*itMonster)->inCombat = true; //Sets monster to combat mode so will follow player around
                (*itMonster)->reduceHealth(mainCharacter->offencePotential + mainCharacter->experience, this);
            }
		}
    }
}

