/* 
 * File:   ElementList.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 4:00 PM
 */

#ifndef ELEMENTLIST_H
#define	ELEMENTLIST_H

#include "Skin/Element.h"
#include "Skin/Text.h"
#include "Skin/Box.h"

#include <vector>

#define OFFSET_X 10
#define OFFSET_Y 5

namespace Skin
{

	class ElementList : public Element
    {
    private:
        std::vector<std::string> mValues;
        std::string mValue;
        Vectorf mBoxsize;
        Text mFont;
        Box mBox;
        
        int mIndex;
        int mOffset;
        unsigned int mMax;

		// module info
		std::string mModuleName;
		std::string mDataName;
        
    public:
        ElementList(Screen&, const Vectorf&, const std::string& = "", const Vectorf& = Vectorf());
        virtual ~ElementList();

		Text& label();
		Box& box();

        virtual std::string getData(const std::string&);
        
		virtual void parse(const std::string&, const std::string&);
        virtual bool collide(double x, double y);
        virtual void draw(SDL_Surface* displaySurface);
        virtual void update(double);
        
        virtual void onUp();
        virtual void onDown();

		// data slot to connect to module signal
		void dataChangedSlot(const std::string & name);
        
    private:
        bool parseDynamicData(const std::string & value);
    };
}

#endif	/* ELEMENTLIST_H */

