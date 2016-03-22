//
//  Animation.cpp
//  Knights
//
//  Created by Ben James on 22/03/2016.
//
//

#include "Animation.h"

ALLEGRO_BITMAP* Animation::getFrame(int frame) const
{
    if (frame < m_frames.size())
    {
        return m_frames.at(frame);
    }
    return nullptr;
}

void Animation::addFrame(const char* path)
{
    ALLEGRO_BITMAP* image = al_load_bitmap(path);
    al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
    m_frames.push_back(image);
}