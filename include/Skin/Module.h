/* 
 * File:   Module.h
 * Author: Inozuma
 *
 * Created on December 11, 2011, 11:03 PM
 */

#ifndef MODULE_H
#define	MODULE_H

#include "Skin/DynamicData.h"

#include <vector>
#include <string>

#if defined(SKINENGINE_EXPORT)
# define SKINENGINE_API __declspec(dllexport)
#else
# define SKINENGINE_API __declspec(dllimport)
#endif

namespace Skin
{

    struct ModuleParameter
    {
        std::string function;
        std::vector<std::string> parameters;
    };

    class Module
    {
    private:
        DynamicData mDynamicData;

    public:

        virtual ~Module() { }

        // Callback for the core
        virtual void Callback(ModuleParameter const &) = 0;
        
        // Utilities for data
        template <class T>
        bool addDynamicData(const std::string & name, T data)
        {
            return this->mDynamicData.addData<T>(name, data);
        }
        
        template <class T>
        bool updateDynamicData(const std::string & name, T data)
        {
            return this->mDynamicData.updateData<T>(name, data);
        }
        
        bool deleteDynamicData(const std::string & name)
        {
            return this->mDynamicData.deleteData(name);
        }
        
        template <class T>
        T getDynamicData(const std::string & name)
        {
            return this->mDynamicData.getData<T>(name);
        };
    };
};

#endif	/* MODULE_H */

