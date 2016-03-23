#ifndef MAPSQUARES_H
#define MAPSQUARES_H

#include <vector>
#include <allegro5/allegro.h>

class MapSquare
{
public:
    MapSquare(const char* imageFile, bool collidable)
    : m_collidable(collidable)
    {
        m_image = al_load_bitmap(imageFile);
        al_convert_mask_to_alpha(m_image, al_map_rgb(255, 0, 255));
    }
    
    bool isCollidable() { return m_collidable; }
    ALLEGRO_BITMAP* getImage() { return m_image; }
    
private:
    ALLEGRO_BITMAP* m_image;
    bool m_collidable;
};

class MapSquares {
    public:
    static std::vector<MapSquare*> treeSquare;
    static std::vector<MapSquare*> rockSquare;
    static std::vector<MapSquare*> polarSquare;
    static std::vector<MapSquare*> grassSquare;
    
    static void setMapSquares();
};

#endif