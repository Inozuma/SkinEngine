/* 
 * File:   Screen.h
 * Author: Inozuma
 *
 * Created on December 10, 2011, 11:09 PM
 */

#ifndef SCREEN_H
#define	SCREEN_H

#include "Skin/Element.h"
#include "Skin/Image.h"
#include "Skin/Events.h"

#include <map>
#include <string>

typedef std::map<int, Skin::Element*> ElementMap;
typedef std::pair<int, Skin::Element*> ElementPair;

namespace Skin
{
    class Engine;

    class Screen
    {
    private:
        Engine & mCore;
        
        ElementMap mElements;
        int mActiveElement;
        
        ActionMap mActions;
        EffectMap mEffects;
        EffectList mActiveEffects;
        
        Image mBackground;

    public:
        Screen(Engine &);
        virtual ~Screen();
        
        Engine& getCore();

        void addElement(int, Element *);
        void deleteElement(int);
        Element* getElement(int);
        
		int getActiveElement() const;
        void setActiveElement(int);
        
        void setBackground(const std::string&);

		void eventQuit();
		void eventKeyPressed(EventKey const &);
		void eventKeyReleased(EventKey const &);
		void eventMouseButtonPressed(EventMouseButton const &);
		void eventMouseButtonReleased(EventMouseButton const &);
		void eventMouseMoved(EventMouseMotion const &);
        void update(double);
        void draw(SDL_Surface* displaySurface);
        
        // Interface Callback
        void onLoad();
        void onUnload();
        void onEscape();
    };
}

#endif	/* SCREEN_H */

