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
        double mOriginH;
        double mOriginV;
        
    public:
        ElementImage(Screen&, const Vectorf &, const std::string & = "");
        virtual ~ElementImage();
        
		Image& image();

		virtual void parse(const std::string&, const std::string&);
        virtual bool collide(double, double);
        virtual void draw(SDL_Surface* displaySurface);
    };
}

#endif	/* ELEMENTIMAGE_H */

