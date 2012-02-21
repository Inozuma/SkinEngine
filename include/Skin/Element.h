/* 
 * File:   Element.h
 * Author: Inozuma
 *
 * Created on December 11, 2011, 3:35 AM
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include "Skin/Vector.h"
#include "Skin/Action.h"
#include "Skin/Effect.h"
#include "Skin/Color.h"
#include "Parser/Node.h"

// need proper abstraction
struct SDL_Surface;
union SDL_Event;

typedef std::list<Skin::Action*> ActionList;
typedef std::list<Skin::Effect*> EffectList;
typedef std::map<std::string, std::list<Skin::Action*> > ActionMap;
typedef std::pair<std::string, std::list<Skin::Action*> > ActionPair;
typedef std::map<std::string, std::list<Skin::Effect*> > EffectMap;
typedef std::pair<std::string, std::list<Skin::Effect*> > EffectPair;
typedef std::list<std::list<Skin::Effect*> > EffectTable;

namespace Skin
{
    class Screen;

    class Element
    {
    protected:
        Screen & mScreen;
        std::map<std::string, std::string> mData;

        Vectorf mPosition;
        bool mDynamic;
        Color mColor;
        
        Color mEffectColor;
        Vectorf mTranslation;
        double mRotation;
        Vectorf mScale;

        ActionMap mActions;
        EffectMap mEffects;
        EffectTable mActiveEffects;

    public:
        Element(Screen &, const Vectorf & = Vectorf(), bool = true);
        virtual ~Element();

        Screen& getScreen();
        
        virtual std::string getData(const std::string&);

        bool isDynamic() const;

        void addEffect(const std::string &, Effect*);
        void addAction(const std::string &, Action*);

        void setPosition(const Vectorf &);
        const Vectorf & getPosition() const;

        void setColor(const Color &);
        const Color & getColor() const;
        
        void setColorize(const Color &);
        const Color & getColorize() const;

        void setTranslation(const Vectorf &);
        const Vectorf & getTranslation() const;

        void setRotation(double);
        double getRotation() const;

        void setScale(const Vectorf & pScale);
        const Vectorf & getScale() const;

		virtual void parse(const std::string&, const std::string&);
        virtual void event(const SDL_Event &);
        virtual void update(double);
        virtual void draw(SDL_Surface*) = 0;
        virtual bool collide(double, double) = 0;

        // Input callback
        virtual void onUp();
        virtual void onDown();
        virtual void onLeft();
        virtual void onRight();
        virtual void onSelect();

        // focus etc...
        virtual void onIdle();
        virtual void onFocus();
        virtual void onUnfocus();
    };
};

#endif	/* ELEMENT_H */

