/* 
 * File:   ElementList.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 4:00 PM
 */

#ifndef ELEMENTLIST_H
#define	ELEMENTLIST_H

#include "Skin/Element.h"
#include "Skin/Text.h"
#include "Skin/Box.h"

#include <vector>

#define OFFSET_X 10
#define OFFSET_Y 5

namespace Skin
{

    class ElementList : public Element
    {
    private:
        std::vector<std::string> mValues;
        std::string mValue;
        Vectorf mBoxsize;
        Text mFont;
        Box mBox;
        
        int mIndex;
        int mOffset;
        unsigned int mMax;
        
    public:
        ElementList(Screen&, const Vectorf&, const std::string&, const Vectorf&);
        virtual ~ElementList();
        
        virtual std::string getData(const std::string&);
        
        virtual bool collide(float x, float y);
        virtual void draw(SDL_Surface* displaySurface);
        virtual void update(float);
        
        virtual void onUp();
        virtual void onDown();
        
        void setFontname(const std::string&);
        void setFontsize(unsigned int);
        
    private:
        void parseDynamicData();
    };
}

#endif	/* ELEMENTLIST_H */

