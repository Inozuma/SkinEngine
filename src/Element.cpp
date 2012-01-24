/* 
 * File:   Element.cpp
 * Author: Inozuma
 * 
 * Created on December 11, 2011, 3:35 AM
 */

#include <SFML/Window/Event.hpp>

#include "Skin/Element.h"

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

bool Element::getDynamic() const
{
    return mDynamic;
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

const Color& Element::getEffectColor() const
{
    return mEffectColor;
}

void Element::setEffectColor(const Color& color)
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

void Element::setRotation(float rotation)
{
    this->mRotation = rotation;
}

float Element::getRotation() const
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

void Element::event(const SDL_Event& event)
{
    // TODO : Mouse?
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
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
}

void Element::update(float time)
{
    if (!this->mActiveEffects.empty())
    {
        mEffectColor = Color(0, 0, 0, 0);
        mTranslation = Vectorf();
        mRotation = 0;
        mScale = Vectorf();

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