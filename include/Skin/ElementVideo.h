#pragma once
#include "Skin/Element.h"

struct SDL_mutex;

namespace Skin
{
	class ElementVideo : public Element
	{
	private:
		std::string mValueSurface;
		std::string mDataSurface;
		std::string mValueMutex;
		std::string mDataMutex;
		double mWidth;
		double mHeight;

		SDL_mutex* mMutex;
		SDL_Surface* mSurface;
	public:
		ElementVideo(Screen&, const Vectorf&);
		~ElementVideo(void);

		virtual void parse(const std::string&, const std::string&);
        virtual bool collide(double x, double y);
        virtual void draw(SDL_Surface* displaySurface);

		void dataSurfaceChangedSlot(const std::string & data);
		void dataMutexChangedSlot(const std::string & data);

	private:
		void parseDynamicDataSurface();
		void parseDynamicDataMutex();
	};
}