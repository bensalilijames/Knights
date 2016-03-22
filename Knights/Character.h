#ifndef CHARACTER_H
#define CHARACTER_H

#include <allegro5/allegro.h>
#include <vector>
#include "MapSquare.h"
#include "Animation.h"

class Character
{
public:
	int x_position;
	int y_position;
	int last_direction = 0;
    int current_direction = 0;
	ALLEGRO_BITMAP* images[12];
	int offencePotential;
	int defencePotential;

    int health;
    int max_health;
    
	ALLEGRO_BITMAP* getImage();
	void loadImages(int initial_image);
	bool isCollision(int direction, int height, int width, std::vector<std::vector<MapSquare*>> map);
    
    Animation m_currentAnimation;
    std::vector<Animation> m_animations;
    
    void createAnimation(const std::vector<const char*> paths);
    void setActiveAnimation(int animationId);
    void updateAnimation();
};

#endif