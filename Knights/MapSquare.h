#ifndef MAPSQUARE_H
#define MAPSQUARE_H

#include <allegro5/allegro.h>

class MapSquare
{
public:
	MapSquare(void);
    MapSquare(const char* mapImageToSet, bool collisionInvalidToSet);
	~MapSquare(void);

	ALLEGRO_BITMAP* mapImage;
	bool collisionInvalid;
};

#endif