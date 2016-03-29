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
        
    mainFont = al_load_font("PTS75F.ttf", 16, 0);
    
    hp_green = al_load_bitmap("hp_green.bmp");
    hp_red = al_load_bitmap("hp_red.bmp");
    portal = al_load_bitmap("portal.bmp");
    al_convert_mask_to_alpha(portal, al_map_rgb(255, 0, 255));
    
    // Has to be performed at runtime since it requires the allegro image library to be initialised
    Items::setItems();
    MapSquares::setMapSquares();
    
    m_currentLevel = std::make_unique<GameLevel>();
    //Takes the data from a text file and stitches map, inputting player, monster and portal co-ordinates
    getCurrentLevel().loadLevel(m_currentWave, *m_player);
    
    getPlayer().getInventory().populateInventory();
}

void GameState::Cleanup() {
    al_destroy_font(mainFont);
    
    al_destroy_bitmap(hp_green);
    al_destroy_bitmap(hp_red);
    al_destroy_bitmap(portal);
}

void GameState::Pause() {
    
}
void GameState::Resume() {
    
}

void GameState::HandleEvents(GameEngine* gameEngine) {
    al_get_keyboard_state(&keyboardState);
    
    bool hasMoved = false;
    
    auto doMovement = [&hasMoved, this](int key, int altKey, Direction direction, int deltaX, int deltaY) {
        if(al_key_down(&keyboardState, key) ||
           al_key_down(&keyboardState, altKey)) {
            if(!getPlayer().isCollision(direction, getCurrentLevel().m_map))
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
        
        auto event = gameEngine->getEvent();
        
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                doCombat();
            }
            
            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                gameEngine->Quit();
            }
            
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                getPlayer().getInventory().useSelectedItem(&getPlayer());
            }
        
            if(event.keyboard.keycode == ALLEGRO_KEY_E) {
                getPlayer().getInventory().moveSelectorRight();
            }
            
            if(event.keyboard.keycode == ALLEGRO_KEY_Q) {
                getPlayer().getInventory().moveSelectorLeft();
            }
            
            
            if(event.keyboard.keycode == ALLEGRO_KEY_P) {
                getPlayer().getInventory().dropSelectedItem(this);
            }

            
            if(event.keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
                
                Player& player = getPlayer();
                
                auto it = std::begin(getCurrentLevel().m_mapItems);
                
                while (it != std::end(getCurrentLevel().m_mapItems))
                {
                    if (it->second.x == (player.getX() + 15) / 50
                        && it->second.y == (player.getY() + 20) / 50)
                    {
                        player.getInventory().addToInventory(it->first);
                        getCurrentLevel().m_mapItems.erase(it);
                        // only pick up one item
                        break;
                    }
                    ++it;
                }
                
                // Level finished if there are no monsters left
                if(getCurrentLevel().getMonsterCount() == 0) {
                    if(abs(player.getX() - getCurrentLevel().getPortalX())
                       + abs(player.getY() - getCurrentLevel().getPortalY()) < 30)
                    {
                        m_currentWave++;
                        
                        //When the user reaches the end of wave 10, display congratulations message
                        if(m_currentWave == 11)
                        {
                            gameEngine->ChangeState(std::make_unique<MenuState>());
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
    
    const auto& monsters = getCurrentLevel().m_monsters;
    
    for (auto &monster : monsters) {
        if(monster->isSpawned())
        {
            monster->handleMovement(this);
            monster->handleCombat(this);
            monster->updateAnimation();
        }
    }
    
    if (getPlayer().isDead()) {
        gameEngine->ChangeState(std::make_unique<MenuState>());
    }
}

void GameState::Draw(GameEngine* gameEngine) {
    
    al_set_target_bitmap(getCurrentLevel().m_monsterOverlay);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
    const int screenWidth = gameEngine->m_screenWidth;
    const int screenHeight = gameEngine->m_screenHeight;
    
    // Draws the empty_content_map to the monster_overlay where the monsters will be added: only a segment (the visible screen) will be drawn
    
    al_draw_bitmap_region(getCurrentLevel().m_emptyContentMap,
                          getPlayer().getX() - screenWidth / 2,
                          getPlayer().getY() - screenHeight / 2,
                          screenWidth,
                          screenHeight,
                          getPlayer().getX() - screenWidth / 2,
                          getPlayer().getY() - screenHeight / 2,
                          0);
    
    for (auto &itemCoordPair : getCurrentLevel().m_mapItems)
    {
        al_draw_bitmap(itemCoordPair.first->getImage(),
                       itemCoordPair.second.x * 50,
                       itemCoordPair.second.y * 50,
                       0);
    }
    
    double ratio;
    
    for (auto &monster : getCurrentLevel().m_monsters)
    {
        if(monster->isSpawned())
        {
            al_draw_bitmap(monster->getImage(),
                           monster->getX(),
                           monster->getY(),
                           0);
            
            al_draw_bitmap(hp_red,
                           monster->getX(),
                           monster->getY(),
                           0);
            
            ratio = ((double)monster->getHealth() / monster->getMaxHealth());
            al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, monster->getX(), monster->getY(), ratio * 44, 6, 0);
        }
    }
    
    al_draw_bitmap(hp_red, getPlayer().getX()-10, getPlayer().getY()-10, 0);
    ratio = ((double)getPlayer().getHealth() / getPlayer().getMaxHealth());
    al_draw_scaled_bitmap(hp_green, 0, 0, 44, 6, getPlayer().getX()-10, getPlayer().getY()-10, ratio * 44, 6, 0);
    
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
    // Draw the overlay to the buffer
	al_draw_bitmap(getCurrentLevel().m_monsterOverlay,
                   screenWidth / 2 - 15 - getPlayer().getX(),
                   screenHeight / 2 - 20 - getPlayer().getY(),
                   0);
    
    // If there are no monsters left, issue a message and show the portal
	if(getCurrentLevel().getMonsterCount() == 0)
	{
        al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 35, 0, "Wave complete! Enter the portal to move on.");
		al_draw_bitmap(portal,
                       screenWidth / 2 - 15 - getPlayer().getX() + getCurrentLevel().getPortalX(),
                       screenHeight / 2 - 20 - getPlayer().getY() + getCurrentLevel().getPortalY(), 0);
	}
    
    // Draw the player
	al_draw_bitmap(getPlayer().getImage(),
                   screenWidth / 2 - 25,
                   screenHeight / 2 - 25,
                   0);
    
	al_draw_text(mainFont, al_map_rgb(255, 255, 255), 20, 20, 0, "Kill all the monsters to go to the next wave!");
    
    // Draw inventory
	getPlayer().getInventory().drawInventory(gameEngine, getPlayer().getSelectedWeapon(), mainFont);
    
    al_set_target_backbuffer(gameEngine->display);
    
    al_draw_bitmap(getPlayer().getInventory().getDrawnInventory(),
                   0,
                   screenHeight - 150,
                   0);
    
	al_flip_display();
    
    
    if(getPlayer().isDead())
    {
        //Display death message on death
        gameEngine->PushState(std::make_unique<MenuState>());
    }

}


// Called when space is pressed and combat timer is a certain value
void GameState::doCombat(void)
{
    for (auto &monster : getCurrentLevel().m_monsters)
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

