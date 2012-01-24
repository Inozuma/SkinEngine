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

#include <rapidxml/rapidxml.hpp>

#include <map>
#include <string>

#define VIDEO_MODE_FULLSCREEN true
#define VIDEO_MODE_WINDOW false

#define DEFAULT_SKIN_PATH "skin/"
#define DEFAULT_RESOURCE_PATH "resources/"
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_VIDEO_MODE VIDEO_MODE_WINDOW

#define CFG_NODE_FIRST "config"
#define CFG_NODE_SKIN_PATH "skin"
#define CFG_NODE_RESOURCE_PATH "resources"
#define CFG_NODE_VIDEO "video"
#define CFG_ATTR_WIDTH "width"
#define CFG_ATTR_HEIGHT "height"
#define CFG_ATTR_FULLSCREEN "fullscreen"

typedef std::map<std::string, Skin::Screen*> ScreenMap;
typedef std::pair<std::string, Skin::Screen*> ScreenPair;

typedef std::map<std::string, Skin::Module*> ModuleMap;
typedef std::pair<std::string, Skin::Module*> ModulePair;


namespace Skin
{

    class Engine : public Module
    {
    private:
        // Configuration
        std::string mConfigurationFile;
        std::string mSkinPath;
        std::string mSkinName;
        std::string mResourcePath;
        size_t mWidth;
        size_t mHeight;
        bool mFullscreen;

        // Module
        ModuleMap mModules;

        // Skin Core
        bool mRunning;
        SDL_Surface* mDisplaySurface;
        ScreenMap mScreens;
        std::string mActiveScreen;
        
        std::string mTestString;
        std::list<std::string> mTestList;


    public:
        Engine(std::string const & = "");
        virtual ~Engine();

        // Utilities
        bool isRunning() const;
        void addModule(std::string const &, Module *);
        void deleteModule(std::string const &);
        Module* getModule(std::string const &);
        
        void changeScreen(const std::string&);
        const std::string& getScreen() const;
        
        // Core functions
        bool init();
        void quit();
        void run();
        
        // Callback
        void Callback(const ModuleParameter &);

    private:
        // Config parsing
        bool parseConfigurationFile();
        void parseNode(size_t, rapidxml::xml_node<>*);
        
        // Menu without XML
        void createMenu();
        
    public:
        // Runtime
        void update(float);
        void draw();
    };
};

#endif	/* SKINCORE_H */