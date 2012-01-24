/* 
 * File:   ActionFocus.h
 * Author: Inozuma
 *
 * Created on January 11, 2012, 11:25 AM
 */

#ifndef ACTIONFOCUS_H
#define	ACTIONFOCUS_H

#include "Skin/Action.h"

namespace Skin
{

    class ActionFocus : public Action
    {
    private:
        unsigned int mFocus;
        
    public:
        ActionFocus(Element&, unsigned int);
        virtual ~ActionFocus();
        
        virtual void execute();
    };
}

#endif	/* ACTIONFOCUS_H */

