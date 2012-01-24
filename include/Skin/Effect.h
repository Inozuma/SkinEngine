/* 
 * File:   Effect.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 10:15 AM
 */

#ifndef EFFECT_H
#define	EFFECT_H

#include "Skin/Vector.h"
#include "Skin/Color.h"

namespace Skin
{
    class Element;
    class Screen;
    
    class Effect
    {
    private:
        bool mActive;
        
        float mTime;
        float mStart;
        float mEnd;
        float mLength;
        
        Vectorf mTranslation;
        float mRotation;
        Vectorf mScale;
        Color mColor;
        
    public:
        Effect(float = 0, float = 0,
                const Vectorf & = Vectorf(), float = 0,
                const Vectorf & = Vectorf(), const Color & = Color());
        virtual ~Effect();
        
        void setColor(const Color&);
        const Color& getColor() const;
        
        void setScale(const Vectorf&);
        const Vectorf& getScale() const;
        
        void setRotation(float);
        float getRotation() const;
        
        void setTranslation(const Vectorf&);
        const Vectorf& getTranslation() const;
        
        void setEnd(float mEnd);
        float getEnd() const;
        
        void setStart(float mStart);
        float getStart() const;
        
        bool isActive() const;
        
        template <class T>
        void update(T&, float);
    };
    
    template <> void Effect::update<Element>(Element&, float);
    template <> void Effect::update<Screen>(Screen&, float);
}

#endif	/* EFFECT_H */

