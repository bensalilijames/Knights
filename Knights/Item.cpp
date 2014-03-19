#include "Item.h"

Item::Item(void)
{
}

Item::Item(const char* imageToSet, const char* nameToSet, const char* examineToSet, const char* typeToSet, int offenceModifierToSet, int healingPotentialToSet)
{
    image = al_load_bitmap(imageToSet);
    al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
    name = nameToSet;
    examine = examineToSet;
    type = typeToSet;
    offenceModifier = offenceModifierToSet;
    healingPotential = healingPotentialToSet;
}

Item::~Item(void)
{
}