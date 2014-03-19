#include "Character.h"

Character::Character(void)
{
}


Character::~Character(void)
{
}

void Character::loadImages(int initial_image) //Loads the relevant images based on the ID of the Character
{
	if(initial_image == 0)
	{
		images[0] = al_load_bitmap("manU.bmp");
		images[1] = al_load_bitmap("manU2.bmp");
		images[2] = al_load_bitmap("manU3.bmp");
		images[3] = al_load_bitmap("manR.bmp");
		images[4] = al_load_bitmap("manR2.bmp");
		images[5] = al_load_bitmap("manR3.bmp");
		images[6] = al_load_bitmap("manD.bmp");
		images[7] = al_load_bitmap("manD2.bmp");
		images[8] = al_load_bitmap("manD3.bmp");
		images[9] = al_load_bitmap("manL.bmp");
		images[10] = al_load_bitmap("manL2.bmp");
		images[11] = al_load_bitmap("manL3.bmp");
        
	}
	else if(initial_image == 1)
	{
		images[0] = al_load_bitmap("froggyU.bmp");
		images[1] = al_load_bitmap("froggyU.bmp");
		images[2] = al_load_bitmap("froggyU.bmp");
		images[3] = al_load_bitmap("froggyR.bmp");
		images[4] = al_load_bitmap("froggyR.bmp");
		images[5] = al_load_bitmap("froggyR.bmp");
		images[6] = al_load_bitmap("froggyD.bmp");
		images[7] = al_load_bitmap("froggyD.bmp");
		images[8] = al_load_bitmap("froggyD.bmp");
		images[9] = al_load_bitmap("froggyL.bmp");
		images[10] = al_load_bitmap("froggyL.bmp");
		images[11] = al_load_bitmap("froggyL.bmp");
	}
	else if(initial_image == 2)
	{
		images[0] = al_load_bitmap("globbyU.bmp");
		images[1] = al_load_bitmap("globbyU.bmp");
		images[2] = al_load_bitmap("globbyU.bmp");
		images[3] = al_load_bitmap("globbyR.bmp");
		images[4] = al_load_bitmap("globbyR.bmp");
		images[5] = al_load_bitmap("globbyR.bmp");
		images[6] = al_load_bitmap("globbyD.bmp");
		images[7] = al_load_bitmap("globbyD.bmp");
		images[8] = al_load_bitmap("globbyD.bmp");
		images[9] = al_load_bitmap("globbyL.bmp");
		images[10] = al_load_bitmap("globbyL.bmp");
		images[11] = al_load_bitmap("globbyL.bmp");
	}
    
    for (int i = 0; i <= 11; i++) {
        al_convert_mask_to_alpha(images[i], al_map_rgb(255, 0, 255));
    }
}

ALLEGRO_BITMAP* Character::getImage() //Returns an image based on the animation_timer and the direction in which the player is moving
{
	if(last_direction == 1 || last_direction == 2)
	{
		if(internal_animation_timer/25 < 1)
		{
			return images[0];
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return images[1];
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return images[0];
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return images[2];
		}
	}
	if(last_direction == 3 || last_direction == 4)
	{
		if(internal_animation_timer/25 < 1)
		{
			return images[3];
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return images[4];
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return images[3];
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return images[5];
		}
	}
	if(last_direction == 5 || last_direction == 6)
	{
		if(internal_animation_timer/25 < 1)
		{
			return images[6];
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return images[7];
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return images[6];
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return images[8];
		}
	}
	if(last_direction == 7 || last_direction == 8)
	{
		if(internal_animation_timer/25 < 1)
		{
			return images[9];
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return images[10];
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return images[9];
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return images[11];
		}
	}
	
	return images[6];
	

}

bool Character::isCollision(int direction, int height, int width, std::vector<std::vector<MapSquare*>> map) //Checks if the player collides with a square which has no collision on
{
    if(direction != 1 && direction != 3 && direction != 5 && direction != 7) {
        return false;
    }
    
    int collision[4];
    
	if(direction == 1) //UP
	{
		collision[0] = (x_position) / 50; //Sets up the x_position and y_position to check for collision
		collision[1] = (y_position - 1) / 50;

		collision[2] = (x_position + width) / 50;
		collision[3] = (y_position - 1) / 50;

	}

	if(direction == 5) //DOWN
	{
		collision[0] = (x_position) / 50;
		collision[1] = (y_position + height + 1) / 50;

		collision[2] = (x_position + width) / 50;
		collision[3] = (y_position + height + 1) / 50;
        
	}

	if(direction == 3) //RIGHT
	{
		collision[0] = (x_position + width + 1) / 50;
		collision[1] = (y_position) / 50;

		collision[2] = (x_position + width + 1) / 50;
		collision[3] = (y_position + height) / 50;

	}

	if(direction == 7) //LEFT
	{
		collision[0] = (x_position - 1) / 50;
		collision[1] = (y_position) / 50;

		collision[2] = (x_position - 1) / 50;
		collision[3] = (y_position + height) / 50;

	}

    if (map[collision[1]][collision[0]]->collisionInvalid == true || map[collision[3]][collision[2]]->collisionInvalid == true) {
        return true;
    }
    
	return false;
}
