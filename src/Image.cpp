/* 
 * File:   Image.cpp
 * Author: inozuma
 * 
 * Created on January 23, 2012, 2:55 AM
 */

#include "Skin/Image.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>

using namespace Skin;

Image::Image() :
mSurface(NULL),
mRotation(0),
mScale(1, 1),
mSmooth(0),
mWidth(0),
mHeight(0)
{
}

Image::Image(const std::string& filename) :
mSurface(NULL),
mRotation(0),
mScale(1, 1),
mSmooth(0),
mWidth(0),
mHeight(0)
{
    openFile(filename);
}

Image::~Image()
{
    if (mSurface)
    {
        SDL_FreeSurface(mSurface);
        mSurface = NULL;
    }
}

bool Image::openFile(const std::string& filename)
{
    if (mSurface)
    {
        SDL_FreeSurface(mSurface);
        mSurface = NULL;
        mFilename = "";
        mWidth = 0;
        mHeight = 0;
    }
    mSurface = IMG_Load(filename.c_str());
    if (mSurface == NULL)
    {
        std::cerr << "Could not load file `" << filename << "`: " << IMG_GetError() << std::endl;
        return false;
    }
    mFilename = filename;
    mWidth = mSurface->w;
    mHeight = mSurface->h;
    return true;
}

bool Image::isOpen() const
{
    return mSurface ? true : false;
}

const std::string& Image::getFilename() const
{
    return mFilename;
}

const Vectorf& Image::getPosition() const
{
    return mPosition;
}

float Image::getRotation() const
{
    return mRotation;
}

const Vectorf& Image::getScale() const
{
    return mScale;
}

bool Image::hasSmooth() const
{
    return mSmooth ? true : false;
}

int Image::getWidth() const
{
    return mWidth;
}

int Image::getHeight() const
{
    return mHeight;
}

void Image::setPosition(const Vectorf& position)
{
    mPosition = position;
}

void Image::setPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Image::setRotation(float rotation)
{
    mRotation = rotation;
}

void Image::setScale(const Vectorf& scale)
{
    mScale = scale;
}

void Image::setScale(float x, float y)
{
    mScale.x = x;
    mScale.y = y;
}

void Image::setSmooth(bool smooth)
{
    mSmooth = smooth ? true : false;
}

void Image::draw(SDL_Surface* drawSurface)
{
    if (mSurface)
    {
        SDL_Surface* surface = rotozoomSurfaceXY(mSurface, mRotation, mScale.x, mScale.y, mSmooth);

        if (surface)
        {
            SDL_Rect position;
            
            position.h = 0;
            position.w = 0;
            position.x = mPosition.x;
            position.y = mPosition.y;

            SDL_BlitSurface(surface, NULL, drawSurface, &position);
            SDL_FreeSurface(surface);
        }
    }
}