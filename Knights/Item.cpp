#include "Item.h"

Item::Item(const char* image, const char* name, const char* examine, ItemType type, int offenceModifier, int defenceModifier, int healingPotential)
: m_name(name),
  m_examine(examine),
  m_type(type),
  m_offenceModifier(offenceModifier),
  m_defenceModifier(defenceModifier),
  m_healingPotential(healingPotential)
{
    m_image = al_load_bitmap(image);
    al_convert_mask_to_alpha(m_image, al_map_rgb(255, 0, 255));
}