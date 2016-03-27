#include "Player.h"

Player::Player()
{
    m_height = 40;
    m_width = 30;
    m_offencePotential = 25;
    m_health = 1000;
    m_maxHealth = 1000;
    inventory = std::make_unique<Inventory>();
    
    loadImages(CharacterType::Player);
};

