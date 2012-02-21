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
#include "Skin/Exception.h"
#include "Skin/Filesystem/Directory.h"
#include "Skin/Filesystem/File.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <rapidxml/rapidxml.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

using namespace Skin;

Engine::Engine(std::string const & cfgFile) :
mParserConfiguration(NULL),
mConfigurationFile(cfgFile),
mSkinPath(""),
mFullscreen(false),
mWidth(0),
mHeight(0),
mFramerate(0),
mVsync(false),
mRunning(true),
mDisplaySurface(NULL),
mMutex(NULL)
{
    this->addModule("Core", this);
	this->setupParserConfiguration();
	this->setupParserSkin();

	if (!mParserConfiguration->parse(mConfigurationFile))
    {
        std::cout << "Loading default configuration" << std::endl;

        this->mSkinPath = DEFAULT_SKIN_PATH;
		this->mSkinName = DEFAULT_SKIN_NAME;
		this->mLanguage = DEFAULT_LANGUAGE;
        this->mFullscreen = DEFAULT_VIDEO_MODE;
        this->mWidth = DEFAULT_WIDTH;
        this->mHeight = DEFAULT_HEIGHT;
		this->mFramerate = DEFAULT_FRAMERATE;
		this->mVsync = DEFAULT_VSYNC;
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
	// Check correct value of configuration
    if (!mWidth || !mHeight)
    {
        std::cout << "Loading default width and height values." << std::endl;

        mWidth = DEFAULT_WIDTH;
        mHeight = DEFAULT_HEIGHT;
    }
	if (mFramerate > 0 && mFramerate < 200)
	{
		std::cout << "Loading default framerate value." << std::endl;
		mFramerate = DEFAULT_FRAMERATE;
	}

    // Init SDL
    int flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    flags |= mFullscreen ? SDL_FULLSCREEN : 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    mDisplaySurface = SDL_SetVideoMode(mWidth, mHeight, 32, flags);
    
    // Init SDL_image
    flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    IMG_Init(flags);
    
	// Init SDL_ttf
    TTF_Init();
    
    SDL_EnableUNICODE(SDL_ENABLE);
    SDL_EnableKeyRepeat(400, 20);

	Directory skinDir(mSkinPath);
	if (skinDir.hasDirectory(mSkinName))
	{
		if (skinDir.getDirectory(mSkinName)->hasFile("skin.xml"))
			mParserSkin->parse(skinDir.getDirectory(mSkinName)->getFile("skin.xml")->getRelativePath());
		else
		{
			std::cout << "Error : Unable to access to skin.xml" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Error : Unable to access to skin path" << std::endl;
		return false;
	}
    return true;
}

void Engine::quit()
{
    this->mRunning = false;
}

void Engine::launch(bool threaded)
{
	if (threaded == true)
	{
		SDL_Thread* thread = SDL_CreateThread(Engine::entry_point, this);
		if (thread == NULL)
			throw Exception("Could not create new thread");
	}
	else
	{
		this->run();
	}
}

void Engine::update(double time)
{
	if (mActiveScreen.size())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		    this->mScreens[this->mActiveScreen]->event(event);
		this->mScreens[this->mActiveScreen]->update(time);
	}
}

void Engine::draw()
{
    SDL_FillRect(mDisplaySurface, NULL, 0x000000);
	if (mActiveScreen.size())
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

void Engine::run()
{
    double oldTime = 0;

    while (mRunning)
    {
        double time = SDL_GetTicks() / 1000.0;
		if (time - oldTime < 1.0 / mFramerate)
		{
			SDL_Delay(Uint32(((1.0 / mFramerate) - (time - oldTime)) * 1000.0));
			time = SDL_GetTicks() / 1000.0;
		}
        this->update(time - oldTime);
        oldTime = time;
        this->draw();
    }
    SDL_Quit();
}

int Engine::entry_point(void *data)
{
	Engine* engine = reinterpret_cast<Engine*>(data);

	if (engine)
		engine->run();
	return 0;
}

void Engine::setupParserConfiguration()
{
	mParserConfiguration = new Parser();

	Node* root = new Node(NULL, "configuration");
	mParserConfiguration->setRoot(root);
	Node* nodeSkin = root->createChild("skin");
	Node* nodeSkinPath = nodeSkin->createChild("path");
	Node* nodeSkinName = nodeSkin->createChild("name");
	Node* nodeVideo = root->createChild("video");
	Node* nodeVideoFullscreen = nodeVideo->createChild("fullscreen");
	Node* nodeVideoWidth = nodeVideo->createChild("width");
	Node* nodeVideoHeight = nodeVideo->createChild("height");
	Node* nodeVideoFramerate = nodeVideo->createChild("framerate");
	Node* nodeVideoVsync = nodeVideo->createChild("vsync");
	nodeSkinPath->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinPath));
	nodeSkinName->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinName));
	nodeVideoFullscreen->setCallback(this, static_cast<NodeCallback>(&Engine::parseVideoFullscreen));
	nodeVideoWidth->setCallback(this, static_cast<NodeCallback>(&Engine::parseVideoWidth));
	nodeVideoHeight->setCallback(this, static_cast<NodeCallback>(&Engine::parseVideoHeight));
	nodeVideoFramerate->setCallback(this, static_cast<NodeCallback>(&Engine::parseVideoFramerate));
	nodeVideoVsync->setCallback(this, static_cast<NodeCallback>(&Engine::parseVideoVsync));
}

