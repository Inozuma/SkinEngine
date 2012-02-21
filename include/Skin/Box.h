/* 
 * File:   Box.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 9:14 AM
 */

#ifndef BOX_H
#define	BOX_H

#include "Skin/Vector.h"
#include "Skin/Color.h"

#include <string>

struct SDL_Surface;

namespace Skin
{
    class Box
    {
    private:
        Vectorf mPosition;
        Vectorf mSize;
        int mRadius;
        Color mBoxColor;
        Color mOutlineColor;
        
    public:
        Box();
        virtual ~Box();
        
        const Vectorf& getPosition() const;
        const Vectorf& getSize() const;
        int getRadius() const;
        const Color& getBoxColor() const;
        const Color& getOutlineColor() const;
        
        void setPosition(const Vectorf&);
        void setPosition(double x, double y);
        void setSize(const Vectorf&);
        void setSize(double x, double y);
        void setRadius(int);
        void setBoxColor(const Color&);
        void setOutlineColor(const Color&);
        
        void draw(SDL_Surface* drawSurface);
		void parse(const std::string&, const std::string&);
    };
}

#endif	/* BOX_H */

