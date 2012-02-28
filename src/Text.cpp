/* 
 * File:   Text.cpp
 * Author: inozuma
 * 
 * Created on January 23, 2012, 5:23 AM
 */

#include "Skin/Text.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <iostream>

using namespace Skin;

Text::Text(const std::string& text, const std::string& fontname, unsigned int fontsize) :
mText(text),
mFont(NULL),
mColor(255, 255, 255, 1)
{
    this->loadFont(fontname, fontsize);
}

Text::~Text()
{
    if (mFont)
    {
        TTF_CloseFont(mFont);
        mFont = NULL;
    }
}

const Vectorf& Text::getPosition() const
{
    return mPosition;
}

double Text::getRotation() const
{
    return mRotation;
}

const Vectorf& Text::getScale() const
{
    return mScale;
}

const std::string& Text::getText() const
{
    return mText;
}

const std::string& Text::getName() const
{
    return mName;
}

unsigned int Text::getSize() const
{
    return mSize;
}

const Color& Text::getColor() const
{
    return mColor;
}

int Text::getWidth() const
{
    return mWidth;
}

int Text::getHeight() const
{
    return mHeight;
}

int Text::getMaxHeight() const
{
    return TTF_FontHeight(mFont);
}

void Text::setPosition(const Vectorf& position)
{
    mPosition = position;
}

void Text::setPosition(double x, double y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void Text::setRotation(double rotation)
{
    mRotation = rotation;
}

void Text::setScale(const Vectorf& scale)
{
    mScale = scale;
}

void Text::setScale(double x, double y)
{
    mScale.x = x;
    mScale.y = y;
}

void Text::setText(const std::string& text)
{
    mText = text;
}

void Text::setName(const std::string& fontname)
{
    loadFont(fontname, mSize);
}

void Text::setSize(unsigned int fontsize)
{
    mSize = fontsize;
    loadFont(mName, fontsize);
}

void Text::setColor(const Color& color)
{
    mColor = color;
}

void Text::draw(SDL_Surface* drawSurface, unsigned int width, unsigned height)
{
    if (mFont)
    {
        SDL_Color color;
        color.r = mColor.r;
        color.g = mColor.g;
        color.b = mColor.b;
        SDL_Surface* surface = TTF_RenderText_Blended(mFont, mText.c_str(), color);
        if (surface)
        {
            SDL_Rect dstrec;
			SDL_Rect srcrec;
            dstrec.w = 0;
            dstrec.h = 0;
            dstrec.x = short(mPosition.x);
            dstrec.y = short(mPosition.y);
			srcrec.w = width;
			srcrec.h = height;
			srcrec.x = 0;
			srcrec.y = 0;
			if (width && height)
				SDL_BlitSurface(surface, &srcrec, drawSurface, &dstrec);
			else
				SDL_BlitSurface(surface, NULL, drawSurface, &dstrec);
            SDL_FreeSurface(surface);
        }
    }
}

void Text::parse(const std::string& key, const std::string& value)
{
	if (key == "text")
		setText(value);
	else if (key == "name")
		setName(value);
	else if (key == "size")
		setSize(atoi(value.c_str()));
	else if (key == "color")
		setColor(value);
	else if (key == "bold")
		TTF_SetFontStyle(mFont, TTF_STYLE_BOLD);
	else if (key == "italic")
		TTF_SetFontStyle(mFont, TTF_STYLE_ITALIC);
	else if (key == "underline")
		TTF_SetFontStyle(mFont, TTF_STYLE_UNDERLINE);
	else if (key == "strike")
		TTF_SetFontStyle(mFont, TTF_STYLE_STRIKETHROUGH);
}

void Text::loadFont(const std::string& fontname, unsigned int fontsize)
{
    if (mFont)
    {
        TTF_CloseFont(mFont);
        mFont = NULL;
    }
    if (TTF_WasInit())
    {
        mFont = TTF_OpenFont(fontname.c_str(), fontsize);
        if (mFont)
        {
            mName = fontname;
            TTF_SizeText(mFont, mText.c_str(), &mWidth, &mHeight);
        }
        else
        {
            std::cerr << "Could not load font `" << fontname << "`: " << TTF_GetError() << std::endl;
        }
    }
}