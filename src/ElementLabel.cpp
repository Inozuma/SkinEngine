/* 
 * File:   ElementText.cpp
 * Author: Inozuma
 * 
 * Created on January 8, 2012, 8:43 PM
 */

#include "Skin/ElementLabel.h"

#include <iostream>

using namespace Skin;

ElementLabel::ElementLabel(Screen& screen, const Vectorf & position, const std::string & label) :
Element(screen, position, false),
mLabel(label)
{
}

ElementLabel::~ElementLabel()
{
}

bool ElementLabel::collide(float x, float y)
{
    (void) x;
    (void) y;
    return false;
}

void ElementLabel::draw(SDL_Surface* displaySurface)
{
    mLabel.setPosition(mPosition.x, mPosition.y);
    
    mLabel.draw(displaySurface);
}

void ElementLabel::setLabel(const std::string& label)
{
    mLabel.setText(label);
}

void ElementLabel::setFontname(const std::string& fontname)
{
    mLabel.setName(fontname);
}

void ElementLabel::setFontsize(unsigned int fontsize)
{
    mLabel.setSize(fontsize);
}

void ElementLabel::setFontcolor(const Color& fontcolor)
{
    mLabel.setColor(fontcolor);
}

const std::string& ElementLabel::getLabel() const
{
    return mLabel.getText();
}

unsigned int ElementLabel::getFontsize() const
{
    return mLabel.getSize();
}

const std::string & ElementLabel::getFontname() const
{
    return mLabel.getName();
}

const Color & ElementLabel::getFontcolor() const
{
    return mLabel.getColor();
}