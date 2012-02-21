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
        
        double mTime;
        double mStart;
        double mEnd;
        double mLength;
        
        Vectorf mTranslation;
        double mRotation;
        Vectorf mScale;
        Color mColor;
        
    public:
        Effect(double = 0, double = 0,
                const Vectorf & = Vectorf(), double = 0,
                const Vectorf & = Vectorf(), const Color & = Color());
        virtual ~Effect();
        
        void setColor(const Color&);
        const Color& getColor() const;
        
        void setScale(const Vectorf&);
        const Vectorf& getScale() const;
        
        void setRotation(double);
        double getRotation() const;
        
        void setTranslation(const Vectorf&);
        const Vectorf& getTranslation() const;
        
        void setEnd(double mEnd);
        double getEnd() const;
        
        void setStart(double mStart);
        double getStart() const;
        
        bool isActive() const;
        
        template <class T>
        void update(T&, double);
    };
    
    template <> void Effect::update<Element>(Element&, double);
    template <> void Effect::update<Screen>(Screen&, double);
}

#endif	/* EFFECT_H */

