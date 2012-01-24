/* 
 * File:   ElementButton.cpp
 * Author: Inozuma
 * 
 * Created on January 10, 2012, 11:22 PM
 */

#include "Skin/ElementButton.h"

using namespace Skin;

ElementButton::ElementButton(Screen& screen, const Vectorf& position,
        const std::string& label) :
Element(screen, position),
mLabel(label),
mCurrentState(ONIDLE)
{
}

ElementButton::~ElementButton()
{
}

bool ElementButton::collide(float x, float y)
{
    if (x > mPosition.x && x < mPosition.x + mLabel.getWidth()
            && y > mPosition.y && y < mPosition.y + mLabel.getHeight())
        return true;
    return false;
}

void ElementButton::draw(SDL_Surface* displaySurface)
{
    // Image transformation
    mImage[mCurrentState].setPosition(mPosition.x + mTranslation.x, mPosition.y + mTranslation.y);
    // String transformation
    mLabel.setPosition(mPosition.x + mTranslation.x, mPosition.y + mTranslation.y);

    // Rendering
    mImage[mCurrentState].draw(displaySurface);
    mLabel.draw(displaySurface);
}

void ElementButton::onIdle()
{
    mCurrentState = ONIDLE;
    Element::onIdle();
}

void ElementButton::onFocus()
{
    mCurrentState = ONFOCUS;
    Element::onFocus();
}

void ElementButton::onSelect()
{
    mCurrentState = ONSELECT;
    Element::onSelect();
}

void ElementButton::setFontname(const std::string& fontname)
{
    mLabel.setName(fontname);
}

void ElementButton::setFontsize(unsigned int fontsize)
{
    mLabel.setSize(fontsize);
}

void ElementButton::setFontcolor(const Color& fontcolor)
{
    mLabel.setColor(fontcolor);
}

void ElementButton::setImageOnIdle(const std::string& image)
{
    mImage[ONIDLE].openFile(image);
}

void ElementButton::setImageOnFocus(const std::string& image)
{
    mImage[ONFOCUS].openFile(image);
}

void ElementButton::setImageOnSelect(const std::string& image)
{
    mImage[ONSELECT].openFile(image);
}