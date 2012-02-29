#include "Skin/ElementVideo.h"
#include "Skin/Screen.h"
#include "Skin/Engine.h"

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

using namespace Skin;

ElementVideo::ElementVideo(Screen& screen, const Vectorf& pos) :
Element(screen, pos, false),
	mWidth(0),
	mHeight(0),
	mMutex(NULL),
	mSurface(NULL)
{
}

ElementVideo::~ElementVideo(void)
{
}

void ElementVideo::parse(const std::string& key, const std::string& value)
{
	std::string sSize("size-");
	std::string sValue("value-");

	if (key.find(sValue) == 0)
	{
		std::string subkey(key.substr(sValue.size()));

		if (subkey == "video")
			mValueSurface = value;
		else if (subkey == "mutex")
			mValueMutex = value;
	}
	else if (key.find(sSize) == 0)
	{
		std::string subkey(key.substr(sSize.size()));

		if (subkey == "width")
			mWidth = atof(value.c_str());
		else if (subkey == "height")
			mHeight = atof(value.c_str());
	}
}

bool ElementVideo::collide(double x, double y)
{
	if (x > mPosition.x && x < mPosition.x + mWidth
		&& y > mPosition.y && y < mPosition.y + mHeight)
		return true;
	return false;
}

void ElementVideo::draw(SDL_Surface* displaySurface)
{
	if (mMutex == NULL)
		parseDynamicDataMutex();
	if (mSurface == NULL)
		parseDynamicDataSurface();

	if (mSurface)
	{
		if (mMutex)
			SDL_LockMutex(mMutex);
		SDL_Rect pos;
		SDL_Surface* zoomedSurface = zoomSurface(mSurface, mWidth / double(mSurface->w), mHeight / double(mSurface->h), 1);
		pos.x = static_cast<Sint16>(mPosition.x);
		pos.y = static_cast<Sint16>(mPosition.y);
		pos.w = 0;
		pos.h = 0;
		SDL_BlitSurface(zoomedSurface, NULL, displaySurface, &pos);
		SDL_FreeSurface(zoomedSurface);
		if (mMutex)
			SDL_UnlockMutex(mMutex);
	}
}

void ElementVideo::parseDynamicDataSurface()
{
    size_t pos;

    if ((pos = mValueSurface.find('.')) == std::string::npos)
        return ;

    std::string moduleName = mValueSurface.substr(0, pos);
    std::string dataName = mValueSurface.substr(pos + 1, mValueSurface.size() - 1);

    Module* module = mScreen.getCore().getModule(moduleName);
    if (module)
        mSurface = module->getDynamicData<SDL_Surface*>(dataName);
    return ;
}

void ElementVideo::parseDynamicDataMutex()
{
    size_t pos;

    if ((pos = mValueMutex.find('.')) == std::string::npos)
        return ;

    std::string moduleName = mValueMutex.substr(0, pos);
    std::string dataName = mValueMutex.substr(pos + 1, mValueMutex.size() - 1);

    Module* module = mScreen.getCore().getModule(moduleName);
    if (module)
        mMutex = module->getDynamicData<SDL_mutex*>(dataName);
    return ;
}