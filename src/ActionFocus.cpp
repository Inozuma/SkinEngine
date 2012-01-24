/* 
 * File:   ActionFocus.cpp
 * Author: Inozuma
 * 
 * Created on January 11, 2012, 11:25 AM
 */

#include "Skin/ActionFocus.h"
#include "Skin/Element.h"
#include "Skin/Screen.h"

using namespace Skin;

ActionFocus::ActionFocus(Element& element, unsigned int id) :
Action(element),
mFocus(id)
{
}

ActionFocus::~ActionFocus()
{
}

void ActionFocus::execute()
{
    mElement.getScreen().setActiveElement(mFocus);
}