void Engine::parseSkinPath(XMLNode* node)
{
	mSkinPath = node->value();
}

void Engine::parseSkinName(XMLNode* node)
{
	mSkinName = node->value();
}

void Engine::parseVideoFullscreen(XMLNode* node)
{
	std::string value(node->value());

	if (value == "0")
		mFullscreen = false;
	else if (value == "1")
		mFullscreen = true;
}

void Engine::parseVideoWidth(XMLNode* node)
{
	mWidth = atoi(node->value());
}

void Engine::parseVideoHeight(XMLNode* node)
{
	mHeight = atoi(node->value());
}

void Engine::parseVideoFramerate(XMLNode* node)
{
	mFramerate = atoi(node->value());
}

void Engine::parseVideoVsync(XMLNode* node)
{
	std::string value(node->value());

	if (value == "0")
		mVsync = false;
	else if (value == "1")
		mVsync = true;
}

void Engine::setupParserSkin()
{
	/*
	*	<font> : name / size / *color / *bold / *italic / *underline
	*	<img> : src
	*	<size> : *x / *y / *width / *height / *length
	*	<box> : bg-color / border-color
	*/
	mParserSkin = new Parser();

	Node* root = new Node(NULL, "skin");
	mParserSkin->setRoot(root);
	Node* skinVersion = root->createChild("version");
	Node* skinAuthor = root->createChild("author");
	Node* skinDescription = root->createChild("description");
	Node* skinInclude = root->createChild("include");
	Node* skinResolution = root->createChild("resolution");
	skinResolution->addAttribute("width");
	skinResolution->addAttribute("height");
	Node* skinScreen = root->createChild("screen");
	skinScreen->addAttribute("name");
	skinScreen->addAttribute("background", false);
	Node* skinElement = skinScreen->createChild("element");
	skinElement->addAttribute("x");
	skinElement->addAttribute("y");
	skinElement->addAttribute("id");
	skinElement->addAttribute("type");
	Node* skinElementFont = skinElement->createChild("font");
	skinElementFont->addAttribute("name");
	skinElementFont->addAttribute("size");
	skinElementFont->addAttribute("color", false);
	skinElementFont->addAttribute("bold", false);
	skinElementFont->addAttribute("italic", false);
	skinElementFont->addAttribute("underline", false);
	Node* skinElementImg = skinElement->createChild("img");
	skinElementImg->addAttribute("src");
	skinElementImg->addAttribute("event", false);
	Node* skinElementSize = skinElement->createChild("size");
	skinElementSize->addAttribute("x", false);
	skinElementSize->addAttribute("y", false);
	skinElementSize->addAttribute("width", false);
	skinElementSize->addAttribute("height", false);
	skinElementSize->addAttribute("length", false);
	Node* skinElementBox = skinElement->createChild("box");
	skinElementBox->addAttribute("bg-color", false);
	skinElementBox->addAttribute("border-color", false);
	Node* skinAction = skinElement->createChild("action");
	skinAction->addAttribute("event");
	Node* skinEffect = skinAction->createSibling("effect");
	skinAction->addAttribute("event");
	skinAction->addAttribute("start");
	skinAction->addAttribute("end");
	Node* skinEffectTranslate = skinEffect->createChild("translate");
	skinEffectTranslate->addAttribute("x", true);
	skinEffectTranslate->addAttribute("y", true);
	Node* skinEffectRotate = skinEffect->createChild("rotate");
	skinEffectRotate->addAttribute("angle", true);
	Node* skinEffectScale = skinEffect->createChild("scale");
	skinEffectScale->addAttribute("x", true);
	skinEffectScale->addAttribute("y", true);
	skinVersion->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinVersion));
	skinAuthor->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinAuthor));
	skinDescription->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinDescription));
	skinInclude->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinInclude));
	skinResolution->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinResolution));
	skinScreen->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinScreen));
	skinElement->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinElement));
	skinElementFont->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinElementFont));
	skinElementImg->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinElementImg));
	skinElementSize->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinElementSize));
	skinElementBox->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinElementBox));
	skinAction->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinAction));
	skinEffect->setCallback(this, static_cast<NodeCallback>(&Engine::parseSkinEffect));
}

