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

ALLEGRO_BITMAP* Animation::getCurrentFrame() const
{
    return m_frames.at(m_currentFrame);
}

void Animation::nextFrame()
{
    m_currentFrame++;
    if (m_currentFrame >= m_frames.size())
    {
        m_currentFrame = 0;
    }
}

void Animation::pause()
{
    m_paused = true;
}

void Animation::reset()
{
    m_lastAnimUpdateTime = al_get_time();
    m_currentFrame = 0;
    m_timeToNextFrame = 0.5;
    m_paused = false;
}

void Animation::update()
{
    if (!m_paused)
    {
        //TODO: move timedelta to game engine method
        double currentTime = al_get_time();
        double timeDelta = al_get_time() - m_lastAnimUpdateTime;
        m_lastAnimUpdateTime = currentTime;
        m_timeToNextFrame -= timeDelta;
        if (m_timeToNextFrame <= 0.0)
        {
            nextFrame();
            m_timeToNextFrame = 0.5;
        }
    }
}

void Animation::setCurrentFrame(int frame)
{
    m_currentFrame = frame;
}