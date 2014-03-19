#include "MapSquare.h"


MapSquare::MapSquare(void)
{
}

MapSquare::MapSquare(const char* mapImageToSet, bool collisionInvalidToSet) {
    mapImage = al_load_bitmap(mapImageToSet);
    al_convert_mask_to_alpha(mapImage, al_map_rgb(255, 0, 255));
    collisionInvalid = collisionInvalidToSet;
}

MapSquare::~MapSquare(void)
{
}