/* 
 * File:   ElementImage.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 9:35 AM
 */

#ifndef ELEMENTIMAGE_H
#define	ELEMENTIMAGE_H

#include "Skin/Element.h"
#include "Skin/Image.h"

namespace Skin
{

    class ElementImage : public Element
    {
    private:
        std::string mFilename;
        Image mImage;
        float mOriginH;
        float mOriginV;
        
    public:
        ElementImage(Screen&, const Vectorf &, const std::string &);
        virtual ~ElementImage();
        
        virtual bool collide(float, float);
        virtual void draw(SDL_Surface* displaySurface);
        
        void setOrigin(float, float);
    };
}

#endif	/* ELEMENTIMAGE_H */

