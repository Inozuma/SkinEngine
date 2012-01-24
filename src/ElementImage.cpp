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
    mImage.openFile(mFilename);
}

ElementImage::~ElementImage()
{
}

bool ElementImage::collide(float x, float y)
{
    if (x > mPosition.x && x < mPosition.x + mImage.getWidth()
            && y > mPosition.y && y < mPosition.y + mImage.getHeight())
        return true;
    return false;
}

void ElementImage::draw(SDL_Surface* displaySurface)
{
    mImage.setPosition(mPosition.x + mImage.getWidth() * mOriginH,
            mPosition.y + mImage.getHeight() * mOriginV);
    mImage.setRotation(mRotation);
    mImage.setScale(mScale.x, mScale.y);
    mImage.draw(displaySurface);
}

void ElementImage::setOrigin(float h, float v)
{
    mOriginH = h;
    mOriginV = v;
    if (mOriginH > 1)
        mOriginH = 1;
    else if (mOriginH < 0)
        mOriginH = 0;
    if (mOriginV > 1)
        mOriginV = 0;
    else if (mOriginV < 0)
        mOriginV = 0;
}