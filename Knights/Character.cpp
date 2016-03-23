#include "Character.h"

void Character::modifyOffencePotential(int delta)
{
    m_offencePotential += delta;
}

void Character::updateDirection(Direction direction)
{
    m_lastDirection = m_currentDirection;
    m_currentDirection = direction;
}

void Character::move(int x, int y)
{
    m_x += x;
    m_y += y;
}

void Character::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

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
    if(m_currentDirection != m_lastDirection)
    {
        if(m_currentDirection == North || m_currentDirection == NorthEast)
        {
            //TODO: This would be better with an anim ID or name instead of an arbitary number
            setActiveAnimation(0);
        }
        else if(m_currentDirection == East || m_currentDirection == SouthEast)
        {
            setActiveAnimation(1);
        }
        else if(m_currentDirection == South || m_currentDirection == SouthWest)
        {
            setActiveAnimation(2);
        }
        else if(m_currentDirection == West || m_currentDirection == NorthWest)
        {
            setActiveAnimation(3);
        }
        else
        {
            // Player is idle, set animation back to first frame and pause
            m_currentAnimation.reset();
            m_currentAnimation.pause();
        }
    }
    
    m_currentAnimation.update();
}

// Returns the current frame of the animation
ALLEGRO_BITMAP* Character::getImage()
{
    return m_currentAnimation.getCurrentFrame();
}

bool Character::isCollision(Direction direction, std::vector<std::vector<MapSquare*>> map)
{
    if(direction != 1 && direction != 3 && direction != 5 && direction != 7) {
        return false;
    }
    
    int collision[4];
    
	if(direction == North)
	{
		collision[0] = (m_x) / 50; //Sets up the m_x and m_y to check for collision
		collision[1] = (m_y - 1) / 50;

		collision[2] = (m_x + m_width) / 50;
		collision[3] = (m_y - 1) / 50;

	}

	if(direction == South)
	{
		collision[0] = (m_x) / 50;
		collision[1] = (m_y + m_height + 1) / 50;

		collision[2] = (m_x + m_width) / 50;
		collision[3] = (m_y + m_height + 1) / 50;
        
	}

	if(direction == East)
	{
		collision[0] = (m_x + m_width + 1) / 50;
		collision[1] = (m_y) / 50;

		collision[2] = (m_x + m_width + 1) / 50;
		collision[3] = (m_y + m_height) / 50;

	}

	if(direction == West)
	{
		collision[0] = (m_x - 1) / 50;
		collision[1] = (m_y) / 50;

		collision[2] = (m_x - 1) / 50;
		collision[3] = (m_y + m_height) / 50;

	}

    if (map[collision[1]][collision[0]]->collisionInvalid == true || map[collision[3]][collision[2]]->collisionInvalid == true) {
        return true;
    }
    
	return false;
}
