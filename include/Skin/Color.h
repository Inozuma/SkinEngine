/* 
 * File:   Color.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 10:38 AM
 */

#ifndef COLOR_H
#define	COLOR_H

#include <stdint.h>

namespace Skin
{
    // TODO : operator+

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        float a;
        
        Color();
        Color(uint8_t r, uint8_t g, uint8_t b, float a = 1);
        
        Color operator +(const Color&) const;
        Color operator -(const Color&) const;
        
        Color operator *(float) const;
        Color operator /(float) const;
        
    private:
        Color set(int r, int g, int b, float a) const;
        
    };
}

#endif	/* COLOR_H */

