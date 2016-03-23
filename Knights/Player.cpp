#include "Player.h"

extern GameEngine *gameEngine;

Player::Player()
{
    m_height = 40;
    m_width = 30;
    m_offencePotential = 25;
    m_health = 1000;
    m_maxHealth = 1000;
    inventory = new Inventory(gameEngine);
    
    loadImages(0);
};

void Player::reduceHealth(int maxReduction)
{
	m_health -= rand() % maxReduction; //Reduces health by a random amount
	if(m_health <= 0) //If reduced to 0 then Player is dead
	{
		m_health = 0;
		isDead = true;
	}
}

void Player::increaseHealth(int increment)
{
	m_health += increment;
	if(m_health >= m_maxHealth) //Ensures cannot go over max health
	{
		m_health = m_maxHealth;
	}
}


