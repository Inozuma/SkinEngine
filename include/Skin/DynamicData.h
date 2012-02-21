/* 
 * File:   DynamicData.h
 * Author: Inozuma
 *
 * Created on December 11, 2011, 2:52 AM
 */

#ifndef DYNAMICDATA_H
#define	DYNAMICDATA_H

#include "Skin/DynamicType.h"

#include <map>
#include <string>
#include <typeinfo>
#include <iostream>

#if defined(SKINENGINE_EXPORT)
# define SKINENGINE_API __declspec(dllexport)
#else
# define SKINENGINE_API __declspec(dllimport)
#endif

typedef std::map<std::string, DynamicType> DynamicTypeMap;
typedef std::pair<std::string, DynamicType> DynamicTypePair;

class DynamicData
{
private:
    DynamicTypeMap mData;

public:

    DynamicData() { }

    virtual ~DynamicData() { }

    template <class T>
    bool addData(std::string const & name, T data)
    {
        if (this->mData.count(name))
        {
            std::cout << "Error on add: Data `" << name << "` already exists." << std::endl;
            return false;
        }
        std::cout << "Data `" << name << "` added as " << typeid (T).name() << std::endl;
        this->mData.insert(DynamicTypePair(name, data));
        return true;
    }

    bool deleteData(std::string const & name)
    {
        if (!this->mData.count(name))
        {
            std::cout << "Error on delete: Data `" << name << "` not found." << std::endl;
            return false;
        }
        std::cout << "Data `" << name << "` deleted." << std::endl;
        this->mData.erase(name);
        return true;

    }

    template <class T>
    bool updateData(std::string const & name, T data)
    {
        if (!this->mData.count(name))
        {
            std::cout << "Error on update: Data `" << name << "` not found." << std::endl;
            return false;
        }
        try
        {
            std::cout << "Data `" << name << "` updated." << std::endl;
            DynamicCast<T > (this->mData[name]);
            this->mData[name] = data;
        }
        catch (...)
        {
            std::cout << "Error on update: Data `" << name << "` exists with a different type." << std::endl;
            return false;
        }
        return true;
    }

    template <class T>
    T getData(std::string const & name)
    {
        if (!this->mData.count(name))
        {
            std::cout << "Error on get: Data `" << name << "` does not exist." << std::endl;
            return T();
        }
        try
        {
            T value = DynamicCast<T > (this->mData[name]);
            return value;
        }
        catch (...)
        {
            std::cout << "Error on get: Data `" << name << "` exists with a different type" << std::endl;
            return T();
        }
    }
};

#endif	/* DYNAMICDATA_H */