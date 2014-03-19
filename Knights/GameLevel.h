#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "MapSquare.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"

class Player;
class Monster;

class GameLevel {
public:
    GameLevel();
    ~GameLevel();
    
    void loadLevel(int level, Player* player);
    
    std::vector<std::vector<MapSquare*>> levelMap;
    std::vector<std::vector<MapSquare*>> levelMapUnderlay;
    Item* levelMapItems[50][50];
    
    std::vector<Monster*> monsters;
    
    ALLEGRO_BITMAP* empty_content_map;
    ALLEGRO_BITMAP* monster_overlay;
    
    int monsterCount;
    int portalX;
    int portalY;
    
private:
    int mapHeight;
    int mapWidth;
};

#endif