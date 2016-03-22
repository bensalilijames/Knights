#ifndef CHARACTER_H
#define CHARACTER_H

#include <allegro5/allegro.h>
#include <vector>
#include "MapSquare.h"
#include "Animation.h"

class Character
{
public:
	Character(void);
	~Character(void);

	int x_position;
	int y_position;
	int last_direction;
	ALLEGRO_BITMAP* images[12];
	int internal_animation_timer;
	int offencePotential;
	int defencePotential;

	ALLEGRO_BITMAP* getImage();
	void loadImages(int initial_image);
	bool isCollision(int direction, int height, int width, std::vector<std::vector<MapSquare*>> map);
    
    Animation m_animation;
	
};

#endif