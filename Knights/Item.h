#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <allegro5/allegro.h>

class Item
{
public:
	Item(void);
    Item(const char* image, const char* name, const char* examine, const char* type, int offenceModifier, int healingPotential);
	~Item(void);
    
    std::string getName(void) { return name; }
    std::string getExamine(void) { return examine; }
    std::string getType(void) { return type; }
    ALLEGRO_BITMAP* getImage(void) { return image; }
    int getHealingPotential(void) { return healingPotential; }
    int getOffenceModifier(void) { return offenceModifier; }
    int getDefenceModifier(void) { return defenceModifier; }

private:
	std::string name;
	std::string examine;
	std::string type;
	ALLEGRO_BITMAP* image;
	int healingPotential;
	int offenceModifier;
	int defenceModifier;
};

typedef std::unique_ptr<Item> ItemPtr;

#endif