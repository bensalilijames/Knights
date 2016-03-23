#ifndef CHARACTER_H
#define CHARACTER_H

#include <allegro5/allegro.h>
#include <vector>
#include "MapSquares.h"
#include "Animation.h"

enum Direction
{
    None,
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};

class Character
{
public:
    ALLEGRO_BITMAP* getImage();
    void loadImages(int initial_image);
    bool isCollision(Direction direction, std::vector<std::vector<MapSquare*>> map);
    
    void createAnimation(const std::vector<const char*> paths);
    void setActiveAnimation(int animationId);
    void updateAnimation();
    
    void modifyOffencePotential(int delta);
    
    int getX() { return m_x; }
    int getY() { return m_y; }
    int getHealth() { return m_health; }
    int getMaxHealth() { return m_maxHealth; }
    int getOffencePotential() { return m_offencePotential; }
    
    void move(int x, int y);
    void setPosition(int x, int y);
    
    void updateDirection(Direction direction);
    
protected:
	int m_x;
	int m_y;
	Direction m_lastDirection = None;
    Direction m_currentDirection = South;

    int m_offencePotential;
	int m_defencePotential;
    int m_health;
    int m_maxHealth;
    
    int m_height;
    int m_width;

private:
    Animation m_currentAnimation;
    std::vector<Animation> m_animations;
};

#endif