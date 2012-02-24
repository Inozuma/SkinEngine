/* 
 * File:   Image.cpp
 * Author: inozuma
 * 
 * Created on January 23, 2012, 2:55 AM
 */

#include "Skin/Image.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace Skin;

Image::Image() :
mSurface(NULL),
mRotation(0),
mScale(1, 1),
mSmooth(0),
mWidth(0),
mHeight(0),
mOriginH(0),
mOriginV(0)
{
}

Image::Image(const std::string& filename) :
mSurface(NULL),
mRotation(0),
mScale(1, 1),
mSmooth(0),
mWidth(0),
mHeight(0),
mOriginH(0),
mOriginV(0)
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

double Image::getRotation() const
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

void Image::setPosition(double x, double y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Image::setRotation(double rotation)
{
    mRotation = rotation;
}

void Image::setScale(const Vectorf& scale)
{
    mScale = scale;
}

void Image::setScale(double x, double y)
{
    mScale.x = x;
    mScale.y = y;
}

void Image::setSmooth(bool smooth)
{
    mSmooth = smooth ? true : false;
}

void Image::setOrigin(double h, double v)
{
	mOriginH = h;
	mOriginV = v;

	if (mOriginH < 0)
		mOriginH = 0;
	else if (mOriginH > 1)
		mOriginH = 1;
	if (mOriginV < 0)
		mOriginV = 0;
	else if (mOriginV > 1)
		mOriginV = 1;
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
            position.x = static_cast<Sint16>(mPosition.x + mWidth * mOriginH);
            position.y = static_cast<Sint16>(mPosition.y + mHeight * mOriginV);

            SDL_BlitSurface(surface, NULL, drawSurface, &position);
            SDL_FreeSurface(surface);
        }
    }
}

void Image::parse(const std::string& key, const std::string& value)
{
	if (key == "file")
	{
		openFile(value);
		return ;
	}

	std::vector<std::string> strings;
	boost::split(strings, value, boost::is_any_of("\t "));
	double x = 0;
	double y = 0;
	if (strings.size() == 2)
	{
		x = atof(strings[0].c_str());
		y = atof(strings[1].c_str());
	}

	if (key == "scale")
		setScale(x, y);
	else if (key == "rotation")
		setRotation(atof(strings[0].c_str()));
	else if (key == "origin")
		setOrigin(x, y);
}