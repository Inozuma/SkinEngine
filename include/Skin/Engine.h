/* 
 * File:   SkinCore.h
 * Author: Inozuma
 *
 * Created on December 10, 2011, 11:23 PM
 */

#ifndef SKINCORE_H
#define	SKINCORE_H

#include "Skin/Screen.h"
#include "Skin/Module.h"
#include "Skin/Parser/Parser.h"
#include "Skin/Parser/ParserListener.h"

#include <rapidxml/rapidxml.hpp>

#include <map>
#include <string>

#if defined(SKINENGINE_EXPORT)
# define SKINENGINE_API __declspec(dllexport)
#else
# define SKINENGINE_API __declspec(dllimport)
#endif

#define VIDEO_MODE_FULLSCREEN true
#define VIDEO_MODE_WINDOW false

#define DEFAULT_SKIN_DIR "skin/"
#define DEFAULT_SKIN_NAME "default"
#define DEFAULT_LANGUAGE "en_US"
#define DEFAULT_VIDEO_MODE VIDEO_MODE_WINDOW
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FRAMERATE 30
#define DEFAULT_VSYNC false

typedef std::map<std::string, Skin::Screen*> ScreenMap;
typedef std::pair<std::string, Skin::Screen*> ScreenPair;

typedef std::map<std::string, Skin::Module*> ModuleMap;
typedef std::pair<std::string, Skin::Module*> ModulePair;

// need proper abstraction
struct SDL_mutex;

namespace Skin
{
	enum Input
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		OK,
		CANCEL
	};

    class Engine : public Module, public ParserListener
    {
    private:
		// Parser
		Parser* mParserConfiguration;
		Parser* mParserSkin;

        // Configuration
        std::string mConfigurationFile;
        std::string mSkinDir;
        std::string mSkinName;
		std::string mSkinPath;
		std::string mLanguage;
        bool mFullscreen;
        int mWidth;
        int mHeight;
		int mFramerate;
		bool mVsync;

		// Current skin info
		std::string mVersion;
		std::string mAuthor;
		std::string mDescription;
		std::string mSkinResource;
		int mSkinWidth;
		int mSkinHeight;

        // Module
        ModuleMap mModules;

        // Skin Core
        bool mRunning;
        ScreenMap mScreens;
        std::string mActiveScreen;
        SDL_Surface* mDisplaySurface;
		SDL_mutex *mMutex;

    public:
        SKINENGINE_API Engine(std::string const & = "");
        SKINENGINE_API virtual ~Engine();

        // Utilities
        SKINENGINE_API bool isRunning() const;
        SKINENGINE_API void addModule(std::string const &, Module *);
        SKINENGINE_API void deleteModule(std::string const &);
        SKINENGINE_API Module* getModule(std::string const &);
        
        SKINENGINE_API void changeScreen(const std::string&);
        SKINENGINE_API const std::string& getScreen() const;
        
        // Core functions
        SKINENGINE_API bool init();
        SKINENGINE_API void quit();
		SKINENGINE_API void launch(bool);
        SKINENGINE_API void update(double);
        SKINENGINE_API void draw();
		SKINENGINE_API void inject(Input);
		SKINENGINE_API void inject(char);
        
        // Callback
        SKINENGINE_API void Callback(const ModuleParameter &);

	protected:
        void run();
		static int entry_point(void *);

    private:
        // Config parsing
		void setupParserConfiguration();
		void parseSkinPath(XMLNode*);
		void parseSkinName(XMLNode*);
		void parseVideoFullscreen(XMLNode*);
		void parseVideoWidth(XMLNode*);
		void parseVideoHeight(XMLNode*);
		void parseVideoFramerate(XMLNode*);
		void parseVideoVsync(XMLNode*);

		// Skin parsing
		void setupParserSkin();
		void parseSkinVersion(XMLNode*);
		void parseSkinAuthor(XMLNode*);
		void parseSkinDescription(XMLNode*);
		void parseSkinInclude(XMLNode*);
		void parseSkinResolution(XMLNode*);
		void parseSkinScreen(XMLNode*);
		void parseSkinElement(XMLNode*);
		void parseSkinElementValue(XMLNode*);
		void parseSkinElementContent(XMLNode*);
		void parseSkinElementFont(XMLNode*);
		void parseSkinElementImg(XMLNode*);
		void parseSkinElementSize(XMLNode*);
		void parseSkinElementBox(XMLNode*);
		void parseSkinAction(XMLNode*);
		void parseSkinEffect(XMLNode*);
		void parseSkinEffectTranslate(Effect*, XMLNode*);
		void parseSkinEffectRotate(Effect*, XMLNode*);
		void parseSkinEffectScale(Effect*, XMLNode*);
		void parseSkinEffectColor(Effect*, XMLNode*);
    };
};

#endif	/* SKINCORE_H */