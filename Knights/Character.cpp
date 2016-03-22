#include "Character.h"

Character::Character(void)
{
}


Character::~Character(void)
{
}

void Character::loadImages(int initial_image) //Loads the relevant images based on the ID of the Character
{
    Animation animation;
    
	if(initial_image == 0)
	{
        animation.addFrame("manU.bmp");
		animation.addFrame("manU2.bmp");
		animation.addFrame("manU3.bmp");
		animation.addFrame("manR.bmp");
		animation.addFrame("manR2.bmp");
		animation.addFrame("manR3.bmp");
		animation.addFrame("manD.bmp");
		animation.addFrame("manD2.bmp");
		animation.addFrame("manD3.bmp");
		animation.addFrame("manL.bmp");
		animation.addFrame("manL2.bmp");
		animation.addFrame("manL3.bmp");
	}
	else if(initial_image == 1)
	{
		animation.addFrame("froggyU.bmp");
		animation.addFrame("froggyU.bmp");
		animation.addFrame("froggyU.bmp");
		animation.addFrame("froggyR.bmp");
		animation.addFrame("froggyR.bmp");
		animation.addFrame("froggyR.bmp");
		animation.addFrame("froggyD.bmp");
		animation.addFrame("froggyD.bmp");
		animation.addFrame("froggyD.bmp");
		animation.addFrame("froggyL.bmp");
		animation.addFrame("froggyL.bmp");
		animation.addFrame("froggyL.bmp");
	}
	else if(initial_image == 2)
	{
		animation.addFrame("globbyU.bmp");
		animation.addFrame("globbyU.bmp");
		animation.addFrame("globbyU.bmp");
		animation.addFrame("globbyR.bmp");
		animation.addFrame("globbyR.bmp");
		animation.addFrame("globbyR.bmp");
		animation.addFrame("globbyD.bmp");
		animation.addFrame("globbyD.bmp");
		animation.addFrame("globbyD.bmp");
		animation.addFrame("globbyL.bmp");
		animation.addFrame("globbyL.bmp");
		animation.addFrame("globbyL.bmp");
	}
    
    m_animation = animation;
}

ALLEGRO_BITMAP* Character::getImage() //Returns an image based on the animation_timer and the direction in which the player is moving
{
	if(last_direction == 1 || last_direction == 2)
	{
		if(internal_animation_timer/25 < 1)
		{
			return m_animation.getFrame(0);
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return m_animation.getFrame(1);
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return m_animation.getFrame(0);
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return m_animation.getFrame(2);
		}
	}
	if(last_direction == 3 || last_direction == 4)
	{
		if(internal_animation_timer/25 < 1)
		{
			return m_animation.getFrame(3);
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return m_animation.getFrame(4);
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return m_animation.getFrame(3);
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return m_animation.getFrame(5);
		}
	}
	if(last_direction == 5 || last_direction == 6)
	{
		if(internal_animation_timer/25 < 1)
		{
			return m_animation.getFrame(6);
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return m_animation.getFrame(7);
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return m_animation.getFrame(6);
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return m_animation.getFrame(8);
		}
	}
	if(last_direction == 7 || last_direction == 8)
	{
		if(internal_animation_timer/25 < 1)
		{
			return m_animation.getFrame(9);
		}
		if(internal_animation_timer/25 >= 1 && internal_animation_timer/25 < 2)
		{
			return m_animation.getFrame(10);
		}
		if(internal_animation_timer/25 >= 2 && internal_animation_timer/25 < 3)
		{
			return m_animation.getFrame(9);
		}
		if(internal_animation_timer/25 >= 3 && internal_animation_timer/25 <= 4)
		{
			return m_animation.getFrame(11);
		}
	}
	
	return m_animation.getFrame(6);
	

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
