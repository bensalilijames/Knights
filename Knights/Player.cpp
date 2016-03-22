#include "Player.h"

extern GameEngine *gameEngine;

Player::Player()
{
    offencePotential = 25;
    health = 1000;
    max_health = 1000;
    inventory = new Inventory(gameEngine);
    
    loadImages(0);
};

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


