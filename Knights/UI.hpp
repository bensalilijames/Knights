//
//  UI.hpp
//  Knights
//
//  Created by Ben James on 18/04/2016.
//
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>

class UIElement
{
public:
    virtual ~UIElement() {};
    
    virtual void DrawToTarget(ALLEGRO_BITMAP* renderTarget) = 0;
    virtual void DrawToScreen() = 0;
};

class ImageUIElement : UIElement
{
public:
    ImageUIElement() {};
    ImageUIElement(const char* fileName);
    virtual ~ImageUIElement();
    
    virtual void DrawToTarget(ALLEGRO_BITMAP* renderTarget) override;
    virtual void DrawToScreen() override;
    
private:
    ALLEGRO_BITMAP* m_image;
};

typedef std::unique_ptr<ImageUIElement> ImageUIElementPtr;

#endif /* UI_hpp */
