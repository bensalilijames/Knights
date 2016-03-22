//
//  Animation.h
//  Knights
//
//  Created by Ben James on 22/03/2016.
//
//

#ifndef Animation_h
#define Animation_h

#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>

class Animation
{
public:
    ALLEGRO_BITMAP* getFrame(int frame) const;
    ALLEGRO_BITMAP* getCurrentFrame() const;
    void addFrame(const char* path);
    void update();
    void setCurrentFrame(int frame);
    void nextFrame();
    void reset();
    void pause();
    
private:
    std::vector<ALLEGRO_BITMAP*> m_frames;
    double m_timeToNextFrame = 0;
    double m_lastAnimUpdateTime = 0;
    int m_currentFrame = 0;
    bool m_paused = false;
};

#endif /* Animation_h */
