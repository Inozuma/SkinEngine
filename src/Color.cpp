/* 
 * File:   Color.cpp
 * Author: Inozuma
 * 
 * Created on December 12, 2011, 10:38 AM
 */

#include <SDL/SDL_video.h>

#include "Skin/Color.h"

#include <sstream>
#include <algorithm>

using namespace Skin;

Color::Color() :
r(0),
g(0),
b(0),
a(0)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, double a) :
r(r),
g(g),
b(b),
a(a)
{
}

Color::Color(const std::string& str) :
r(0),
g(0),
b(0),
a(1)
{
	if (str.find("#") == 0 && (str.size() == 7 || str.size() == 9))
	{
		std::string lstr(str);
		for (int i = 0; i < lstr.size(); ++i)
			lstr[i] = tolower(str[i]);

		uint8_t red;
		uint8_t green;
		uint8_t blue;
		double alpha = 1;
		std::stringstream ssred;
		std::stringstream ssgreen;
		std::stringstream ssblue;
		ssred << lstr.substr(1, 3);
		ssgreen << lstr.substr(3, 5);
		ssblue << lstr.substr(5, 7);
		ssred >> red;
		ssgreen >> green;
		ssblue >> blue;

		if (str.size() == 9)
		{
			std::stringstream ssalpha;
			ssalpha << lstr.substr(7, 9);
			ssalpha >> alpha;
			alpha = alpha / 255.0;
		}
		set(red, green, blue, alpha);
	}
	else if (str == "red")
		set(255, 0, 0, 1);
	else if (str == "green")
		set(0, 255, 0, 1);
	else if (str == "blue")
		set(0, 0, 255, 1);
	else if (str == "black")
		set(0, 0, 0, 1);
	else if (str == "white")
		set(1, 1, 1, 1);
}

Color Color::operator +(const Color& rhs) const
{
    int r = this->r + rhs.r;
    int g = this->g + rhs.g;
    int b = this->b + rhs.b;
    double a = this->a + rhs.a;
    return this->set(r, g, b, a);
}

Color Color::operator -(const Color& rhs) const
{
    int r = this->r - rhs.r;
    int g = this->g - rhs.g;
    int b = this->b - rhs.b;
    double a = this->a - rhs.a;
    return this->set(r, g, b, a);
}

Color Color::operator *(double v) const
{
    int r = static_cast<int>(this->r * v);
    int g = static_cast<int>(this->g * v);
    int b = static_cast<int>(this->b * v);
    double a = this->a * v;
    return this->set(r, g, b, a);
}

Color Color::operator /(double v) const
{
    int r = static_cast<int>(this->r / v);
    int g = static_cast<int>(this->g / v);
    int b = static_cast<int>(this->b / v);
    double a = this->a / v;
    return this->set(r, g, b, a);
}

Color Color::set(int r, int g, int b, double a) const
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
    if (a > 255)
        a = 1;
    else if (a < 0)
        a = 0;
    return Color(r, g, b, a);
}