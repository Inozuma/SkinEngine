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

void ElementLabel::parse(const std::string& key, const std::string& value)
{
	std::string sContent("content");
	std::string sFont("font-");

	if (key.find(sContent) == 0)
	{
		mLabel.setText(value);
	}
	else if (key.find(sFont) == 0)
	{
		mLabel.parse(key.substr(sFont.size()), value);
	}
}

bool ElementLabel::collide(double x, double y)
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

Text& ElementLabel::label()
{
	return mLabel;
}