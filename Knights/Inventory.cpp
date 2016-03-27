#include "Inventory.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GameEngine.h"
#include "Items.h"

Inventory::Inventory()
{
    capacity = standardCapacity;
    items.resize(standardCapacity);
    
    cachedInventoryDraw = al_create_bitmap(GameEngine::getInstance().scrx, 150);
    needsRedraw = true;
}

Inventory::~Inventory(void)
{
    al_destroy_bitmap(cachedInventoryDraw);
}

int Inventory::getSelectedSlot(void) {
    return selectedSlot;
}

Item* Inventory::getSelectedItem(void) {
    return items[selectedSlot];
}

Item* Inventory::getItemAt(int slot) {
    if (slot < 0 || slot >= items.size()) return NULL;
    return items[slot];
}

void Inventory::deleteFromSelectedSlot()
{
    items[selectedSlot] = NULL;
    needsRedraw = true;
}

void Inventory::deleteFromSlot(int slot) {
    items[slot] = NULL;
    needsRedraw = true;
}

bool Inventory::addToInventory(Item* itemToAdd)
{
	int i = 0;
	
	while(items[i] != NULL && i < items.size())
	{
		i++;
	}
    
	if(i != items.size())
	{
        items[i] = itemToAdd;
        needsRedraw = true;
		return true;
	}
	return false;
}

void Inventory::useSelectedItem(Player* player) {
    if(getSelectedItem() != NULL) {
        if(getSelectedItem()->getType() == ItemType::Food) //If food then increase health
        {
            player->increaseHealth(getSelectedItem()->getHealingPotential());
            deleteFromSelectedSlot();
        }
        else if(getSelectedItem()->getType() == ItemType::Weapon && player->getSelectedWeapon() != selectedSlot) //If weapon and not already one equipped, equip weapon
        {
            if(getItemAt(player->getSelectedWeapon()) != NULL) {
                int delta = -getItemAt(player->getSelectedWeapon())->getOffenceModifier();
                player->modifyOffencePotential(delta);
            }
            player->setSelectedWeapon(selectedSlot);
            int delta = getSelectedItem()->getOffenceModifier();
            player->modifyOffencePotential(delta);
        }
        else if(getSelectedItem()->getType() == ItemType::Weapon && player->getSelectedWeapon() == selectedSlot) //If weapon and not already one equipped, equip weapon
        {
            int delta = -getSelectedItem()->getOffenceModifier();
            player->modifyOffencePotential(delta);
            player->setSelectedWeapon(-1);
        }
    }

    needsRedraw = true;
}

void Inventory::dropSelectedItem(GameState* game) {
    if(getSelectedItem() != NULL)
    {
        if(getSelectedSlot() == game->getPlayer().getSelectedWeapon()) //If equipped weapon, unequip it first
        {
            game->getPlayer().setSelectedWeapon(-1);
            int delta = -getSelectedItem()->getOffenceModifier();
            game->getPlayer().modifyOffencePotential(delta);
        }
        game->getCurrentLevel().levelMapItems[game->getPlayer().getX()/50][game->getPlayer().getY()/50] = getSelectedItem();
        deleteFromSelectedSlot();
    }
}

//Deletes all items and replaces with the initial items
void Inventory::populateInventory(void)
{
	for(int i = 0; i <= items.size(); i++)
    {
		deleteFromSlot(i);
    }
    
	items[0] = Items::fishItem.get();
	items[1] = Items::potionItem.get();
	items[2] = Items::fishItem.get();
	items[3] = Items::fishItem.get();
	
	selectedSlot = 0;
    needsRedraw = true;
}

void Inventory::moveSelectorRight(void) {
    if(selectedSlot < items.size()-1)
    {
        selectedSlot += 1;
    }
    needsRedraw = true;
}

void Inventory::moveSelectorLeft(void) {
    if(selectedSlot >= 1)
    {
        selectedSlot -= 1;
    }
    needsRedraw = true;
}

void Inventory::drawInventory(GameEngine* gameEngine, int equippedItem, ALLEGRO_FONT *mainFont)
{
    if(!needsRedraw) return;
    if(!cachedInventoryDraw) cachedInventoryDraw = al_create_bitmap(gameEngine->scrx, 150);
    
    al_set_target_bitmap(cachedInventoryDraw);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_convert_mask_to_alpha(cachedInventoryDraw, al_map_rgb(0, 0, 0));
    
    al_draw_filled_rectangle(0, 100, gameEngine->scrx, 150, al_map_rgb(100, 100, 100));

	for(int i=0; i<items.size(); i++)  //For every Inventory item, if it’s selected give it a darker background, otherwise a lighter one
	{
		if(i == selectedSlot)
		{
			al_draw_filled_rectangle(70*i+30, 100, 70*i+80, 150,al_map_rgb(150, 150, 150));
			if(items[i] != NULL) //Create an infopane with name and examine
			{
				al_draw_filled_rectangle(70*i+5, 40, 70*i+105, 90, al_map_rgb(52, 152, 219));
                al_draw_text(mainFont, al_map_rgb(255, 255, 255), 70*i+10, 45, 0, items[i]->getName().c_str());
                
				if(items[i]->getExamine().length() <= 12)
				{
					al_draw_text(mainFont, al_map_rgb(255, 255, 255), 70*i+10, 55, 0, items[i]->getExamine().c_str());
				}
				else //If examine text is too long then split it into two lines
				{
                    al_draw_text(mainFont, al_map_rgb(255, 255, 255), 70*i+10, 55, 0, items[i]->getExamine().substr(0,items[i]->getExamine().substr(0,12).find_last_of(" ")).c_str());
                    al_draw_text(mainFont, al_map_rgb(255, 255, 255), 70*i+10, 65, 0, items[i]->getExamine().substr(items[i]->getExamine().substr(0,12).find_last_of(" ")+1).c_str());

                }
			}
			
		}
		else
		{
			al_draw_filled_rectangle(70*i+30, 100, 70*i+80, 150, al_map_rgb(189, 195, 199));
		}
		
		if(equippedItem == i) //If item is equipped (weapon) then make background red
		{
			al_draw_filled_rectangle(70*i+30, 100, 70*i+80, 150, al_map_rgb(231, 76, 60));
		}

		if(items[i] != NULL && items[i]->getExamine() != "")
		{
			al_draw_bitmap(items[i]->getImage(), 70*i+30, 100, 0);
		}
	}
    
    needsRedraw = false;
}