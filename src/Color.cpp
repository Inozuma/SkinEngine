/* 
 * File:   Color.cpp
 * Author: Inozuma
 * 
 * Created on December 12, 2011, 10:38 AM
 */

#include <SDL/SDL_video.h>

#include "Skin/Color.h"

using namespace Skin;

Color::Color() :
r(0),
g(0),
b(0),
a(0)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, float a) :
r(r),
g(g),
b(b),
a(a)
{
}

Color Color::operator +(const Color& rhs) const
{
    int r = this->r + rhs.r;
    int g = this->g + rhs.g;
    int b = this->b + rhs.b;
    float a = this->a + rhs.a;
    return this->set(r, g, b, a);
}

Color Color::operator -(const Color& rhs) const
{
    int r = this->r - rhs.r;
    int g = this->g - rhs.g;
    int b = this->b - rhs.b;
    float a = this->a - rhs.a;
    return this->set(r, g, b, a);
}

Color Color::operator *(float v) const
{
    int r = this->r * v;
    int g = this->g * v;
    int b = this->b * v;
    float a = this->a * v;
    return this->set(r, g, b, a);
}

Color Color::operator /(float v) const
{
    int r = this->r / v;
    int g = this->g / v;
    int b = this->b / v;
    float a = this->a / v;
    return this->set(r, g, b, a);
}

Color Color::set(int r, int g, int b, float a) const
{
    if (r > 255)
        r = 255;
    else if (r < 0)
        r = 0;
    if (g > 255)
        g = 255;
    else if (g < 0)
        g = 0;
    if (b > 255)
        b = 255;
    else if (b < 0)
        b = 0;
    if (a > 1)
        a = 1;
    else if (a < 0)
        a = 0;
    return Color(r, g, b, a);
}