/* 
 * File:   Box.cpp
 * Author: Inozuma
 * 
 * Created on December 11, 2011, 9:17 AM
 */

#include "Skin/Box.h"

#include <SDL/SDL_gfxPrimitives.h>

using namespace Skin;

Box::Box() :
mRadius(1)
{
}

Box::~Box()
{
}

const Vectorf& Box::getPosition() const
{
    return mPosition;
}

const Vectorf& Box::getSize() const
{
    return mSize;
}

int Box::getRadius() const
{
    return mRadius;
}

const Color& Box::getBoxColor() const
{
    return mBoxColor;
}

const Color& Box::getOutlineColor() const
{
    return mOutlineColor;
}

void Box::setPosition(const Vectorf& point)
{
    mPosition = point;
}

void Box::setPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Box::setSize(const Vectorf& point)
{
    mSize = point;
}

void Box::setSize(float x, float y)
{
    mSize.x = x;
    mSize.y = y;
}

void Box::setRadius(int radius)
{
    mRadius = radius;
}

void Box::setBoxColor(const Color& color)
{
    mBoxColor = color;
}

void Box::setOutlineColor(const Color& color)
{
    mOutlineColor = color;
}

void Box::draw(SDL_Surface* drawSurface)
{
    roundedBoxRGBA(drawSurface, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.y + mSize.y, mRadius, mBoxColor.r, mBoxColor.g, mBoxColor.b, mBoxColor.a * 255);
    roundedRectangleRGBA(drawSurface, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.y + mSize.y, mRadius, mOutlineColor.r, mOutlineColor.g, mOutlineColor.b, mOutlineColor.a * 255);
}