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
    void addFrame(const char* path);
    
private:
    std::vector<ALLEGRO_BITMAP*> m_frames;
};

#endif /* Animation_h */
