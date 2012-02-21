/* 
 * File:   ElementText.h
 * Author: Inozuma
 *
 * Created on January 8, 2012, 8:43 PM
 */

#ifndef ELEMENTTEXT_H
#define	ELEMENTTEXT_H

#include "Skin/Element.h"
#include "Skin/Text.h"

namespace Skin
{

    class ElementLabel : public Element
    {
    public:
        enum Alignment
        {
            RIGHT,
            CENTER,
            LEFT
        };
        
    private:
        Text mLabel;
        
    public:
        ElementLabel(Screen&, const Vectorf & = Vectorf(), const std::string & = "");
        virtual ~ElementLabel();
        
		virtual void parse(const std::string&, const std::string&);
        virtual bool collide(double, double);
        virtual void draw(SDL_Surface* displaySurface);
        
        Text& label();
    };
};

#endif	/* ELEMENTTEXT_H */

