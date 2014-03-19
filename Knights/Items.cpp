#include "Items.h"

void Items::setItems(void) {
    fishItem = new Item("fish.bmp", "Fish", "Heals some health", "Food", 0, 150);
    swordItem = new Item("sword.bmp", "Sword", "A deadly weapon", "Weapon", 30, 0);
    potionItem = new Item("healingPotion.bmp", "Potion", "Heals some health", "Food", 0, 300);
}

Item* Items::fishItem = NULL;
Item* Items::potionItem = NULL;
Item* Items::swordItem = NULL;