/* 
 * File:   ElementList.cpp
 * Author: Inozuma
 * 
 * Created on January 10, 2012, 4:00 PM
 */

#include "Skin/ElementList.h"
#include "Skin/ElementLabel.h"

#include "Skin/Screen.h"
#include "Skin/Engine.h"

using namespace Skin;

ElementList::ElementList(Screen& screen, const Vectorf& position,
        const std::string& value, const Vectorf& size) :
Element(screen, position, true),
mValue(value),
mBoxsize(size),
mFont(""),
mIndex(0),
mOffset(0),
mMax(0)
{
    mBox.setPosition(mPosition.x, mPosition.y);
    mBox.setSize(mBoxsize.x, mBoxsize.y);
    mBox.setBoxColor(Color(255, 255, 255, 0.2));
    mBox.setOutlineColor(Color(255, 255, 255, 1));
    mMax = mBoxsize.y / mFont.getMaxHeight();
}

ElementList::~ElementList()
{
}

std::string ElementList::getData(const std::string& name)
{
    if (name == "value")
    {
        if (mValues.empty())
            return "";
        return mValues[mIndex + mOffset];
    }
    return "";
}

bool ElementList::collide(float x, float y)
{
    if (x > mPosition.x && x < mPosition.x + mBoxsize.x
            && y > mPosition.y && y < mPosition.y + mBoxsize.y)
        return true;
    return false;
}

void ElementList::draw(SDL_Surface* displaySurface)
{
    mBox.draw(displaySurface);
    for (int i = 0; i < (signed)mValues.size(); ++i)
    {
        Text text(mValues[i + mOffset]);

        text.setPosition(mPosition.x + mFont.getMaxHeight() / 2,
                mPosition.y + mFont.getMaxHeight() / 4 + i * mFont.getMaxHeight());
        text.setColor(Color(255, 255, 255, 1));
        if (i == mIndex)
        {
            Box hl;
            hl.setPosition(mPosition.x, mPosition.y + mFont.getMaxHeight() / 4 + i * mFont.getMaxHeight());
            hl.setSize(mBoxsize.x, mFont.getMaxHeight() * 1.25);
            hl.draw(displaySurface);
        }
        if (i < (signed)mMax)
        {
            text.draw(displaySurface);
        }
        else
            break ;
    }
}

void ElementList::update(float time)
{
    parseDynamicData();
    Element::update(time);
}

void ElementList::onUp()
{
    mIndex--;
    if (mIndex < 0)
    {
        mIndex = 0;
        mOffset--;
        if (mOffset < 0)
        {
            mOffset = 0;
            Element::onUp();
        }
    }
}

void ElementList::onDown()
{
    mIndex++;
    if (mIndex > (signed)mValues.size() - 1)
    {
        mIndex--;
        Element::onDown();
    }
    else if (mIndex > (signed)mMax - 1)
    {
        mIndex--;
        mOffset++;
        if (mOffset + mIndex > (signed)mValues.size() - 1)
        {
            mOffset--;
            Element::onDown();
        }
    }
}

void ElementList::setFontname(const std::string& fontname)
{
    mFont.setName(fontname);
    mMax = mBoxsize.y / mFont.getMaxHeight();
}

void ElementList::setFontsize(unsigned int size)
{
    mFont.setSize(size);
}

void ElementList::parseDynamicData()
{
    size_t pos;

    if ((pos = mValue.find('.')) == std::string::npos)
        return ;

    std::string moduleName = mValue.substr(0, pos);
    std::string dataName = mValue.substr(pos + 1, mValue.size() - 1);

    Module* module = mScreen.getCore().getModule(moduleName);
    if (module)
        mValues = module->getDynamicData<std::vector<std::string> >(dataName);
    return ;
}