/* 
 * File:   Effect.cpp
 * Author: Inozuma
 * 
 * Created on December 12, 2011, 10:15 AM
 */

#include "Skin/Effect.h"
#include "Skin/Screen.h"
#include "Skin/Element.h"

using namespace Skin;

Effect::Effect(double start, double end,
        const Vectorf & translation, double rotation,
        const Vectorf & scale, const Color & color) :
mActive(true),
mTime(0),
mStart(start),
mEnd(end),
mLength(end - start),
mTranslation(translation),
mRotation(rotation),
mScale(scale),
mColor(color)
{
}

Effect::~Effect()
{
}

void Effect::setColor(const Color& mColor)
{
    this->mColor = mColor;
}

const Color& Effect::getColor() const
{
    return mColor;
}

void Effect::setScale(const Vectorf& mScale)
{
    this->mScale = mScale;
}

const Vectorf& Effect::getScale() const
{
    return mScale;
}

void Effect::setRotation(double mRotation)
{
    this->mRotation = mRotation;
}

double Effect::getRotation() const
{
    return mRotation;
}

void Effect::setTranslation(const Vectorf& mTranslation)
{
    this->mTranslation = mTranslation;
}

const Vectorf& Effect::getTranslation() const
{
    return mTranslation;
}

void Effect::setEnd(double mEnd)
{
    this->mEnd = mEnd;
}

double Effect::getEnd() const
{
    return mEnd;
}

void Effect::setStart(double mStart)
{
    this->mStart = mStart;
}

double Effect::getStart() const
{
    return mStart;
}

bool Effect::isActive() const
{
    return this->mActive;
}

template<>
void Effect::update<Element>(Element& element, double time)
{
    if (this->mActive)
    {
        this->mTime += time;
        if (this->mTime >= this->mStart && this->mTime < this->mEnd)
        {
            double pos = (this->mTime - this->mStart) / this->mLength;
            element.setTranslation(element.getTranslation() + this->mTranslation * pos);
            element.setRotation(element.getRotation() + this->mRotation * pos);
            element.setScale(element.getScale() + this->mScale * pos);
			element.setColorize(element.getColorize() + this->mColor * pos);
        }
        else if (this->mTime >= this->mEnd)
        {
            element.setTranslation(element.getTranslation() + this->mTranslation);
            element.setRotation(element.getRotation() + this->mRotation);
            element.setScale(element.getScale() + this->mScale);
			element.setColorize(element.getColorize() + this->mColor);
            this->mActive = false;
        }
    }
}

template<>
void Effect::update<Screen>(Screen&, double)
{
}