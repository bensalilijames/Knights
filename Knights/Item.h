#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <allegro5/allegro.h>

enum class ItemType {
    Food,
    Weapon
};

class Item
{
public:
	Item(const char* image, const char* name, const char* examine, ItemType type, int offenceModifier, int defenceModifier, int healingPotential);
	
    std::string getName(void) { return m_name; }
    std::string getExamine(void) { return m_examine; }
    ItemType getType(void) { return m_type; }
    ALLEGRO_BITMAP* getImage(void) { return m_image; }
    int getHealingPotential(void) { return m_healingPotential; }
    int getOffenceModifier(void) { return m_offenceModifier; }
    int getDefenceModifier(void) { return m_defenceModifier; }

private:
	const std::string m_name;
	const std::string m_examine;
	const ItemType m_type;
	ALLEGRO_BITMAP* m_image;
	const int m_healingPotential;
	const int m_offenceModifier;
	const int m_defenceModifier;
};

typedef std::unique_ptr<Item> ItemPtr;

#endif