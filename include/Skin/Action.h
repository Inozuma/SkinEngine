/* 
 * File:   Action.h
 * Author: Inozuma
 *
 * Created on December 12, 2011, 10:01 AM
 */

#ifndef SKINACTION_H
#define	SKINACTION_H

#include "Skin/Module.h"

namespace Skin
{
    class Element;

    class Action
    {
    protected:
        Element& mElement;

    public:
        Action(Element&);
        virtual ~Action();

        virtual void execute() = 0;
    };
}

#endif	/* ACTION_H */

