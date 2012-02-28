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
        double mSize;
        std::string mText;
        bool mSelect;
        
    public:
        ElementInput(Screen&, const Vectorf&, double = 0);
        virtual ~ElementInput();
        
		Text& label();
		Box& box();

        virtual std::string getData(const std::string&);
        
		virtual void parse(const std::string&, const std::string&);
        virtual bool collide(double x, double y);
        virtual void draw(SDL_Surface* displaySurface);
		virtual void eventKey(const EventKey &);
        
        virtual void onFocus();
        virtual void onIdle();
    };
}

#endif	/* ELEMENTINPUT_H */

