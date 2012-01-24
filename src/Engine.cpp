/* 
 * File:   SkinCore.cpp
 * Author: Inozuma
 * 
 * Created on December 10, 2011, 11:23 PM
 */

#include "Skin/Engine.h"

#include "Skin/ElementLabel.h"
#include "Skin/ElementImage.h"
#include "Skin/ElementInput.h"
#include "Skin/ElementList.h"
#include "Skin/ElementButton.h"
#include "Skin/ActionFocus.h"
#include "Skin/ActionCallback.h"

#include <iostream>
#include <fstream>
#include <rapidxml/rapidxml.hpp>
#include <SDL/SDL_image.h>

using namespace Skin;

Engine::Engine(std::string const & cfgFile) :
mConfigurationFile(cfgFile),
mSkinPath(""),
mResourcePath(""),
mWidth(0),
mHeight(0),
mFullscreen(false),
mRunning(true),
mDisplaySurface(NULL)
{
    this->addModule("Core", this);

    if (!this->parseConfigurationFile())
    {
        std::cout << "using default configuration" << std::endl;

        this->mSkinPath = DEFAULT_SKIN_PATH;
        this->mResourcePath = DEFAULT_RESOURCE_PATH;
        this->mWidth = DEFAULT_WIDTH;
        this->mHeight = DEFAULT_HEIGHT;
        this->mFullscreen = DEFAULT_VIDEO_MODE;
    }
}

Engine::~Engine()
{
}

bool Engine::isRunning() const
{
    return this->mRunning;
}

void Engine::addModule(std::string const & moduleName , Module* module)
{
    if (!this->mModules.count(moduleName))
    {
        this->mModules.insert(ModulePair(moduleName, module));
    }
}

void Engine::deleteModule(std::string const & moduleName)
{
    if (this->mModules.count(moduleName))
    {
        this->mModules.erase(moduleName);
    }
}

Module* Engine::getModule(std::string const & moduleName)
{
    if (this->mModules.count(moduleName))
    {
        return this->mModules[moduleName];
    }
    return NULL;
}

void Engine::changeScreen(const std::string& screen)
{
    if (mScreens.count(screen) && mActiveScreen != screen)
    {
        if (mScreens.count(mActiveScreen))
            mScreens[mActiveScreen]->onUnload();
        mActiveScreen = screen;
        mScreens[screen]->onLoad();
    }
}

const std::string& Engine::getScreen() const
{
    return mActiveScreen;
}

bool Engine::init()
{
    if (!mWidth || !mHeight)
    {
        std::cout << "using default configuration" << std::endl;

        mSkinPath = DEFAULT_SKIN_PATH;
        mResourcePath = DEFAULT_RESOURCE_PATH;
        mWidth = DEFAULT_WIDTH;
        mHeight = DEFAULT_HEIGHT;
        mFullscreen = DEFAULT_VIDEO_MODE;
    }
    // Init SDL
    int flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    flags |= mFullscreen ? SDL_FULLSCREEN : 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    mDisplaySurface = SDL_SetVideoMode(mWidth, mHeight, 32, flags);
    //    mRenderWindow->EnableKeyRepeat(false);
    
    // Init SDL Image
    flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    IMG_Init(flags);
    
    TTF_Init();
    
    SDL_EnableUNICODE(SDL_ENABLE);
    SDL_EnableKeyRepeat(400, 20);
    
    this->createMenu();
    return true;
}

void Engine::quit()
{
    this->mRunning = false;
}

void Engine::run()
{
    float oldTime = 0;

    while (mRunning)
    {
        float time = float(SDL_GetTicks()) / 1000.0;
        this->update(time - oldTime);
        oldTime = time;
        this->draw();
    }
    SDL_Quit();
}

bool Engine::parseConfigurationFile()
{
    std::fstream fs;

    fs.open(mConfigurationFile.c_str());
    if (fs.is_open())
    {
        std::cout << "loading `" << mConfigurationFile << "` configuration file" << std::endl;
        char *buf;
        size_t size;

        fs.seekg(0, std::ios::end);
        size = fs.tellg();
        buf = new char[size + 1];
        buf[size] = '\0';
        fs.seekg(0);
        fs.read(buf, size);
        fs.close();

        try
        {
            rapidxml::xml_document<> cfg;
            cfg.parse < 0 > (buf);
            delete [] buf;

            if (rapidxml::xml_node<>* node = cfg.first_node())
                this->parseNode(0, node);
            else
                std::cout << "Error: empty xml tree" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "Error parsing `" << mConfigurationFile << "`: " << e.what() << std::endl;
            delete [] buf;
            return false;
        }
    }
    else
    {
        std::cerr << "file `" << mConfigurationFile << "` not found." << std::endl;
        return false;
    }
    return true;
}

