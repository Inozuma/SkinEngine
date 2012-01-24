/* 
 * File:   ActionCallback.h
 * Author: Inozuma
 *
 * Created on January 11, 2012, 11:11 AM
 */

#ifndef ACTIONCALLBACK_H
#define	ACTIONCALLBACK_H

#include "Skin/Action.h"

namespace Skin
{

    class ActionCallback : public Action
    {
    private:
        std::string mModule;
        ModuleParameter mParameter;
        
    public:
        ActionCallback(Element&, const std::string&);
        virtual ~ActionCallback();
        
        virtual void execute();
        
        void setFunctionName(const std::string&);
        void addParameter(const std::string&);
        
    private:
        std::string parseParameter(const std::string&);
        
        std::string parseParameterElement(const std::string&);
        std::string parseParameterModule(const std::string&);
    };
}

#endif	/* ACTIONCALLBACK_H */

