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

#include <string>

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
        
        virtual bool collide(float, float);
        virtual void draw(SDL_Surface* displaySurface);
        
        void setLabel(const std::string &);
        void setFontname(const std::string &);
        void setFontsize(unsigned int);
        void setFontcolor(const Color&);
        
        const std::string& getLabel() const;
        unsigned int getSize() const;
        const std::string & getFontname() const;
        unsigned int getFontsize() const;
        const Color& getFontcolor() const;
    };
};

#endif	/* ELEMENTTEXT_H */