void Engine::parseSkinVersion(XMLNode* node)
{
	mVersion = node->value();
}

void Engine::parseSkinAuthor(XMLNode* node)
{
	mAuthor = node->value();
}

void Engine::parseSkinDescription(XMLNode* node)
{
	mDescription = node->value();
}

void Engine::parseSkinInclude(XMLNode* node)
{
	File file(node->value());

	if (file.exists())
	{
		mParserSkin->parse(node->value());
	}
	else
	{
		std::cout << "Warning: Cannot include file `" << node->value() << "`, skipping." << std::endl;
	}
}

void Engine::parseSkinResolution(XMLNode* node)
{
	XMLAttribute* attrWidth = node->first_attribute("width");
	XMLAttribute* attrHeight = node->first_attribute("height");

	if (attrWidth)
		mSkinWidth = atoi(attrWidth->value());
	if (attrHeight)
		mSkinHeight = atoi(attrHeight->value());
}

void Engine::parseSkinScreen(XMLNode* node)
{
	XMLAttribute* attrName = node->first_attribute("name");
	XMLAttribute* attrBackground = node->first_attribute("background");

	if (attrName && attrBackground)
	{
		std::string name = attrName->value();
		std::string background = attrBackground->value();

		if (!mScreens.count(attrName->value()))
		{
			mScreens[name] = new Screen(*this);
			mScreens[name]->setBackground(background);

			if (mActiveScreen.empty())
				mActiveScreen = name;
		}
	}
}

void Engine::parseSkinElement(XMLNode* node)
{
	XMLAttribute* attrX = node->first_attribute("x");
	XMLAttribute* attrY = node->first_attribute("y");
	XMLAttribute* attrID = node->first_attribute("id");
	XMLAttribute* attrType = node->first_attribute("type");

	if (attrX && attrY && attrID && attrType)
	{
		XMLNode* nodeScreen = node->parent();
		if (mScreens.count(nodeScreen->value()))
		{
			Screen* screen = mScreens[nodeScreen->value()];
			int x = atoi(attrX->value());
			int y = atoi(attrY->value());
			int id = atoi(attrID->value());
			std::string type = attrType->value();

			Element* element = NULL;
			if (type == "label")
			{
				// NEED <font>
				element = new ElementLabel(*screen, Vectorf(x, y));
			}
			else if (type == "image")
			{
				// NEED <img>
				element = new ElementImage(*screen, Vectorf(x, y));
			}
			else if (type == "button")
			{
				// NEED <font> <img>
				element = new ElementButton(*screen, Vectorf(x, y));
			}
			else if (type == "input")
			{
				// NEED <size> <font> <box>
				element = new ElementInput(*screen, Vectorf(x, y));
			}
			else if (type == "list")
			{
				// NEED <size> <font> <box> <value>
				element = new ElementList(*screen, Vectorf(x, y));
			}
			else if (type == "video")
			{
				// NEED <size>
			}

			screen->addElement(id, element);
		}
	}
}

