/* 
 * File:   DynamicType.h
 * Author: Inozuma
 *
 * Created on December 13, 2011, 10:53 PM
 */

#ifndef DYNAMICTYPE_H
#define	DYNAMICTYPE_H

#include <algorithm>

class DynamicType;

template <class T>
T DynamicCast(DynamicType&);

class DynamicBase
{
public:
    virtual ~DynamicBase() {}
    virtual DynamicBase* clone() const = 0;
};

template <class T>
class DynamicValue : public DynamicBase
{
    T mValue;
    
public:
    DynamicValue(const T& value) : mValue(value) {}
    
    DynamicBase* clone() const
    {
        return new DynamicValue(mValue);
    }
    
    friend T DynamicCast<>(DynamicType&);
};

class DynamicType
{
private:
    DynamicBase *mType;
    
public:
    DynamicType() : mType(0) {}
    ~DynamicType() { delete mType; }
    
    template <class T>
    DynamicType(const T& type) : mType(new DynamicValue<T>(type)) {}
    DynamicType(const DynamicType& rhs) : mType(rhs.mType != 0 ? rhs.mType->clone() : 0) {}
    
    DynamicType& operator =(const DynamicType& rhs)
    {
        if (this != &rhs)
        {
            DynamicType copy(rhs);
            std::swap(this->mType, copy.mType);
        }
        return *this;
    }
    
    template <class T>
    friend T DynamicCast(DynamicType&);
};

class bad_dynamic_cast : public std::exception
{
public:
    const char* what() const throw()
    {
        return "Bad DynamicCast exception";
    }
};

template <class T>
T DynamicCast(DynamicType& type)
{
    DynamicValue<T>* value = dynamic_cast<DynamicValue<T>*>(type.mType);
    
    if (!value)
        throw bad_dynamic_cast();
    return value->mValue;
}

#endif	/* DYNAMICTYPE_H */