void Engine::parseNode(size_t level, rapidxml::xml_node<>* node)
{
    if (node == 0)
        return ;
    if (level == 0)
    {
        if (std::string(node->name()) == CFG_NODE_FIRST)
            this->parseNode(level + 1, node->first_node());
        else
            std::cout << "Warning: Node `" << node->name() << "` not supported" << std::endl;
    }
    else if (level == 1)
    {
        if (std::string(node->name()) == CFG_NODE_SKIN_PATH)
            this->mSkinPath = node->value();
        else if (std::string(node->name()) == CFG_NODE_RESOURCE_PATH)
            this->mResourcePath = node->value();
        else if (std::string(node->name()) == CFG_NODE_VIDEO)
        {
            for (rapidxml::xml_attribute<>* attr = node->first_attribute();
                    attr; attr = attr->next_attribute())
            {
                if (std::string(attr->name()) == CFG_ATTR_WIDTH)
                    this->mWidth = atoi(attr->value());
                else if (std::string(attr->name()) == CFG_ATTR_HEIGHT)
                    this->mHeight = atoi(attr->value());
                else if (std::string(attr->name()) == CFG_ATTR_FULLSCREEN)
                    this->mFullscreen = std::string(attr->value()) == "1" ? true : false;
                else
                    std::cout << "Warning: Attribute `" << attr->value() << "` in node `" << node->value() << "` not supported" << std::endl;
            }
        }
        else
            std::cout << "Warning: Node(" << node->parent()->name() << ") `" << node->name() << "` not supported" << std::endl;
    }
}