void Engine::parseSkinElementFont(XMLNode* node)
{
	XMLAttribute* attrName = node->first_attribute("name");
	XMLAttribute* attrSize = node->first_attribute("size");
	XMLAttribute* attrColor = node->first_attribute("color");
	XMLAttribute* attrBold = node->first_attribute("bold");
	XMLAttribute* attrItalic = node->first_attribute("italic");
	XMLAttribute* attrUnderline = node->first_attribute("underline");
	XMLAttribute* attrStrike = node->first_attribute("strike");

	if (attrName && attrSize)
	{
		XMLNode* nodeElement = node->parent();
		XMLNode* nodeScreen = nodeElement->parent();

		if (nodeElement && nodeScreen)
		{
			XMLAttribute* attrID = nodeElement->first_attribute("id");
			XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
			std::string screenName = attrScreenName->value();
			int id = atoi(attrID->value());

			Element* element = mScreens[screenName]->getElement(id);
			if (element)
			{
				if (attrName)
					element->parse("font-name", attrName->value());
				if (attrSize)
					element->parse("font-size", attrSize->value());
				if (attrColor)
					element->parse("font-color", attrColor->value());
				if (attrBold)
					element->parse("font-bold", attrBold->value());
				if (attrItalic)
					element->parse("font-italic", attrBold->value());
				if (attrUnderline)
					element->parse("font-underline", attrUnderline->value());
				if (attrStrike)
					element->parse("font-strike", attrStrike->value());
			}
		}
	}
}

void Engine::parseSkinElementImg(XMLNode* node)
{
	XMLAttribute* attrName = node->first_attribute("file");
	XMLAttribute* attrEvent = node->first_attribute("event");
	XMLAttribute* attrScaleX = node->first_attribute("scaleX");
	XMLAttribute* attrScaleY = node->first_attribute("scaleY");
	XMLAttribute* attrRotation = node->first_attribute("rotation");

	if (attrName)
	{
		XMLNode* nodeElement = node->parent();
		XMLNode* nodeScreen = nodeElement->parent();

		if (nodeElement && nodeScreen)
		{
			XMLAttribute* attrID = nodeElement->first_attribute("id");
			XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
			std::string screenName = attrScreenName->value();
			int id = atoi(attrID->value());

			Element* element = mScreens[screenName]->getElement(id);
			if (element)
			{
				if (attrEvent)
					element->parse("img-" + std::string(attrEvent->value()) + "-file", attrName->value());
				else
					element->parse("img-file", attrName->value());
				if (attrScaleX || attrScaleY)
				{
					std::string x(attrScaleX ? attrScaleX->value() : "1");
					std::string y(attrScaleY ? attrScaleY->value() : "1");

					element->parse("img-scale", x + " " + y);
				}
				if (attrRotation)
					element->parse("img-rotation", attrRotation->value());
			}
		}
	}
}

void Engine::parseSkinElementSize(XMLNode* node)
{
	XMLAttribute* attrX = node->first_attribute("x");
	XMLAttribute* attrY = node->first_attribute("y");
	XMLAttribute* attrWidth = node->first_attribute("width");
	XMLAttribute* attrHeight = node->first_attribute("height");
	XMLAttribute* attrLength = node->first_attribute("length");

	XMLNode* nodeElement = node->parent();
	XMLNode* nodeScreen = nodeElement->parent();

	if (nodeElement && nodeScreen)
	{
		XMLAttribute* attrID = nodeElement->first_attribute("id");
		XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
		std::string screenName = attrScreenName->value();
		int id = atoi(attrID->value());

		Element* element = mScreens[screenName]->getElement(id);
		if (element)
		{
			if (attrX)
				element->parse("size-x", attrX->value());
			if (attrY)
				element->parse("size-y", attrY->value());
			if (attrWidth)
				element->parse("size-width", attrWidth->value());
			if (attrHeight)
				element->parse("size-height", attrHeight->value());
			if (attrLength)
				element->parse("size-length", attrLength->value());
		}
	}
}

