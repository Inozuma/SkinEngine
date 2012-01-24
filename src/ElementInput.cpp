/* 
 * File:   ElementInput.cpp
 * Author: Inozuma
 * 
 * Created on January 10, 2012, 10:39 AM
 */

#include "Skin/ElementInput.h"

using namespace Skin;

ElementInput::ElementInput(Screen& screen, const Vectorf & position, float size) :
Element(screen, position),
mLabel(""),
mSize(size),
mSelect(false)
{
    mBox.setPosition(mPosition.x, mPosition.y);
    mBox.setSize(size, mLabel.getMaxHeight() * 1.25);
    mBox.setBoxColor(Color(255, 255, 255, 0.4));
    mBox.setOutlineColor(Color(255, 255, 255, 1));
}

ElementInput::~ElementInput()
{
}

std::string ElementInput::getData(const std::string& name)
{
    if (name == "value")
        return mText;
    return "";
}

bool ElementInput::collide(float x, float y)
{

    if (x > mPosition.x && x < mPosition.x + mSize &&
            y > mPosition.y && y < mPosition.y + mLabel.getMaxHeight())
        return true;
    return false;
}

void ElementInput::draw(SDL_Surface* displaySurface)
{
    mLabel.setText(mText + (mSelect ? "|" : ""));
    mLabel.setPosition(mPosition.x + mTranslation.x + mLabel.getMaxHeight() / 4, mPosition.y + mTranslation.y);
    mLabel.setScale(1 + mScale.x, 1 + mScale.y);
    
    mBox.draw(displaySurface);
    mLabel.draw(displaySurface);
}

void ElementInput::event(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN
            && event.key.keysym.sym != SDLK_RETURN
            && event.key.keysym.sym != SDLK_BACKSPACE
            && event.key.keysym.sym != SDLK_DELETE
            && event.key.keysym.unicode != 0
            && event.key.keysym.unicode != '\r'
            && event.key.keysym.unicode != '\n'
            && event.key.keysym.unicode != '\b')
    {
        if (event.key.keysym.sym != SDLK_BACKSPACE)
            mText.push_back(event.key.keysym.unicode);
    }
    else if (event.type == SDL_KEYDOWN)
    {
        if ((event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_DELETE)
                && !mText.empty())
        {
            mText.resize(mText.size() - 1);
        }
        else
            Element::event(event);
    }
}

void ElementInput::onFocus()
{
    mSelect = true;
    Element::onFocus();
}

void ElementInput::onIdle()
{
    mSelect = false;
    Element::onIdle();
}

void ElementInput::setFontname(const std::string& fontname)
{
    mLabel.setName(fontname);
}

void ElementInput::setFontsize(unsigned int fontsize)
{
    mLabel.setSize(fontsize);
}

void ElementInput::setFontcolor(const Color& color)
{
    mLabel.setColor(color);
}

void ElementInput::setBoxColor(const Color& color)
{
    mBox.setBoxColor(color);
}

void ElementInput::setOutlineColor(const Color& color)
{
    mBox.setOutlineColor(color);
}

void ElementInput::setRadius(int radius)
{
    mBox.setRadius(radius);
}

void ElementInput::setSize(float size)
{
    mSize = size;
    mBox.setSize(mPosition.x + size, mPosition.y + mLabel.getMaxHeight());
}

void ElementInput::setText(const std::string& text)
{
    mText = text;
}

const std::string& ElementInput::getFontname() const
{
    return mLabel.getName();
}

unsigned int ElementInput::getFonsize() const
{
    return mLabel.getSize();
}

const Color& ElementInput::getFontcolor() const
{
    return mLabel.getColor();
}

float ElementInput::getSize() const
{
    return mSize;
}

const std::string& ElementInput::getText() const
{
    return mText;
}