/* 
 * File:   Screen.cpp
 * Author: Inozuma
 * 
 * Created on December 10, 2011, 11:09 PM
 */

#include "Skin/Screen.h"
#include "Skin/Engine.h"

#include <SDL/SDL.h>

using namespace Skin;

Screen::Screen(Engine & skinCore) :
mCore(skinCore),
mActiveElement(-1),
mBackground()
{
}

Screen::~Screen()
{
}

Engine& Screen::getCore()
{
    return this->mCore;
}

void Screen::addElement(int id, Element * element)
{
    if (!this->mElements.count(id))
    {
        this->mElements.insert(std::pair<int, Element*>(id, element));
		if (mActiveElement == -1 && element->isDynamic())
			setActiveElement(id);
    }
}

void Screen::deleteElement(int id)
{
    if (this->mElements.count(id))
    {
        this->mElements.erase(id);
    }
}

Element* Screen::getElement(int id)
{
    if (mElements.count(id))
        return mElements[id];
    return NULL;
}

int Screen::getActiveElement() const
{
	return mActiveElement;
}

void Screen::setActiveElement(int id)
{
    if (mActiveElement != id)
    {
        if (mActiveElement != -1)
            mElements[mActiveElement]->onIdle();
        mActiveElement = id;
        mElements[mActiveElement]->onFocus();
    }
}

bool Screen::isBusy() const
{
	for (ElementMap::const_iterator it = mElements.begin(); it != mElements.end(); ++it)
		if (it->second->isBusy())
			return true;
	return false;
}

void Screen::setBackground(const std::string& file)
{
	if (mBackground.openFile(file))
	{
		/*SDL_Surface* video = SDL_GetVideoSurface();
		mBackground.setScale(double(video->w / mBackground.getWidth()),
				double(video->h / mBackground.getHeight()));*/
	}
}

void Screen::update(double time)
{
    for (ElementMap::iterator it = this->mElements.begin();
            it != this->mElements.end(); ++it)
    {
        it->second->update(time);
    }
}

void Screen::draw(SDL_Surface* displaySurface)
{
    mBackground.draw(displaySurface);
    for (ElementMap::iterator it = this->mElements.begin();
            it != this->mElements.end(); ++it)
    {
        it->second->draw(displaySurface);
    }
}

void Screen::eventQuit()
{
	this->mCore.quit();
}

void Screen::eventKeyPressed(EventKey const & key)
{
	if (key.sym == SDLK_ESCAPE)
		this->onEscape();
	else if (mActiveElement != -1)
		mElements[mActiveElement]->eventKey(key);
}

void Screen::eventKeyReleased(EventKey const & key)
{
}

void Screen::eventMouseButtonPressed(EventMouseButton const & mouse)
{
	if (mActiveElement != -1 && mElements[mActiveElement]->collide(mouse.x, mouse.y))
		mElements[mActiveElement]->onSelect();
	else if (mActiveElement != -1)
		mElements[mActiveElement]->eventMouseButton(mouse);
}

void Screen::eventMouseButtonReleased(EventMouseButton const & mouse)
{
}

void Screen::eventMouseMoved(EventMouseMotion const & motion)
{
	for (ElementMap::iterator it = mElements.begin(); it != mElements.end(); ++it)
	{
		if (it->second->isDynamic()	&& it->second->collide(motion.x, motion.y))
		{
			this->setActiveElement(it->first);
			break;
		}
	}
	if (mActiveElement != -1)
		mElements[mActiveElement]->eventMouseMoved(motion);
}

void Screen::onLoad()
{
	for (ElementMap::iterator it = mElements.begin(); it != mElements.end(); ++it)
		it->second->onLoad();
}

void Screen::onUnload()
{
    for (ElementMap::iterator it = mElements.begin(); it != mElements.end(); ++it)
		it->second->onUnload();
}

void Screen::onEscape()
{
    // TODO
    this->mCore.quit();
}