/* 
 * File:   ElementButton.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 11:22 PM
 */

#ifndef ELEMENTBUTTON_H
#define	ELEMENTBUTTON_H

#include "Skin/Element.h"
#include "Skin/Image.h"
#include "Skin/Text.h"

#include <SDL/SDL_ttf.h>

namespace Skin
{

    class ElementButton : public Element
    {
    private:
        enum State
        {
            ONIDLE = 0,
            ONFOCUS,
            ONSELECT
        };
        
    private:
        Text mLabel;
        Image mImage[3];

        State mCurrentState;

    public:
        ElementButton(Screen&, const Vectorf&, const std::string&);
        virtual ~ElementButton();

        virtual bool collide(float x, float y);
        virtual void draw(SDL_Surface* displaySurface);
        
        virtual void onIdle();
        virtual void onFocus();
        virtual void onSelect();
        
        void setFontname(const std::string& fontname);
        void setFontsize(unsigned int fontsize);
        void setFontcolor(const Color& fontcolor);
        void setImageOnIdle(const std::string& image);
        void setImageOnFocus(const std::string& image);
        void setImageOnSelect(const std::string& image);
    };
}

#endif	/* ELEMENTBUTTON_H */

