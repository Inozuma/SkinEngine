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

#include <sigc++/functors/mem_fun.h>

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
    mMax = static_cast<int>(mBoxsize.y / mFont.getMaxHeight());
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

Text& ElementList::label()
{
	return mFont;
}

Box& ElementList::box()
{
	return mBox;
}

void ElementList::parse(const std::string& key, const std::string& value)
{
	if (key == "value")
	{
		if (parseDynamicData(value) == true)
		{
			mValue = value;
			Module *module = mScreen.getCore().getModule(mModuleName);
			module->dataChangedSignal.connect(sigc::mem_fun(this, &ElementList::dataChangedSlot));
		}
	}
	else
	{
		std::string sSize("size-");
		std::string sFont("font-");
		std::string sBox("box-");

		if (key.find(sSize) == 0)
		{
			std::string subkey(key.substr(sSize.size()));

			if (subkey == "width")
				mBoxsize.x = atof(value.c_str());
			else if (subkey == "height")
				mBoxsize.y = atof(value.c_str());
			mBox.setSize(mBoxsize.x, mBoxsize.y);
			mMax = static_cast<int>(mBoxsize.y / mFont.getMaxHeight());
		}
		else if (key.find(sFont) == 0)
		{
			mFont.parse(key.substr(sFont.size()), value);
			mMax = static_cast<int>(mBoxsize.y / mFont.getMaxHeight());
		}
		else if (key.find(sBox) == 0)
		{
			mBox.parse(key.substr(sBox.size()), value);
			mMax = static_cast<int>(mBoxsize.y / mFont.getMaxHeight());
		}
	}
}

bool ElementList::collide(double x, double y)
{
    if (x > mPosition.x && x < mPosition.x + mBoxsize.x
            && y > mPosition.y && y < mPosition.y + mBoxsize.y)
        return true;
    return false;
}

void ElementList::draw(SDL_Surface* displaySurface)
{
    mBox.draw(displaySurface);
	if (mValues.size())
	{
		Box hl;
		hl.setBoxColor(Color("#424242"));
        hl.setPosition(mPosition.x, mPosition.y + mIndex * mFont.getMaxHeight());
        hl.setSize(mBoxsize.x, mFont.getMaxHeight() + mFont.getMaxHeight() / 2);
        hl.draw(displaySurface);
	}
    for (int i = 0; i + mOffset < (signed)mValues.size(); ++i)
    {
        Text text(mValues[i + mOffset]);

        text.setPosition(mPosition.x + mFont.getMaxHeight() / 2,
                mPosition.y + mFont.getMaxHeight() / 4 + i * mFont.getMaxHeight());
        text.setColor(Color(255, 255, 255, 1));
        if (i < (signed)mMax)
        {
            text.draw(displaySurface, mBoxsize.x - mFont.getMaxHeight() / 2, mBoxsize.y);
        }
        else
            break ;
    }
}

void ElementList::update(double time)
{
    //parseDynamicData();
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

bool ElementList::parseDynamicData(const std::string & value)
{
    size_t pos;

    if ((pos = value.find('.')) == std::string::npos)
        return false;

    mModuleName = value.substr(0, pos);
    mDataName = value.substr(pos + 1, value.size() - 1);

    Module* module = mScreen.getCore().getModule(mModuleName);
    if (module)
	{
        mValues = module->getDynamicData<std::vector<std::string> >(mDataName);
		return true;
	}
	else
	{
		return false;
	}
}

void ElementList::dataChangedSlot(const std::string & name)
{
	if (name == mDataName)
	{
		Module* module = mScreen.getCore().getModule(mModuleName);
		mValues = module->getDynamicData<std::vector<std::string> >(mDataName);
	}
}