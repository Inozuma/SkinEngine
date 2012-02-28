/* 
 * File:   ActionCallback.cpp
 * Author: Inozuma
 * 
 * Created on January 11, 2012, 11:11 AM
 */

#include "Skin/ActionCallback.h"
#include "Skin/Screen.h"
#include "Skin/Engine.h"

#include <vector>

using namespace Skin;

ActionCallback::ActionCallback(Element& element, const std::string& command) :
Action(element)
{
	int posDot = command.find(".");
	int posLBracket = command.find("(");
	int posRBracket = posLBracket;
	for (; command[posRBracket] && command[posRBracket] != ')'; posRBracket++)
	{
		if (command[posRBracket] == '"')
		{
			posRBracket++;
			while (command[posRBracket] != '"')
				posRBracket++;
		}
	}
	std::string params = command.substr(posLBracket + 1, posRBracket - posLBracket - 1);

	mModule = command.substr(0, posDot);
	mParameter.function = command.substr(posDot + 1, posLBracket - posDot - 1);
	if (params.size())
	{
		std::vector<int> indexList;
		indexList.push_back(-1);
		while (params.find(",", indexList.back() + 1) != std::string::npos)
		{
			std::string subparam(params.substr(params.find(",", indexList.back() + 1)));
			indexList.push_back(params.find(",", indexList.back() + 1));
			int c = indexList.back();
		}
		indexList.push_back(params.size());
		for (int i = 0; i + 1 < indexList.size(); ++i)
		{
			int posL = indexList[i];
			int posR = indexList[i + 1];
			std::string param = params.substr(posL + 1, posR - posL - 1);
			while (isspace(param.front()))
				param = param.substr(1);
			while (isspace(param.back()))
				param.pop_back();
			if (param.front() == '"' && param.back() == '"')
			{
				param = param.substr(1, param.size() - 2);
			}
			addParameter(param);
		}
	}
}

ActionCallback::~ActionCallback()
{
}

void ActionCallback::execute()
{
    Module* module = mElement.getScreen().getCore().getModule(mModule);
    
    if (module)
    {
        ModuleParameter param;
        
        // parse parameters
        param.function = mParameter.function;
        for (std::list<std::string>::iterator it = mParameter.parameters.begin();
                it != mParameter.parameters.end(); ++it)
        {
            param.parameters.push_back(this->parseParameter(*it));
        }
        
        // callback
        module->Callback(param);
    }
}

void ActionCallback::setFunctionName(const std::string& functionName)
{
    mParameter.function = functionName;
}

void ActionCallback::addParameter(const std::string& param)
{
    mParameter.parameters.push_back(param);
}

std::string ActionCallback::parseParameter(const std::string& param)
{
    // if calling an element : [0].value
    if (param[0] == '[' && param.find(']') != std::string::npos
            && param.find('.') != std::string::npos)
        return parseParameterElement(param);
    // if finding a module value
    else if (param.find('.') != std::string::npos)
        return parseParameterModule(param);
    else
        return param;
}

std::string ActionCallback::parseParameterElement(const std::string& param)
{
    int id;
    std::string value;
    
    unsigned int pos = param.find(']');
    id = atoi(param.substr(1, pos).c_str());
    
    pos = param.find('.');
    value = param.substr(pos + 1, param.size());
    
    Element* element = mElement.getScreen().getElement(id);
    if (element)
        return element->getData(value);
    return param;
}

std::string ActionCallback::parseParameterModule(const std::string& param)
{
    size_t pos;

    if ((pos = param.find('.')) == std::string::npos)
        return param;

    std::string moduleName = param.substr(0, pos);
    std::string dataName = param.substr(pos + 1, param.size() - 1);

    Module* module = mElement.getScreen().getCore().getModule(moduleName);
    if (module)
        return module->getDynamicData<std::string>(dataName);
    return param;
}