void Engine::parseSkinElementBox(XMLNode* node)
{
	XMLAttribute* attrBgColor = node->first_attribute("bg-color");
	XMLAttribute* attrBorderColor = node->first_attribute("border-color");
	XMLAttribute* attrRadius = node->first_attribute("radius");

	XMLNode* nodeElement = node->parent();
	XMLNode* nodeScreen = nodeElement->parent();

	if (nodeElement && nodeScreen)
	{
		XMLAttribute* attrID = nodeElement->first_attribute("id");
		XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
		std::string screenName = attrScreenName->value();
		int id = atoi(attrID->value());

		Element* element = mScreens[screenName]->getElement(id);
		if (element)
		{
			if (attrBgColor)
				element->parse("box-bg-color", attrBgColor->value());
			if (attrBorderColor)
				element->parse("box-border-color", attrBorderColor->value());
			if (attrRadius)
				element->parse("box-radius", attrRadius->value());
		}
	}
}

void Engine::parseSkinAction(XMLNode* node)
{
	XMLAttribute* attrEvent = node->first_attribute("event");

	if (attrEvent)
	{
		std::string value(node->value());

		XMLNode* nodeElement = node->parent();
		XMLNode* nodeScreen = nodeElement->parent();

		if (nodeElement && nodeScreen)
		{
			XMLAttribute* attrID = nodeElement->first_attribute("id");
			XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
			std::string screenName = attrScreenName->value();
			int id = atoi(attrID->value());

			Element* element = mScreens[screenName]->getElement(id);
			if (element)
			{
				if (std::for_each<std::string::iterator, int (*)(int)>(value.begin(), value.end(), isdigit))
					element->addAction(attrEvent->value(), new ActionFocus(*element, atoi(value.c_str())));
				else
					element->addAction(attrEvent->value(), new ActionCallback(*element, value));
			}
		}
	}
}

void Engine::parseSkinEffect(XMLNode* node)
{
	XMLAttribute* attrEvent = node->first_attribute("event");
	XMLAttribute* attrStart = node->first_attribute("start");
	XMLAttribute* attrEnd = node->first_attribute("end");
	
	if (attrEvent && attrStart && attrEnd)
	{
		XMLNode* nodeElement = node->parent();
		XMLNode* nodeScreen = nodeElement->parent();

		if (nodeElement && nodeScreen)
		{
			XMLAttribute* attrID = nodeElement->first_attribute("id");
			XMLAttribute* attrScreenName =  nodeScreen->first_attribute("name");
			std::string screenName = attrScreenName->value();
			int id = atoi(attrID->value());

			Element* element = mScreens[screenName]->getElement(id);
			if (element)
			{
				Effect* effect = new Effect(atof(attrStart->value()), atof(attrEnd->value()));
				element->addEffect(attrEvent->value(), effect);
				
				if (node->first_node("translate"))
					parseSkinEffectTranslate(effect, node->first_node("translate"));
				if (node->first_node("rotate"))
					parseSkinEffectRotate(effect, node->first_node("rotate"));
				if (node->first_node("scale"))
					parseSkinEffectScale(effect, node->first_node("scale"));
				if (node->first_node("color"))
					parseSkinEffectColor(effect, node->first_node("color"));
			}
		}
	}
}

void Engine::parseSkinEffectTranslate(Effect* effect, XMLNode* node)
{
	XMLAttribute* attrX = node->first_attribute("x");
	XMLAttribute* attrY = node->first_attribute("y");
	double x = attrX ? atof(attrX->value()) : 0;
	double y = attrY ? atof(attrY->value()) : 0;

	effect->setTranslation(Vectorf(x, y));
}

void Engine::parseSkinEffectRotate(Effect* effect, XMLNode* node)
{
	XMLAttribute* attrAngle = node->first_attribute("x");
	double angle = attrAngle ? atof(attrAngle->value()) : 0;

	effect->setRotation(angle);
}

void Engine::parseSkinEffectScale(Effect* effect, XMLNode* node)
{
	XMLAttribute* attrX = node->first_attribute("x");
	XMLAttribute* attrY = node->first_attribute("y");
	double x = attrX ? atof(attrX->value()) : 0;
	double y = attrY ? atof(attrY->value()) : 0;

	effect->setScale(Vectorf(x, y));
}

void Engine::parseSkinEffectColor(Effect* effect, XMLNode* node)
{
	XMLAttribute* attrValue = node->first_attribute("value");

	if (attrValue)
		effect->setColor(Color(attrValue->value()));
}