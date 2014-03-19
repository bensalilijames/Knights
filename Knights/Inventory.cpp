#include "Inventory.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GameEngine.h"
#include "Items.h"

Inventory::Inventory(GameEngine* gameEngine)
{
    selectedSlot = 0;
    capacity = standardCapacity;
    items.resize(standardCapacity);
    
    //cachedInventoryDraw = al_create_bitmap(gameEngine->scrx, 150);
    cachedInventoryDraw = NULL;
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
	}  //Cycles through Inventory spaces until an empty slot is found
	
	if(i != items.size()) //If there is space (i.e. not 8) then add the item to the Inventory
	{
        items[i] = itemToAdd;
        needsRedraw = true;
		return 1;
	}
	return 0;
}

void Inventory::useSelectedItem(Player* player) {
    if(getSelectedItem() != NULL) {
        if(getSelectedItem()->getType() == "Food") //If food then increase health
        {
            player->increaseHealth(getSelectedItem()->getHealingPotential());
            deleteFromSelectedSlot();
        }
        else if(getSelectedItem()->getType() == "Weapon" && player->selected_weapon != selectedSlot) //If weapon and not already one equipped, equip weapon
        {
            if(getItemAt(player->selected_weapon) != NULL) {
                player->offencePotential -= getItemAt(player->selected_weapon)->getOffenceModifier();
            }
            player->selected_weapon = selectedSlot;
            player->offencePotential += getSelectedItem()->getOffenceModifier();
        }
        else if(getSelectedItem()->getType() == "Weapon" && player->selected_weapon == selectedSlot) //If weapon and not already one equipped, equip weapon
        {
            player->offencePotential -= getSelectedItem()->getOffenceModifier();
            player->selected_weapon = -1;
        }
    }

    needsRedraw = true;
}

void Inventory::dropSelectedItem(GameState* game) {
    if(getSelectedItem() != NULL)
    {
        if(getSelectedSlot() == game->mainCharacter->selected_weapon) //If equipped weapon, unequip it first
        {
            game->mainCharacter->selected_weapon = -1;
            game->mainCharacter->offencePotential -= getSelectedItem()->getOffenceModifier();
        }
        game->currentLevel->levelMapItems[game->mainCharacter->x_position/50][game->mainCharacter->y_position/50] = getSelectedItem();
        deleteFromSelectedSlot();
    }
}

void Inventory::populateInventory(void) //Deletes all items and replaces with the initial items
{
	for(int i = 0; i <= items.size(); i++)
    {
		deleteFromSlot(i);
    }
    
	items[0] = Items::fishItem;
	items[1] = Items::potionItem;
	items[2] = Items::fishItem;
	items[3] = Items::fishItem;
	
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