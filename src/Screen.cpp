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

void Screen::setBackground(const std::string& file)
{
	if (mBackground.openFile(file))
	{
		SDL_Surface* video = SDL_GetVideoSurface();
		mBackground.setScale(double(video->w / mBackground.getWidth()),
				double(video->h / mBackground.getHeight()));
	}
}

void Screen::event(const SDL_Event& event)
{
    if (event.type == SDL_QUIT)
    {
        this->mCore.quit();
    }
    else if (event.type == SDL_KEYDOWN
            && event.key.keysym.sym == SDLK_ESCAPE)
    {
        this->onEscape();
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
        for (ElementMap::iterator it = mElements.begin();
                it != mElements.end(); ++it)
        {
            if (it->second->isDynamic()
                    && it->second->collide(event.motion.x, event.motion.y))
            {
                this->setActiveElement(it->first);
                break;
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (mActiveElement != -1 &&
                mElements[mActiveElement]->collide(event.motion.x, event.motion.y))
            mElements[mActiveElement]->onSelect();
    }
    else if (this->mActiveElement != -1
            && event.type == SDL_KEYDOWN)
    {
        this->mElements[this->mActiveElement]->event(event);
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

void Screen::onLoad()
{
    // TODO
}

void Screen::onUnload()
{
    // TODO
}

void Screen::onEscape()
{
    // TODO
    this->mCore.quit();
}