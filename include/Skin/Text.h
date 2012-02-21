/* 
 * File:   Text.h
 * Author: inozuma
 *
 * Created on January 23, 2012, 5:23 AM
 */

#ifndef TEXT_H
#define	TEXT_H

#include "Skin/Color.h"
#include "Skin/Vector.h"

#include <string>

#define DEFAULT_FONT "default.ttf"
#define DEFAULT_FONTSIZE 24

struct SDL_Surface;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

namespace Skin
{
    class Text
    {
    private:
        Vectorf mPosition;
        double mRotation;
        Vectorf mScale;
        std::string mText;
        TTF_Font* mFont;
        std::string mName;
        unsigned int mSize;
        Color mColor;
        int mWidth;
        int mHeight;
        
    public:
        Text(const std::string&, const std::string& = DEFAULT_FONT, unsigned int = DEFAULT_FONTSIZE);
        virtual ~Text();
        
        const Vectorf& getPosition() const;
        double getRotation() const;
        const Vectorf& getScale() const;
        const std::string& getText() const;
        const std::string& getName() const;
        unsigned int getSize() const;
        const Color& getColor() const;
        int getWidth() const;
        int getHeight() const;
        int getMaxHeight() const;
        
        void setPosition(const Vectorf&);
        void setPosition(double x, double y);
        void setRotation(double rotation);
        void setScale(const Vectorf&);
        void setScale(double x, double y);
        void setText(const std::string& text);
        void setName(const std::string& fontname);
        void setSize(unsigned int fontsize);
        void setColor(const Color& color);
        
        void draw(SDL_Surface* drawSurface);
		void parse(const std::string&, const std::string&);
        
    private:
        void loadFont(const std::string&, unsigned int);
    };
}

#endif	/* TEXT_H */

