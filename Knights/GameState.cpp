#include "GameState.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MenuState.h"
#include "Items.h"
#include "MapSquares.h"

void GameState::Init() {
    m_player = std::make_unique<Player>();
    
    combatTimer = al_create_timer(1);
    combatEventQueue = al_create_event_queue();
    al_register_event_source(combatEventQueue, al_get_timer_event_source(combatTimer));
    al_start_timer(combatTimer);
    
    mainFont = al_load_font("PTS75F.ttf", 16, 0);
    
    hp_green = al_load_bitmap("hp_green.bmp");
    hp_red = al_load_bitmap("hp_red.bmp");
    portal = al_load_bitmap("portal.bmp");
    al_convert_mask_to_alpha(portal, al_map_rgb(255, 0, 255));
    
    Items::setItems();
    MapSquares::setMapSquares();
    
    m_currentLevel = std::make_unique<GameLevel>();
    //Takes the data from a text file and stitches map, inputting player, monster and portal co-ordinates
    getCurrentLevel().loadLevel(m_currentWave, *m_player);
    
    getPlayer().getInventory().populateInventory();
}

void GameState::Cleanup() {
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
            if(!getPlayer().isCollision(direction, getCurrentLevel().levelMap))
                getPlayer().move(deltaX, deltaY);
            if(!hasMoved)
            {
                getPlayer().updateDirection(direction);
                hasMoved = true;
            }
        }
    };
    
    doMovement(ALLEGRO_KEY_UP, ALLEGRO_KEY_W, Direction::North, 0, -1);
    doMovement(ALLEGRO_KEY_DOWN, ALLEGRO_KEY_S, Direction::South, 0, 1);
    doMovement(ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_D, Direction::East, 1, 0);
    doMovement(ALLEGRO_KEY_LEFT, ALLEGRO_KEY_A, Direction::West, -1, 0);
    
    if(!hasMoved)
    {
        getPlayer().updateDirection(Direction::None);
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
                getPlayer().getInventory().useSelectedItem(&getPlayer());
            }
        
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_E) {
                getPlayer().getInventory().moveSelectorRight();
            }
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_Q) {
                getPlayer().getInventory().moveSelectorLeft();
            }
            
            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_P) {
                getPlayer().getInventory().dropSelectedItem(this);
            }

            
            if(gameEngine->getEvent().keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
                
                if(getCurrentLevel().levelMapItems[(getPlayer().getX()+15)/50][(getPlayer().getY()+20)/50] != NULL)
				{
                    if(getPlayer().getInventory().addToInventory(getCurrentLevel().levelMapItems[(getPlayer().getX()+15)/50][(getPlayer().getY()+20)/50]))
                            //If there is, then add that item to inventory ñ this function returns 0 if no space and 1 if there is space for item
                    {
                        getCurrentLevel().levelMapItems[(getPlayer().getX()+15)/50][(getPlayer().getY()+20)/50] = NULL; //Gets rid of item from map
                    }
                }

                
                if(getCurrentLevel().getMonsterCount() == 0) {
                    if(abs(getPlayer().getX() - getCurrentLevel().getPortalX())
                       + abs(getPlayer().getY() - getCurrentLevel().getPortalY()) < 30) //Checks if user is near a portal
                    {
                        m_currentWave++;
                        
                        //When the user reaches the end of wave 10, display congratulations message
                        if(m_currentWave == 11)
                        {
                            gameEngine->ChangeState(new MenuState);
                        }
                        else {
                            m_currentLevel = std::make_unique<GameLevel>();
                            getCurrentLevel().loadLevel(m_currentWave, *m_player);
                        }
                    }

                }
            }
            
        }
    }
}

void GameState::Update(GameEngine* gameEngine) {
    getPlayer().updateAnimation();
    
    auto monsters = getCurrentLevel().monsters;
    
    for (auto &monster : monsters) {
        if(monster->isSpawned())
        {
            monster->handleMovement(this);
            monster->handleCombat(this);
            monster->updateAnimation();
        }
    }
    
    if (getPlayer().isDead()) {
        gameEngine->ChangeState(new MenuState);
    }
}

void GameState::Draw(GameEngine* gameEngine) {
    
    al_set_target_bitmap(getCurrentLevel().m_monsterOverlay);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
	al_draw_bitmap_region(getCurrentLevel().m_emptyContentMap, getPlayer().getX()-400, getPlayer().getY()-300, gameEngine->scrx, gameEngine->scry, getPlayer().getX()-400, getPlayer().getY()-300, 0); //Draws the empty_content_map to the monster_overlay where the monsters will be added ñ only a segment (the visible screen) will be drawn
    
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if(getCurrentLevel().levelMapItems[i][j] != NULL)
                al_draw_bitmap(getCurrentLevel().levelMapItems[i][j]->getImage(), 50 * i, 50 * j, 0);
        }
    }
    

    for (auto &monster : getCurrentLevel().monsters)
    {
        if((monster->getX() != 0) && (monster->getY() != 0)) //If monster is spawned draw monster and HP bars
        {
            al_draw_bitmap(monster->getImage(), monster->getX(), monster->getY(), 0);
            al_draw_bitmap(hp_red, monster->getX(), monster->getY(), 0);
            ratio = ((double)monster->getHealth() / monster->getMaxHealth());
            al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, monster->getX(), monster->getY(), ratio * 44, 6, 0);
        }
    }
    
    al_draw_bitmap(hp_red, getPlayer().getX()-10, getPlayer().getY()-10, 0);
    ratio = ((double)getPlayer().getHealth() / getPlayer().getMaxHealth());
    al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, getPlayer().getX()-10, getPlayer().getY()-10, ratio * 44, 6, 0);
    
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
    //Draw the overlay_to the buffer
	al_draw_bitmap(getCurrentLevel().m_monsterOverlay, 385-getPlayer().getX(), 280-getPlayer().getY(), 0);
    
    //If there are no monsters left, issue a message and show the portal
	if(getCurrentLevel().getMonsterCount() == 0)
	{
        al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 35, 0, "Wave complete! Enter the portal to move on.");
		al_draw_bitmap(portal, 385 - getPlayer().getX() + getCurrentLevel().getPortalX(), 280 - getPlayer().getY() + getCurrentLevel().getPortalY(), 0);
	}
    
	al_draw_bitmap(getPlayer().getImage(), (gameEngine->scrx/2)-25, (gameEngine->scry/2)-25, 0); //Draws the player to the screen
    
	al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 20, 0, "Kill all the monsters to go to the next wave!");
    
    // Draw inventory
	getPlayer().getInventory().drawInventory(gameEngine, getPlayer().getSelectedWeapon(), mainFont);
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_draw_bitmap(getPlayer().getInventory().getDrawnInventory(), 0, 450, 0);
    
	al_flip_display();
    
    
    if(getPlayer().isDead())
    {
        //Display death message on death
        gameEngine->PushState(new MenuState);
    }

}


// Called when space is pressed and combat timer is a certain value
void GameState::doCombat(void)
{
    for (auto &monster : getCurrentLevel().monsters)
    {
        if ((monster->getX() != 0) && (monster->getX() != 0))
        {
            // If monster is in range, set the monster to 'in combat' to follow the player around
            if (abs(getPlayer().getX() - monster->getX() - 10) + abs(getPlayer().getY() - monster->getY() - 5) < 60)
            {
                monster->setInCombat(true);
                monster->reduceHealth(getPlayer().getOffencePotential() + getPlayer().getExperience(), this);
            }
        }
    }
}

