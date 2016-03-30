#ifndef MAPSQUARES_H
#define MAPSQUARES_H

#include <vector>
#include <allegro5/allegro.h>

enum class MapSquareGroup {
    None,
    Grass,
    Rock,
    Tree,
    Polar
};

class MapSquare
{
public:
    MapSquare(const char* imageFile, bool collidable, MapSquareGroup group = MapSquareGroup::None)
    : m_collidable(collidable), m_group(group)
    {
        m_image = al_load_bitmap(imageFile);
        al_convert_mask_to_alpha(m_image, al_map_rgb(255, 0, 255));
    }
    
    bool isCollidable() { return m_collidable; }
    ALLEGRO_BITMAP* getImage() { return m_image; }
    MapSquareGroup getGroup() { return m_group; }
    
private:
    ALLEGRO_BITMAP* m_image;
    bool m_collidable;
    MapSquareGroup m_group;
};

typedef std::unique_ptr<MapSquare> MapSquarePtr;

class MapRegistry {
public:
    static void registerDefaultSquares();
    static void registerSquare(const std::string& id,
                               const std::string& imageFile,
                               bool collidable,
                               MapSquareGroup group = MapSquareGroup::None);
    static MapSquare* getRegisteredSquare(const std::string& id);
    static MapSquare* getRandomSquareInGroup(MapSquareGroup group);

private:
    static std::vector<std::pair<std::string, MapSquarePtr>> s_registeredSquares;
};

#endif