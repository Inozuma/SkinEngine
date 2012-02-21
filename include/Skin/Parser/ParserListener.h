#pragma once

#if defined(SKINENGINE_EXPORT)
# define SKINENGINE_API __declspec(dllexport)
#else
# define SKINENGINE_API __declspec(dllimport)
#endif

namespace Skin
{
	class SKINENGINE_API ParserListener
	{
	public:
		ParserListener();
		~ParserListener();
	};
}