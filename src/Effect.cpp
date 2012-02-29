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

void Effect::setStartScale(const Vectorf& scale)
{
	mStartScale = scale;
}

void Effect::setStartAngle(double angle)
{
	mStartAngle = angle;
}

void Effect::setStartPosition(const Vectorf& position)
{
	mStartPosition = position;
}

void Effect::setStartColor(const Color& color)
{
	mStartColor = color;
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
    if (mActive)
    {
		if (mTime == 0)
		{
			element.setTranslation(mStartPosition);
			element.setRotation(mStartAngle);
			element.setScale(mStartScale);
			element.setColorize(mStartColor);
		}
        mTime += time;
        if (mTime >= mStart && mTime < mEnd)
        {
            double pos = (mTime - mStart) / mLength;
            element.setTranslation(mStartPosition + mTranslation * pos);
            element.setRotation(mStartAngle + mRotation * pos);
            element.setScale(mStartScale + mScale * pos);
			element.setColorize(mStartColor + mColor * pos);
        }
        else if (mTime >= mEnd)
        {
            element.setTranslation(mStartPosition + mTranslation);
            element.setRotation(mStartAngle + mRotation);
            element.setScale(mStartScale + mScale);
			element.setColorize(mStartColor + mColor);
            mActive = false;
        }
    }
}

template<>
void Effect::update<Screen>(Screen&, double)
{
}