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

void ElementButton::parse(const std::string& key, const std::string& value)
{
	std::string sContent("content");
	std::string sImg("img-");
	std::string sFont("font-");

	if (key.find(sContent) == 0)
	{
		mLabel.setText(value);
	}
	else if (key.find(sImg) == 0)
	{
		std::string subkey = key.substr(sImg.size());
		std::string sOnIdle("onidle-");
		std::string sOnFocus("onfocus-");
		std::string sOnSelect("onselect-");

		if (subkey.find(sOnIdle) == 0)
			mImage[ONIDLE].parse(subkey.substr(sOnIdle.size()), value);
		else if (subkey.find(sOnFocus) == 0)
			mImage[ONFOCUS].parse(subkey.substr(sOnFocus.size()), value);
		else if (subkey.find(sOnSelect) == 0)
			mImage[ONSELECT].parse(subkey.substr(sOnSelect.size()), value);
	}
	else if (key.find(sFont) == 0)
		mLabel.parse(key.substr(sFont.size()), value);
}

bool ElementButton::collide(double x, double y)
{
    if (x > mPosition.x && x < mPosition.x + mImage[mCurrentState].getWidth()
            && y > mPosition.y && y < mPosition.y + mImage[mCurrentState].getHeight())
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

Text& ElementButton::label()
{
	return mLabel;
}

Image& ElementButton::imageOnIdle()
{
	return mImage[ONIDLE];
}

Image& ElementButton::imageOnFocus()
{
	return mImage[ONFOCUS];
}

Image& ElementButton::imageOnSelect()
{
	return mImage[ONSELECT];
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