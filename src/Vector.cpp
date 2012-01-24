/* 
 * File:   Vector.cpp
 * Author: Inozuma
 * 
 * Created on December 12, 2011, 9:20 AM
 */

#include "Skin/Vector.h"

using namespace Skin;

Vector::Vector(int x, int y) :
        x(x),
        y(y)
{
}

Vectorf::Vectorf(float x, float y) :
        x(x),
        y(y)
{
}

Vector Vector::operator +(Vector const & rhs) const
{
    return Vector(this->x + rhs.x, this->y + rhs.y);
}

Vector Vector::operator -(const Vector& rhs) const
{
    return Vector(this->x - rhs.x, this->y - rhs.y);
}

Vector Vector::operator *(const Vector& rhs) const
{
    return Vector(this->x * rhs.x, this->y * rhs.y);
}

Vector Vector::operator /(const Vector& rhs) const
{
    return Vector(rhs.x ? this->x / rhs.x : this->x,
            rhs.y ? this->y / rhs.y : this->y);
}

Vectorf Vectorf::operator +(const Vectorf& rhs) const
{
    return Vectorf(this->x + rhs.x, this->y + rhs.y);
}

Vectorf Vectorf::operator -(const Vectorf& rhs) const
{
    return Vectorf(this->x - rhs.x, this->y - rhs.y);
}

Vectorf Vectorf::operator *(const Vectorf& rhs) const
{
    return Vectorf(this->x * rhs.x, this->y * rhs.y);
}

Vectorf Vectorf::operator /(const Vectorf& rhs) const
{
    return Vectorf(rhs.x ? this->x / rhs.x : this->x,
            rhs.y ? this->y / rhs.y : this->y);
}

Vector Vector::operator *(int v) const
{
    return Vector(this->x * v, this->y * v);
}

Vector Vector::operator /(int v) const
{
    return v ? Vector(this->x / v, this->y / v) : *this;
}

Vectorf Vectorf::operator *(float v) const
{
    return Vectorf(this->x * v, this->y * v);
}

Vectorf Vectorf::operator /(float v) const
{
    return v ? Vectorf(this->x / v, this->y / v) : *this;
}