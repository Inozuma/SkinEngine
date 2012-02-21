#pragma once

#include "Skin\Parser\Node.h"

#include <rapidxml\rapidxml.hpp>

namespace Skin
{
	class Parser
	{
	private:
		Node* mRoot;

	public:
		Parser();
		~Parser(void);

		void setRoot(Node *);

		bool parse(const std::string&);

	private:
		bool proceedNode(Node*, rapidxml::xml_node<>*);
	};

}

