#pragma once

#include "Skin/Parser/Node.h"
#include "Skin/Parser/ParserListener.h"

#include <list>
#include <map>
#include <string>

#include <rapidxml\rapidxml.hpp>

namespace Skin
{
	typedef rapidxml::xml_node<> XMLNode;
	typedef rapidxml::xml_attribute<> XMLAttribute;
	typedef void (ParserListener::*NodeCallback)(XMLNode*);

	class Node
	{
	private:
		Node* mParent;
		std::string mName;
		std::list<Node*> mChildren;
		std::list<Node*> mSiblings;
		std::map<std::string, bool> mAttributes;
		ParserListener* mParserListener;
		NodeCallback mCallback;

	public:
		Node(Node* parent = NULL, const std::string& name = "");
		~Node();

		const std::string& getName() const;
		void setName(const std::string&);

		Node* getParent() const;
		void setParent(Node*);

		const std::list<Node*>& getChildren() const;
		bool hasChild(const std::string&) const;
		Node* getChild(const std::string&) const;
		Node* createChild(const std::string&);
		void addChild(Node *);

		const std::list<Node*>& getSiblings() const;
		bool hasSibling(const std::string&) const;
		Node* getSibling(const std::string&) const;
		Node* createSibling(const std::string&);
		void addSibling(Node *);

		void addAttribute(const std::string &, bool = true);
		bool isAttributeRequired(const std::string &);
		bool hasAttribute(const std::string &);
		const std::map<std::string, bool> & getAttributes() const;

		void setCallback(void*, NodeCallback);

		void operator()(XMLNode*);
	};
}