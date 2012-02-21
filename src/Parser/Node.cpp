#include "Skin/Parser/Node.h"

#include <algorithm>

using namespace Skin;

Node::Node(Node* parent, const std::string& name) :
mParent(parent),
mName(name),
mParserListener(NULL),
mCallback(NULL)
{
}

Node::~Node()
{
	for (std::list<Node*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
		delete (*it);
}

const std::string& Node::getName() const
{
	return mName;
}

void Node::setName(const std::string& name)
{
	mName = name;
}

Node* Node::getParent() const
{
	return mParent;
}

void Node::setParent(Node* parent)
{
	mParent = parent;
}

const std::list<Node*>& Node::getChildren() const
{
	return mChildren;
}

bool Node::hasChild(const std::string& name) const
{
	for (std::list<Node*>::const_iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if ((*it)->mName == name)
			return true;
	}
	return false;
}

Node* Node::getChild(const std::string& name) const
{
	for (std::list<Node*>::const_iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if ((*it)->mName == name)
			return (*it);
	}
	return NULL;
}

Node* Node::createChild(const std::string& name)
{
	Node* node = new Node(this, name);

	for (std::list<Node*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		node->addSibling(*it);
		(*it)->addSibling(node);
	}
	mChildren.push_back(node);
	return node;
}

void Node::addChild(Node *node)
{
	if (this != node)
		this->mChildren.push_back(node);
}

const std::list<Node*>& Node::getSiblings() const
{
	return mSiblings;
}

bool Node::hasSibling(const std::string& name) const
{
	for (std::list<Node*>::const_iterator it = mSiblings.begin(); it != mSiblings.end(); ++it)
	{
		if ((*it)->mName == name)
			return true;
	}
	return false;
}

Node* Node::getSibling(const std::string& name) const
{
	for (std::list<Node*>::const_iterator it = mSiblings.begin(); it != mSiblings.end(); ++it)
	{
		if ((*it)->mName == name)
			return (*it);
	}
	return NULL;
}

Node* Node::createSibling(const std::string& name)
{
	Node* node = new Node(this->mParent, name);

	node->mSiblings = mSiblings;
	this->addSibling(node);
	node->addSibling(this);
	if (mParent)
		mParent->addChild(node);
	for (std::list<Node*>::iterator it = mSiblings.begin(); it != mSiblings.end(); ++it)
	{
		(*it)->addSibling(node);
	}
	return node;
}

void Node::addSibling(Node* node)
{
	if (this != node)
		mSiblings.push_back(node);
}

void Node::addAttribute(const std::string & attribute, bool required)
{

	if (!hasAttribute(attribute))
		mAttributes[attribute] = required;
}

bool Node::hasAttribute(const std::string & attribute)
{
	return this->mAttributes.count(attribute) ? true : false;
}

bool Node::isAttributeRequired(const std::string & attribute)
{
	if (hasAttribute(attribute))
		return mAttributes[attribute];
	return false;
}

const std::map<std::string, bool> & Node::getAttributes() const
{
	return mAttributes;
}

void Node::setCallback(void* parserListener, NodeCallback callback)
{
	mParserListener = reinterpret_cast<ParserListener*>(parserListener);
	mCallback = callback;
}

void Node::operator()(XMLNode* node)
{
	if (mParserListener && mCallback)
		(mParserListener->*mCallback)(node);
}