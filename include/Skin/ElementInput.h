/* 
 * File:   ElementInput.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 10:39 AM
 */

#ifndef ELEMENTINPUT_H
#define	ELEMENTINPUT_H

#include "Skin/Element.h"
#include "Skin/Text.h"
#include "Skin/Box.h"

namespace Skin
{

    class ElementInput : public Element
    {
    private:
        Text mLabel;
        Box mBox;
        float mSize;
        std::string mText;
        bool mSelect;
        
    public:
        ElementInput(Screen&, const Vectorf&, float);
        virtual ~ElementInput();
        
        virtual std::string getData(const std::string&);
        
        virtual bool collide(float x, float y);
        virtual void draw(SDL_Surface* displaySurface);
        virtual void event(const SDL_Event&);
        
        virtual void onFocus();
        virtual void onIdle();
        
        void setFontname(const std::string&);
        void setFontsize(unsigned int);
        void setFontcolor(const Color&);
        void setBoxColor(const Color&);
        void setOutlineColor(const Color&);
        void setRadius(int);
        void setSize(float);
        void setText(const std::string&);
        
        const std::string& getFontname() const;
        unsigned int getFonsize() const;
        const Color& getFontcolor() const;
        float getSize() const;
        const std::string& getText() const;
    };
}

#endif	/* ELEMENTINPUT_H */

