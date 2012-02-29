/* 
 * File:   Element.cpp
 * Author: Inozuma
 * 
 * Created on December 11, 2011, 3:35 AM
 */

#include "Skin/Element.h"

#include <SDL/SDL.h>

#include <vector>
#include <boost/algorithm/string.hpp>

using namespace Skin;

Element::Element(Screen & screen, const Vectorf & position, bool dynamic) :
mScreen(screen),
mPosition(position),
mDynamic(dynamic),
mColor(),
mEffectColor(),
mTranslation(0, 0),
mRotation(0),
mScale(1, 1)
{
}

Element::~Element()
{
}

Screen& Element::getScreen()
{
    return this->mScreen;
}

std::string Element::getData(const std::string& name)
{
    return "";
}

bool Element::isDynamic() const
{
    return mDynamic;
}

bool Element::isBusy() const
{
	return !mActiveEffects.empty();
}

void Element::addEffect(const std::string& eventName, Effect* effect)
{
    mEffects[eventName].push_back(effect);
}

void Element::addAction(const std::string& eventName, Action* action)
{
    mActions[eventName].push_back(action);
}

void Element::setPosition(const Vectorf & position)
{
    this->mPosition = position;
}

const Vectorf & Element::getPosition() const
{
    return mPosition;
}

void Element::setColor(const Color& color)
{
    this->mColor = color;
}

const Color& Element::getColor() const
{
    return this->mColor;
}

const Color& Element::getColorize() const
{
    return mEffectColor;
}

void Element::setColorize(const Color& color)
{
    mEffectColor = color;
}

void Element::setTranslation(const Vectorf & translation)
{
    this->mTranslation = translation;
}

const Vectorf & Element::getTranslation() const
{
    return mTranslation;
}

void Element::setRotation(double rotation)
{
    this->mRotation = rotation;
}

double Element::getRotation() const
{
    return mRotation;
}

void Element::setScale(const Vectorf & scale)
{
    this->mScale = scale;
}

const Vectorf & Element::getScale() const
{
    return mScale;
}

void Element::parse(const std::string& key, const std::string& value)
{
	if (key == "position")
	{
		std::vector<std::string> values;
		boost::split(values, value, boost::is_any_of("\t "));

		if (values.size() == 1)
			mPosition.x = atof(values[0].c_str());
		if (values.size() == 2)
			mPosition.y = atof(values[1].c_str());
	}
}

void Element::eventKey(const EventKey& key)
{
	switch (key.sym)
    {
        case SDLK_UP:
            this->onUp();
            break;

        case SDLK_DOWN:
            this->onDown();
            break;

        case SDLK_LEFT:
            this->onLeft();
            break;

        case SDLK_RIGHT:
            this->onRight();
            break;

        case SDLK_RETURN:
            this->onSelect();
            break;

        default:
            break;
    }
}

void Element::eventMouseButton(const EventMouseButton&)
{
}

void Element::eventMouseMoved(const EventMouseMotion&)
{
}

void Element::update(double time)
{
    if (!this->mActiveEffects.empty())
    {
        EffectList& currentEffects = this->mActiveEffects.front();

        for (EffectList::iterator it = currentEffects.begin();
                it != currentEffects.end();) 
        {
            (*it)->update<Element>(*this, time);
            if ((*it)->isActive() == false)
            {
                delete (*it);
                currentEffects.erase(it);
                it = currentEffects.begin();
            }
            else
              ++it;
        }

        if (currentEffects.empty())
            this->mActiveEffects.pop_front();
    }
}

void Element::onUp()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onUp"].begin();
            it != this->mEffects["onUp"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    // execute actions
    for (ActionList::iterator it = this->mActions["onUp"].begin();
            it != this->mActions["onUp"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onDown()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onDown"].begin();
            it != this->mEffects["onDown"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onDown"].begin();
            it != this->mActions["onDown"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onLeft()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onLeft"].begin();
            it != this->mEffects["onLeft"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onLeft"].begin();
            it != this->mActions["onLeft"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onRight()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onRight"].begin();
            it != this->mEffects["onRight"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onRight"].begin();
            it != this->mActions["onRight"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onSelect()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onSelect"].begin();
            it != this->mEffects["onSelect"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onSelect"].begin();
            it != this->mActions["onSelect"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onIdle()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onIdle"].begin();
            it != this->mEffects["onIdle"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onIdle"].begin();
            it != this->mActions["onIdle"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onFocus()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onFocus"].begin();
            it != this->mEffects["onFocus"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onFocus"].begin();
            it != this->mActions["onFocus"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onUnfocus()
{
    // add effects
    EffectList copy;
    for (EffectList::iterator it = this->mEffects["onUnfocus"].begin();
            it != this->mEffects["onUnfocus"].end(); ++it)
    {
        copy.push_back(new Effect(**it));
    }
    this->mActiveEffects.push_back(copy);
    // execute actions
    for (ActionList::iterator it = this->mActions["onUnfocus"].begin();
            it != this->mActions["onUnfocus"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onLoad()
{
    // add effects
	if (mEffects["onLoad"].size())
	{
		EffectList copy;
		for (EffectList::iterator it = this->mEffects["onLoad"].begin();
				it != this->mEffects["onLoad"].end(); ++it)
		{
			copy.push_back(new Effect(**it));
		}
		this->mActiveEffects.push_back(copy);
	}
    // execute actions
    for (ActionList::iterator it = this->mActions["onLoad"].begin();
            it != this->mActions["onLoad"].end(); ++it)
    {
        (*it)->execute();
    }
}

void Element::onUnload()
{
    // add effects
	if (mEffects["onUnload"].size())
	{
		EffectList copy;
		for (EffectList::iterator it = this->mEffects["onUnload"].begin();
				it != this->mEffects["onUnload"].end(); ++it)
		{
			copy.push_back(new Effect(**it));
		}
		this->mActiveEffects.push_back(copy);
	}
    // execute actions
    for (ActionList::iterator it = this->mActions["onUnload"].begin();
            it != this->mActions["onUnload"].end(); ++it)
    {
        (*it)->execute();
    }
}