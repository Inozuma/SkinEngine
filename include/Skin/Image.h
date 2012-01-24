/* 
 * File:   Image.h
 * Author: inozuma
 *
 * Created on January 23, 2012, 2:55 AM
 */

#ifndef IMAGE_H
#define	IMAGE_H

#include "Skin/Vector.h"

#include <SDL/SDL.h>

#include <string>

namespace Skin
{
    class Image
    {
    private:
        SDL_Surface* mSurface;
        std::string mFilename;
        Vectorf mPosition;
        float mRotation;
        Vectorf mScale;
        int mSmooth;
        int mWidth;
        int mHeight;
        
    public:
        Image();
        Image(const std::string&);
        virtual ~Image();
        
        bool openFile(const std::string&);
        bool isOpen() const;
        
        const std::string& getFilename() const;
        const Vectorf& getPosition() const;
        float getRotation() const;
        const Vectorf& getScale() const;
        bool hasSmooth() const;
        int getWidth() const;
        int getHeight() const;
        
        void setPosition(const Vectorf& position);
        void setPosition(float x, float y);
        void setRotation(float rotation);
        void setScale(const Vectorf& scale);
        void setScale(float x, float y);
        void setSmooth(bool smooth);
        
        void draw(SDL_Surface* drawSurface);
    };
}

#endif	/* IMAGE_H */