void Engine::createMenu()
{
    this->mActiveScreen = "Main";

    // MAIN SCREEN
    Screen* MainScreen = new Screen(*this);
    std::cout << "CREATING MAIN MENU" << std::endl;
    MainScreen->setBackground("assets/mainbg.png");
    this->mScreens.insert(ScreenPair("Main", MainScreen));

    ElementButton* mainConnectButton = new ElementButton(*MainScreen, Vectorf(200, 300), "Connect");
    mainConnectButton->setImageOnIdle("assets/button-idle.png");
    mainConnectButton->setImageOnFocus("assets/button-focus.png");
    mainConnectButton->setImageOnSelect("assets/button-select.png");
    ActionFocus* mainConnectFocus = new ActionFocus(*mainConnectButton, 1);
    mainConnectButton->addAction("onDown", mainConnectFocus);
    ActionCallback* mainConnectCallback = new ActionCallback(*mainConnectButton, "Core");
    mainConnectCallback->setFunctionName("ChangeScreen");
    mainConnectCallback->addParameter("Connect");
    mainConnectButton->addAction("onSelect", mainConnectCallback);
    Effect* mainConnectEffect = new Effect(0, 0.1, Vectorf(5, 0));
    mainConnectButton->addEffect("onFocus", mainConnectEffect);
    MainScreen->addElement(0, mainConnectButton);

    ElementButton* mainQuitButton = new ElementButton(*MainScreen, Vectorf(200, 350), "Quit");
    mainQuitButton->setImageOnIdle("assets/button-idle.png");
    mainQuitButton->setImageOnFocus("assets/button-focus.png");
    mainQuitButton->setImageOnSelect("assets/button-select.png");
    Effect* mainQuitEffect = new Effect(0, 0.1, Vectorf(5, 0));
    mainQuitButton->addEffect("onFocus", mainQuitEffect);
    ActionFocus* mainQuitFocus = new ActionFocus(*mainQuitButton, 0);
    mainQuitButton->addAction("onUp", mainQuitFocus);
    
    ActionCallback* mainQuitCallbackMain = new ActionCallback(*mainQuitButton, "Net");
    mainQuitCallbackMain->setFunctionName("close");
    mainQuitCallbackMain->addParameter("main");
    mainQuitButton->addAction("onSelect", mainQuitCallbackMain);

    ActionCallback* mainQuitCallback = new ActionCallback(*mainQuitButton, "Core");
    mainQuitCallback->setFunctionName("Quit");
    mainQuitButton->addAction("onSelect", mainQuitCallback);
    MainScreen->addElement(1, mainQuitButton);

    ElementImage* mainLogo = new ElementImage(*MainScreen, Vectorf(100, 100), "assets/logo.png");
    MainScreen->addElement(2, mainLogo);

    MainScreen->setActiveElement(0);


    // CONNECT SCREEN
    Screen* ConnectScreen = new Screen(*this);
    ConnectScreen->setBackground("assets/selectbg.png");
    this->mScreens.insert(ScreenPair("Connect", ConnectScreen));

    ElementLabel* connectLabel = new ElementLabel(*ConnectScreen, Vectorf(100, 50), "Connection");
    connectLabel->setFontsize(42);
    connectLabel->setFontname("title.ttf");
    ConnectScreen->addElement(100, connectLabel);

    ElementLabel* connectLabelNickname = new ElementLabel(*ConnectScreen, Vectorf(150, 200), "Nickname");
    ConnectScreen->addElement(101, connectLabelNickname);

    ElementLabel* connectLabelServer = new ElementLabel(*ConnectScreen, Vectorf(150, 300), "Server");
    ConnectScreen->addElement(102, connectLabelServer);

    ElementInput* connectNickname = new ElementInput(*ConnectScreen, Vectorf(175, 250), 500);
    ActionFocus* connectNicknameFocus = new ActionFocus(*connectNickname, 2);
    connectNickname->addAction("onDown", connectNicknameFocus);
    connectNickname->addAction("onSelect", connectNicknameFocus);
    ConnectScreen->addElement(1, connectNickname);

    ElementInput* connectServer = new ElementInput(*ConnectScreen, Vectorf(175, 350), 500);
    ActionFocus* connectServerFocus = new ActionFocus(*connectServer, 1);
    connectServer->addAction("onUp", connectServerFocus);
    connectServerFocus = new ActionFocus(*connectServer, 3);
    connectServer->addAction("onDown", connectServerFocus);
    connectServer->addAction("onSelect", connectServerFocus);
    ConnectScreen->addElement(2, connectServer);
    Effect* connectServerEffect = new Effect(0, 0.2, Vectorf(0, 0), 0, Vectorf(0, 0), Color(0, 0, 0, 0.4));
    connectServer->addEffect("onFocus", connectServerEffect);

    ElementButton* connectButtonServer = new ElementButton(*ConnectScreen, Vectorf(150, 425), "Connect");
    connectButtonServer->setImageOnIdle("assets/button-idle.png"); 
    connectButtonServer->setImageOnFocus("assets/button-focus.png");
    connectButtonServer->setImageOnSelect("assets/button-select.png");
    ActionFocus* connectButtonServerFocus = new ActionFocus(*connectButtonServer, 2);
    connectButtonServer->addAction("onUp", connectButtonServerFocus);
    connectButtonServerFocus = new ActionFocus(*connectButtonServer, 4);
    connectButtonServer->addAction("onDown", connectButtonServerFocus);
    ActionCallback* connectButtonServerCallback = new ActionCallback(*connectButtonServer, "Net");
    connectButtonServerCallback->setFunctionName("connect");
    connectButtonServerCallback->addParameter("[2].value");
    connectButtonServerCallback->addParameter("[1].value");
    connectButtonServer->addAction("onSelect", connectButtonServerCallback);
    Effect* connectButtonServerEffect = new Effect(0, 0.1, Vectorf(5, 0));
    connectButtonServer->addEffect("onFocus", connectButtonServerEffect);
    ConnectScreen->addElement(3, connectButtonServer);

    ElementButton* connectBack = new ElementButton(*ConnectScreen, Vectorf(150, 475), "Back");
    connectBack->setImageOnIdle("assets/button-idle.png");
    connectBack->setImageOnFocus("assets/button-focus.png");
    connectBack->setImageOnSelect("assets/button-select.png");
    ActionFocus* connectBackFocus = new ActionFocus(*connectBack, 3);
    connectBack->addAction("onUp", connectBackFocus);
    ActionCallback* connectBackCallback = new ActionCallback(*connectBack, "Core");
    connectBackCallback->setFunctionName("ChangeScreen");
    connectBackCallback->addParameter("Main");
    connectBack->addAction("onSelect", connectBackCallback);
    Effect* connectBackEffect = new Effect(0, 0.1, Vectorf(5, 0));
    connectBack->addEffect("onFocus", connectBackEffect);
    ConnectScreen->addElement(4, connectBack);
    
    ConnectScreen->setActiveElement(1);


    // ROOMLIST SCREEN
    Screen* RoomListScreen = new Screen(*this);
    RoomListScreen->setBackground("assets/selectbg.png");
    this->mScreens.insert(ScreenPair("RoomList", RoomListScreen));
    
    ElementLabel* roomListLabel = new ElementLabel(*RoomListScreen, Vectorf(100, 50), "Rooms");
    roomListLabel->setFontsize(42);
    roomListLabel->setFontname("title.ttf");
    RoomListScreen->addElement(100, roomListLabel);
    
    ElementList* roomList = new ElementList(*RoomListScreen, Vectorf(50, 150), "Net.Rooms", Vectorf(700, 300));
    ActionFocus* roomListFocus = new ActionFocus(*roomList, 1);
    roomList->addAction("onDown", roomListFocus);
    RoomListScreen->addElement(0, roomList);
    
    ElementButton* roomListBack = new ElementButton(*RoomListScreen, Vectorf(75, mHeight * 0.66 + 100), "Back");
    roomListBack->setImageOnIdle("assets/button-idle.png");
    roomListBack->setImageOnFocus("assets/button-focus.png");
    roomListBack->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomListBackFocus = new ActionFocus(*roomListBack, 0);
    roomListBack->addAction("onUp", roomListBackFocus);
    roomListBackFocus = new ActionFocus(*roomListBack, 2);
    roomListBack->addAction("onRight", roomListBackFocus);
    ActionCallback* roomListBackCallback = new ActionCallback(*roomListBack, "Core");
    roomListBackCallback->setFunctionName("ChangeScreen");
    roomListBackCallback->addParameter("Connect");
    roomListBack->addAction("onSelect", roomListBackCallback);
    Effect* roomListBackEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomListBack->addEffect("onFocus", roomListBackEffect);
    RoomListScreen->addElement(1, roomListBack);
    
    ElementButton* roomListRefresh = new ElementButton(*RoomListScreen, Vectorf(mWidth * 0.25 + 75, mHeight * 0.66 + 100), "Refresh");
    roomListRefresh->setImageOnIdle("assets/button-idle.png");
    roomListRefresh->setImageOnFocus("assets/button-focus.png");
    roomListRefresh->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomListRefreshFocus = new ActionFocus(*roomListRefresh, 0);
    roomListRefresh->addAction("onUp", roomListRefreshFocus);
    roomListRefreshFocus = new ActionFocus(*roomListRefresh, 1);
    roomListRefresh->addAction("onLeft", roomListRefreshFocus);
    roomListRefreshFocus = new ActionFocus(*roomListRefresh, 3);
    roomListRefresh->addAction("onRight", roomListRefreshFocus);
    ActionCallback* roomListRefreshCallback = new ActionCallback(*roomListRefresh, "Net");
    roomListRefreshCallback->setFunctionName("refresh");
    roomListRefresh->addAction("onSelect", roomListRefreshCallback);
    Effect* roomListRefreshEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomListRefresh->addEffect("onFocus", roomListRefreshEffect);
    RoomListScreen->addElement(2, roomListRefresh);
    
    ElementButton* roomListCreate = new ElementButton(*RoomListScreen, Vectorf(mWidth * 0.5 + 75, mHeight * 0.66 + 100), "Create");
    roomListCreate->setImageOnIdle("assets/button-idle.png");
    roomListCreate->setImageOnFocus("assets/button-focus.png");
    roomListCreate->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomListCreateFocus = new ActionFocus(*roomListCreate, 0);
    roomListCreate->addAction("onUp", roomListCreateFocus);
    roomListCreateFocus = new ActionFocus(*roomListCreate, 2);
    roomListCreate->addAction("onLeft", roomListCreateFocus);
    roomListCreateFocus = new ActionFocus(*roomListCreate, 4);
    roomListCreate->addAction("onRight", roomListCreateFocus);
    ActionCallback* roomListCreateCallback = new ActionCallback(*roomListCreate, "Net");
    roomListCreateCallback->setFunctionName("join");
    roomListCreateCallback->addParameter("");
    roomListCreate->addAction("onSelect", roomListCreateCallback);
    Effect* roomListCreateEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomListCreate->addEffect("onFocus", roomListCreateEffect);
    RoomListScreen->addElement(3, roomListCreate);
    
    ElementButton* roomListJoin = new ElementButton(*RoomListScreen, Vectorf(mWidth * 0.75 + 75, mHeight * 0.66 + 100), "Join");
    roomListJoin->setImageOnIdle("assets/button-idle.png");
    roomListJoin->setImageOnFocus("assets/button-focus.png");
    roomListJoin->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomListJoinFocus = new ActionFocus(*roomListJoin, 0);
    roomListJoin->addAction("onUp", roomListJoinFocus);
    roomListJoinFocus = new ActionFocus(*roomListJoin, 3);
    roomListJoin->addAction("onLeft", roomListJoinFocus);
    ActionCallback* roomListJoinCallback = new ActionCallback(*roomListJoin, "Net");
    roomListJoinCallback->setFunctionName("join");
    roomListJoinCallback->addParameter("[0].value");
    roomListJoin->addAction("onSelect", roomListJoinCallback);
    Effect* roomListJoinEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomListJoin->addEffect("onFocus", roomListJoinEffect);
    RoomListScreen->addElement(4, roomListJoin);
    
    RoomListScreen->setActiveElement(0);


    // ROOM SCREEN
    Screen* RoomScreen = new Screen(*this);
    RoomScreen->setBackground("assets/selectbg.png");
    this->mScreens.insert(ScreenPair("Room", RoomScreen));
    
    ElementLabel* roomLabel = new ElementLabel(*RoomScreen, Vectorf(100, 50), "Rooms");
    roomLabel->setFontsize(42);
    roomLabel->setFontname("title.ttf");
    RoomScreen->addElement(100, roomLabel);
    
    ElementList* roomPlayerList = new ElementList(*RoomScreen, Vectorf(50, 150), "Net.Players", Vectorf(mWidth * 0.4, mHeight * 0.25));
    ActionFocus* roomPlayerListFocus = new ActionFocus(*roomPlayerList, 1);
    roomPlayerList->addAction("onDown", roomPlayerListFocus);
    RoomScreen->addElement(0, roomPlayerList);
    
    ElementButton* roomBack = new ElementButton(*RoomScreen, Vectorf(75, mHeight * 0.66 + 100), "Back");
    roomBack->setImageOnIdle("assets/button-idle.png");
    roomBack->setImageOnFocus("assets/button-focus.png");
    roomBack->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomBackFocus = new ActionFocus(*roomBack, 0);
    roomBack->addAction("onUp", roomBackFocus);
    roomBackFocus = new ActionFocus(*roomBack, 2);
    roomBack->addAction("onRight", roomBackFocus);
    ActionCallback* roomBackCallback = new ActionCallback(*roomBack, "Core");
    roomBackCallback->setFunctionName("ChangeScreen");
    roomBackCallback->addParameter("RoomList");
    roomBack->addAction("onSelect", roomBackCallback);
    roomBackCallback = new ActionCallback(*roomBack, "Net");
    roomBackCallback->setFunctionName("close");
    roomBackCallback->addParameter("room");
    roomBack->addAction("onSelect", roomBackCallback);
    Effect* roomBackEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomBack->addEffect("onFocus", roomBackEffect);
    RoomScreen->addElement(1, roomBack);
    
    ElementButton* roomStart = new ElementButton(*RoomScreen, Vectorf(mWidth * 0.25 + 75, mHeight * 0.66 + 100), "Start");
    roomStart->setImageOnIdle("assets/button-idle.png");
    roomStart->setImageOnFocus("assets/button-focus.png");
    roomStart->setImageOnSelect("assets/button-select.png");
    ActionFocus* roomStartFocus = new ActionFocus(*roomStart, 0);
    roomStart->addAction("onUp", roomStartFocus);
    roomStartFocus = new ActionFocus(*roomStart, 1);
    roomStart->addAction("onLeft", roomStartFocus);
    ActionCallback* roomStartCallback = new ActionCallback(*roomStart, "Net");
    roomStartCallback->setFunctionName("start");
    roomStart->addAction("onSelect", roomStartCallback);
    Effect* roomStartEffect = new Effect(0, 0.1, Vectorf(0, -5));
    roomStart->addEffect("onFocus", roomStartEffect);
    RoomScreen->addElement(2, roomStart);
    
    RoomScreen->setActiveElement(0);
}

void Engine::update(float time)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        this->mScreens[this->mActiveScreen]->event(event);
    this->mScreens[this->mActiveScreen]->update(time);
}

void Engine::draw()
{
    SDL_FillRect(mDisplaySurface, NULL, 0x000000);
    this->mScreens[this->mActiveScreen]->draw(mDisplaySurface);
    SDL_Flip(mDisplaySurface);
}

void Engine::Callback(const ModuleParameter& moduleParameter)
{
    if (moduleParameter.function == "Quit")
        this->quit();
    else if (moduleParameter.function == "ChangeScreen")
        this->changeScreen(moduleParameter.parameters.front());
}