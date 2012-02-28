#pragma once

/*
*	Events
*/

class EventKey
{
public:
	unsigned int sym;
	unsigned short unicode;

	EventKey() : sym(0), unicode(0) {}
	EventKey(unsigned int _sym, unsigned short _unicode) : sym(_sym), unicode(_unicode)
	{}
};

class EventMouseButton
{
public:
	unsigned char button;
	unsigned short x;
	unsigned short y;

	EventMouseButton() : button(0), x(0), y(0) {}
	EventMouseButton(unsigned char _button, unsigned short _x, unsigned short _y) : button(_button), x(_x), y(_y)
	{}
};

class EventMouseMotion
{
public:
	unsigned short x;
	unsigned short y;
	short xrel;
	short yrel;
	bool left;
	bool right;
	bool middle;

	EventMouseMotion() : x(0), y(0), xrel(0), yrel(0), left(false), right(false), middle(false) {}
	EventMouseMotion(unsigned short x, unsigned short y, short xrel, short yrel, bool left, bool right, bool middle) : x(x), y(y), xrel(xrel), yrel(yrel), left(left), right(right), middle(middle)
	{}
};