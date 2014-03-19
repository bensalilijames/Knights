#include "Player.h"

extern GameEngine *gameEngine;

Player::Player(void)
{
    inventory = new Inventory(gameEngine);
    
    last_direction = 0;
    internal_animation_timer = 0;
    health = 1000;
    max_health = 1000;
    offencePotential = 25;
    isDead = false;
    selected_weapon = -1;
    experience = 0;
    
    loadImages(0);
}

Player::~Player(void)
{
    delete inventory;
}

void Player::handleAnimation(void)
{
	if(is_moving == false)
	{
		internal_animation_timer = 0;
	}

	if(internal_animation_timer >= 100)
	{
		internal_animation_timer = 0;
	}
}

void Player::reduceHealth(int maxReduction)
{
	health -= rand() % maxReduction; //Reduces health by a random amount
	if(health <= 0) //If reduced to 0 then Player is dead
	{
		health = 0;
		isDead = true;
	}
}

void Player::increaseHealth(int increment)
{
	health += increment;
	if(health >= max_health) //Ensures cannot go over max health
	{
		health = max_health;
	}
}


