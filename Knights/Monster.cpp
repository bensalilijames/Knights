#include "Monster.h"
#include <stdio.h>
#include <stdlib.h>
#include "Items.h"

void Monster::moveRandomly(GameState* game)
{
    if(m_isMoving == false)
    {
        if((rand() % 200)==1)
        {
            m_isMoving = true;
            m_currentDirection = Direction(2 * (rand() % 4) + 1);
        }
    }
    else
    {
        if (!isCollision(m_currentDirection, game->getCurrentLevel().levelMap))
        {
            if(m_currentDirection == Direction::North) { m_y--; }
            if(m_currentDirection == Direction::South) { m_y++; }
            if(m_currentDirection == Direction::East)  { m_x++; }
            if(m_currentDirection == Direction::West)  { m_x--; }
            
            if((rand() % 70)==1)
            {
                m_isMoving = false;
            }
        }
        else
        {
            m_isMoving = false;
        }
    }
}

void Monster::moveTowardsPlayer(GameState* game)
{
    if(game->getPlayer().getX() - 30 > m_x && !isCollision(Direction::East, game->getCurrentLevel().levelMap))
    {
        m_x++;
        m_currentDirection = Direction::East;
    }
    if(game->getPlayer().getX() + 20 < m_x && !isCollision(Direction::West, game->getCurrentLevel().levelMap))
    {
        m_x--;
        m_currentDirection = Direction::West;
    }
    if(game->getPlayer().getY() - 30 > m_y && !isCollision(Direction::South, game->getCurrentLevel().levelMap))
    {
        m_y++;
        m_currentDirection = Direction::South;
    }
    if(game->getPlayer().getY() + 20 < m_y && !isCollision(Direction::North, game->getCurrentLevel().levelMap))
    {
        m_y--;
        m_currentDirection = Direction::North;
    }
}

void Monster::handleMovement(GameState* game)
{
	if(m_spawned)
	{
        m_lastDirection = m_currentDirection;
        if(!m_inCombat)
		{
            moveRandomly(game);
		}
		else
		{
            moveTowardsPlayer(game);
		}
	}
}

void Monster::handleCombat(GameState* game)
{
    if(m_inCombat)
    {
        m_timeSinceLastAttack += GameEngine::getDeltaTime();
        if(m_timeSinceLastAttack >= 0.5)
        {
            if(abs(game->getPlayer().getX() - m_x) + abs(game->getPlayer().getY() - m_y) <= 50)
            {
                game->getPlayer().reduceHealth(m_offencePotential, game);
            }
            m_timeSinceLastAttack = 0.0;
        }
    }
}

void Monster::killed(GameState* game) //When killed drop a random item
{
    if(game->getPlayer().getSelectedWeapon() == -1) { //Checks if the player already has a weapon equipped
        switch(rand() % 3)
        {
            case 0:
                game->getCurrentLevel().dropItem(Items::fishItem.get(), (m_x + 25) / 50, (m_y + 25) / 50);
                break;
            case 1:
                game->getCurrentLevel().dropItem(Items::potionItem.get(), (m_x + 25) / 50, (m_y + 25) / 50);
                break;
            case 2:
                game->getCurrentLevel().dropItem(Items::swordItem.get(), (m_x + 25) / 50, (m_y + 25) / 50);
                break;
        }
	}
    else
    {
        switch(rand() % 2)
        {
            case 0:
                game->getCurrentLevel().dropItem(Items::fishItem.get(), (m_x + 25) / 50, (m_y + 25) / 50);
                break;
            case 1:
                game->getCurrentLevel().dropItem(Items::potionItem.get(), (m_x + 25) / 50, (m_y + 25) / 50);
                break;
        }
	}


	m_health = 0;
	m_x = 0;
	m_y = 0;
	m_spawned = false;
	m_inCombat = false;

	game->getPlayer().addExperience(1);

	game->getCurrentLevel().decrementMonsterCount();

}

void Monster::onKill(GameState* game)
{
    killed(game);
}

void Monster::spawn(CharacterType type)
{
    m_width = 49;
    m_height = 49;
    
    if(type == CharacterType::Froggy)
	{
        m_spawned = true;
		m_health = 100;
		m_maxHealth = 100;
		m_offencePotential = 10;
	}
	if(type == CharacterType::Globby)
	{
		m_spawned = true;
		m_health = 150;
		m_maxHealth = 150;
		m_offencePotential = 20;
	}
    
    loadImages(type);
}
