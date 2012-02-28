/* 
 * File:   Color.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 10:38 AM
 */

#ifndef COLOR_H
#define	COLOR_H

#include <stdint.h>
#include <string>

namespace Skin
{
    // TODO : operator+

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        double a;
        
        Color();
        Color(uint8_t r, uint8_t g, uint8_t b, double a = 1);
		Color(const std::string&);
        
        Color operator +(const Color&) const;
        Color operator -(const Color&) const;
        
        Color operator *(double) const;
        Color operator /(double) const;
        
    private:
        Color set(int r, int g, int b, double a) const;
		void set(int red, int green, int blue, double alpha);
        
    };
}

#endif	/* COLOR_H */

