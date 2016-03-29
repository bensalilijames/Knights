#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "MapSquares.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"

class Player;
class Monster;

struct Coord {
    int x;
    int y;
    
    Coord(int x, int y) : x(x), y(y) {}
};

class GameLevel {
public:    
    void loadLevel(int level, Player& player);
    
    std::vector<std::vector<MapSquare*>> levelMap;
    std::vector<std::vector<MapSquare*>> levelMapUnderlay;
    std::vector<std::pair<Item*, Coord>> m_itemsMap;
    
    std::vector<Monster*> monsters;
    
    void decrementMonsterCount() { m_monsterCount--; }
    int getMonsterCount() { return m_monsterCount; }
    int getPortalX() { return m_portalX; }
    int getPortalY() { return m_portalY; }
    
    void dropItem(Item* item, int x, int y);
    
    ALLEGRO_BITMAP* m_emptyContentMap;
    ALLEGRO_BITMAP* m_monsterOverlay;
    
private:
    int m_monsterCount = 0;
    int m_portalX;
    int m_portalY;
    
    int m_mapHeight;
    int m_mapWidth;
};

#endif