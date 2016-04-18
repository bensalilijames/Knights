//
//  UI.cpp
//  Knights
//
//  Created by Ben James on 18/04/2016.
//
//

#include "UI.hpp"
#include "GameEngine.h"

ImageUIElement::ImageUIElement(const char* fileName)
{
    m_image = al_load_bitmap(fileName);
}

ImageUIElement::~ImageUIElement()
{
    if (m_image != nullptr)
    {
        al_destroy_bitmap(m_image);
    }
}

void ImageUIElement::DrawToTarget(ALLEGRO_BITMAP* renderTarget)
{
    al_set_target_bitmap(renderTarget);
    al_draw_bitmap(m_image, 0, 0, 0);
}

void ImageUIElement::DrawToScreen()
{
    al_set_target_backbuffer(GameEngine::getInstance().display);
    al_draw_bitmap(m_image, 0, 0, 0);
}