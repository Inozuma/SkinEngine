#include "Skin/Parser/Parser.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace Skin;

Parser::Parser() :
mRoot(NULL)
{
}

Parser::~Parser(void)
{
	if (mRoot)
	{
		delete mRoot;
		mRoot = NULL;
	}
}

void Parser::setRoot(Node* node)
{
	mRoot = node;
}

bool Parser::parse(const std::string& file)
{
	std::ifstream fs;

	std::cout << "Opening `" << file << "`..." << std::endl;
	fs.open(file.c_str());
    if (fs.is_open())
    {
		std::cout << "Parsing `" << file << "`..." << std::endl;
		std::stringstream ss;

		while (fs.good())
		{
			std::string line;
			std::getline(fs, line);
			
			if (fs.good())
				ss << line << std::endl;
			else
				ss << line;
		}

		fs.close();

		char *text = _strdup(ss.str().c_str());

        try
        {
            rapidxml::xml_document<> cfg;
			cfg.parse<rapidxml::parse_full>(text);

			return proceedNode(mRoot, cfg.first_node());
        }
        catch (std::exception &e)
        {
			delete [] text;
            std::cerr << "Error parsing `" << file << "`: " << e.what() << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error opening `" << file << "`." << std::endl;
        return false;
    }
    return true;
}

bool Parser::proceedNode(Node* node, rapidxml::xml_node<>* xml_node)
{
	if (node && xml_node)
	{
		// Check required attributes
		for (std::map<std::string, bool>::const_iterator it = node->getAttributes().begin(); it != node->getAttributes().end(); ++it)
		{
			XMLAttribute* attr = xml_node->first_attribute(it->first.c_str());

			if (attr == NULL && it->second)
			{
				std::cout << "Error: Attribute `" << it->first << "` in node `" << node->getName() << "` is required." << std::endl;
				return false;
			}
		}

		// Check unsupported attributes
		for (XMLAttribute* attr = xml_node->first_attribute(); attr; attr = attr->next_attribute())
		{
			if (!node->hasAttribute(attr->name()))
				std::cout << "Warning: Attribute `" << attr->name() << "` in node `" << node->getName() << "` not supported." << std::endl;
		}

		// Node callback
		if (node->getName().compare(xml_node->name()) == 0)
			(*node)(xml_node);

		// Proceed sibling nodes
		XMLNode* sibling = xml_node->next_sibling();
		if (sibling && sibling->name())
		{
			if (node->hasSibling(sibling->name()))
			{
				if (!this->proceedNode(node->getSibling(sibling->name()), sibling))
					return false;
			}
			else
				std::cout << "Warning: Sibling `" << sibling->name() << "` of `" << node->getName() << "` not supported." << std::endl;
		}

		// Proceed child nodes
		XMLNode* child = xml_node->first_node();
		if (child && child->name())
		{
			if (node->hasChild(child->name()))
			{
				if (!this->proceedNode(node->getChild(child->name()), child))
					return false;
			}
			else
				std::cout << "Warning: Child `" << child->name() << "` of `" << node->getName() << "` not supported." << std::endl;
		}
	}
	return true;
}