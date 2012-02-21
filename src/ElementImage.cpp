/* 
 * File:   ElementImage.cpp
 * Author: Inozuma
 * 
 * Created on January 10, 2012, 9:35 AM
 */

#include "Skin/ElementImage.h"
#include "Skin/Image.h"

using namespace Skin;

ElementImage::ElementImage(Screen& screen, const Vectorf & position,
        const std::string & imageFile) :
Element(screen, position, false),
mFilename(imageFile),
mOriginH(0),
mOriginV(0)
{
}

ElementImage::~ElementImage()
{
}

Image& ElementImage::image()
{
	return mImage;
}

void ElementImage::parse(const std::string& key, const std::string& value)
{
	std::string sImg("img-");

	if (key.find(sImg) == 0)
	{
		mImage.parse(key.substr(sImg.size()), value);
	}
}

bool ElementImage::collide(double x, double y)
{
    if (x > mPosition.x && x < mPosition.x + mImage.getWidth()
            && y > mPosition.y && y < mPosition.y + mImage.getHeight())
        return true;
    return false;
}

void ElementImage::draw(SDL_Surface* displaySurface)
{
    mImage.setPosition(mPosition.x, mPosition.y);
    mImage.setRotation(mRotation);
    mImage.setScale(mScale.x, mScale.y);
    mImage.draw(displaySurface);
}