/* 
 * File:   Image.h
 * Author: inozuma
 *
 * Created on January 23, 2012, 2:55 AM
 */

#ifndef IMAGE_H
#define	IMAGE_H

#include "Skin/Vector.h"

#include <string>

// need proper abstraction
struct SDL_Surface;

namespace Skin
{
    class Image
    {
    private:
        SDL_Surface* mSurface;
        std::string mFilename;
        Vectorf mPosition;
        double mRotation;
        Vectorf mScale;
        int mSmooth;
        int mWidth;
        int mHeight;
		double mOriginH;
		double mOriginV;
        
    public:
        Image();
        Image(const std::string&);
        virtual ~Image();
        
        bool openFile(const std::string&);
        bool isOpen() const;
        
        const std::string& getFilename() const;
        const Vectorf& getPosition() const;
        double getRotation() const;
        const Vectorf& getScale() const;
        bool hasSmooth() const;
        int getWidth() const;
        int getHeight() const;
        
        void setPosition(const Vectorf& position);
        void setPosition(double x, double y);
        void setRotation(double rotation);
        void setScale(const Vectorf& scale);
        void setScale(double x, double y);
        void setSmooth(bool smooth);
		void setOrigin(double h, double v);
        
        void draw(SDL_Surface* drawSurface);
		void parse(const std::string&, const std::string&);
    };
}

#endif	/* IMAGE_H */

