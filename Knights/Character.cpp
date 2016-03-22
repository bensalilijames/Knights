#include "Character.h"

void Character::createAnimation(const std::vector<const char *> paths)
{
    Animation animation;
    for (auto &path : paths)
    {
        animation.addFrame(path);
    }
    m_animations.push_back(animation);
}

void Character::loadImages(int initial_image) //Loads the relevant images based on the ID of the Character
{
	if(initial_image == 0)
	{
        createAnimation({"manU.bmp", "manU2.bmp", "manU.bmp", "manU3.bmp"});
        createAnimation({"manR.bmp", "manR2.bmp", "manR.bmp", "manR3.bmp"});
        createAnimation({"manD.bmp", "manD2.bmp", "manD.bmp", "manD3.bmp"});
        createAnimation({"manL.bmp", "manL2.bmp", "manL.bmp", "manL3.bmp"});
    }
	else if(initial_image == 1)
	{
        createAnimation({"froggyU.bmp"});
        createAnimation({"froggyR.bmp"});
        createAnimation({"froggyD.bmp"});
        createAnimation({"froggyL.bmp"});
	}
	else if(initial_image == 2)
	{
        createAnimation({"globbyU.bmp"});
        createAnimation({"globbyR.bmp"});
        createAnimation({"globbyD.bmp"});
        createAnimation({"globbyL.bmp"});
	}
    setActiveAnimation(0);
}

void Character::setActiveAnimation(int animationId)
{
    m_currentAnimation = m_animations.at(animationId);
    m_currentAnimation.reset();
}

void Character::updateAnimation()
{
    if(current_direction != last_direction)
    {
        if(current_direction == 1 || current_direction == 2)
        {
            setActiveAnimation(0);
        }
        else if(current_direction == 3 || current_direction == 4)
        {
            setActiveAnimation(1);
        }
        else if(current_direction == 5 || current_direction == 6)
        {
            setActiveAnimation(2);
        }
        else if(current_direction == 7 || current_direction == 8)
        {
            setActiveAnimation(3);
        }
        else
        {
            m_currentAnimation.reset();
            m_currentAnimation.pause();
        }
    }
    
    //TODO: Idle animation
    
    m_currentAnimation.update();
}

ALLEGRO_BITMAP* Character::getImage() //Returns an image based on the animation_timer and the direction in which the player is moving
{
    return m_currentAnimation.getCurrentFrame();
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
