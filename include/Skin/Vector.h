/* 
 * File:   Vector.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 9:20 AM
 */

#ifndef VECTOR_H
#define	VECTOR_H

namespace Skin
{
    // TODO operator +

    struct Vector
    {
        int x;
        int y;
        
        Vector(int x = 0, int y = 0);
        
        Vector operator +(const Vector &) const;
        Vector operator -(const Vector &) const;
        Vector operator *(const Vector&) const;
        Vector operator /(const Vector &) const;
        
        Vector operator *(int) const;
        Vector operator /(int) const;
    };
    
    struct Vectorf
    {
        float x;
        float y;

        Vectorf(float x = 0, float y = 0);
        
        Vectorf operator +(const Vectorf &) const;
        Vectorf operator -(const Vectorf &) const;
        Vectorf operator *(const Vectorf &) const;
        Vectorf operator /(const Vectorf &) const;
        
        Vectorf operator *(float) const;
        Vectorf operator /(float) const;
    };
}

#endif	/* VECTOR_H */