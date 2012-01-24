/* 
 * File:   Action.cpp
 * Author: Inozuma
 * 
 * Created on December 12, 2011, 10:01 AM
 */

#include "Skin/Action.h"

#include <algorithm>

using namespace Skin;

Action::Action(Element& element) :
mElement(element)
{
}

Action::~Action()
{
}

/*
std::string Action::parseParameter(Element& element, const std::string& param)
{
    if (param.size() > 1 && param[0] == '"' && param[param.size() - 1] == '"')
        return param.substr(1, param.size() - 2);
    else if (std::for_each(param.begin(), param.end(), isdigit))
        return param;
    else
        return parseDynamicData<Element>(element, param);
}

std::string Action::parseDynamicData(Element& element, const std::string& param)
{
    size_t pos;

    if ((pos = param.find('.')) == std::string::npos)
        return std::string();

    std::string moduleName = param.substr(0, pos);
    std::string dataName = param.substr(pos + 1, param.size() - 1);

    Module* module = element.getScreen().getCore().getModule(moduleName);
    if (module)
        return module->getDynamicData<std::string>(dataName);
    return "";
}
*/