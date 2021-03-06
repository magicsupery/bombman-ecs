/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <algorithm>

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "src/ecs/system_manager.h"
#include "src/system/move_system.h"
#include "src/system/controller_system.h"
#include "src/system/render_system.h"
#include "src/system/skill_system.h"

#include "src/component/controller.hpp"

#include "src/factory/entity_factory.h"
#include "src/context/game_context.h"

#include "src/helper/utils.hpp"

USING_NS_CC;
using namespace ecs;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

	//add map
	auto map = TMXTiledMap::create("bombman.tmx");
	this->addChild(map, -1);
	GameContext::running_scene = this;

	// systemmanager add
	SystemManager::getInstance()->addSystem<ControllerSystem>();
	SystemManager::getInstance()->addSystem<MoveSystem>();
	SystemManager::getInstance()->addSystem<RenderSystem>();
	SystemManager::getInstance()->addSystem<SkillSystem>();
	// create player needed
	EntityFactory::getInstance()->createP1();

	// add the move key listener
	auto move_listener = EventListenerKeyboard::create();

	//之前使用bit是因为忽略了炸弹人的移动方式，
	//根据炸弹人手感调优，还是需要使用最后按下的移动方向进行移动来调整
	//所以最终决定使用vector，而不是bit位进行记录
	move_listener->onKeyPressed = [](EventKeyboard::KeyCode keycode , Event* event){
		if(keycode == EventKeyboard::KeyCode::KEY_W)
		{
			//GameContext::keybord_bit |= static_cast<unsigned long long>(KeyboradCode::KEY_W);
			GameContext::move_keyboardcode_vector.emplace_back(KeyboradCode::KEY_W);
		}

		else if(keycode == EventKeyboard::KeyCode::KEY_D)
		{

			//GameContext::keybord_bit |= static_cast<unsigned long long>(KeyboradCode::KEY_D);
			GameContext::move_keyboardcode_vector.emplace_back(KeyboradCode::KEY_D);
		}
		else if(keycode == EventKeyboard::KeyCode::KEY_A)
		{

			//GameContext::keybord_bit |= static_cast<unsigned long long>(KeyboradCode::KEY_A);
			GameContext::move_keyboardcode_vector.emplace_back(KeyboradCode::KEY_A);
		}
		else if(keycode == EventKeyboard::KeyCode::KEY_S)
		{

			//GameContext::keybord_bit |= static_cast<unsigned long long>(KeyboradCode::KEY_S);
			GameContext::move_keyboardcode_vector.emplace_back(KeyboradCode::KEY_S);
		}

		SystemManager::getInstance()->getSystem<ControllerSystem>()->notify_keyboard_move_event_changed();

	};

	move_listener->onKeyReleased = [](EventKeyboard::KeyCode keycode , Event* event){
		if(keycode == EventKeyboard::KeyCode::KEY_W)
		{
			//GameContext::keybord_bit &= ~static_cast<unsigned long long>(KeyboradCode::KEY_W);
			GameContext::move_keyboardcode_vector.erase(std::remove(
						GameContext::move_keyboardcode_vector.begin(),
						GameContext::move_keyboardcode_vector.end(),
						KeyboradCode::KEY_W));
		}
		else if(keycode == EventKeyboard::KeyCode::KEY_D)
		{
			//GameContext::keybord_bit &= ~static_cast<unsigned long long>(KeyboradCode::KEY_D);
			GameContext::move_keyboardcode_vector.erase(std::remove(
						GameContext::move_keyboardcode_vector.begin(),
						GameContext::move_keyboardcode_vector.end(),
						KeyboradCode::KEY_D));
		}
		else if(keycode == EventKeyboard::KeyCode::KEY_A)
		{
			//GameContext::keybord_bit &= ~static_cast<unsigned long long>(KeyboradCode::KEY_A);
			GameContext::move_keyboardcode_vector.erase(std::remove(
						GameContext::move_keyboardcode_vector.begin(),
						GameContext::move_keyboardcode_vector.end(),
						KeyboradCode::KEY_A));
		}
		else if(keycode == EventKeyboard::KeyCode::KEY_S)
		{
			//GameContext::keybord_bit &= ~static_cast<unsigned long long>(KeyboradCode::KEY_S);
			GameContext::move_keyboardcode_vector.erase(std::remove(
						GameContext::move_keyboardcode_vector.begin(),
						GameContext::move_keyboardcode_vector.end(),
						KeyboradCode::KEY_S));
		}

		SystemManager::getInstance()->getSystem<ControllerSystem>()->notify_keyboard_move_event_changed();
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(move_listener, this);


	// add the skill key listener
	auto skill_listener = EventListenerKeyboard::create();

	skill_listener->onKeyPressed = [](EventKeyboard::KeyCode keycode , Event* event){
		if(keycode == EventKeyboard::KeyCode::KEY_J)
		{
			GameContext::keybord_bit |= static_cast<unsigned long long>(KeyboradCode::KEY_J);
		}
		SystemManager::getInstance()->getSystem<ControllerSystem>()->notify_keyboard_skill_event_changed();
	};

	skill_listener->onKeyReleased = [](EventKeyboard::KeyCode keycode , Event* event){
		if(keycode == EventKeyboard::KeyCode::KEY_J)
		{
			GameContext::keybord_bit &= ~static_cast<unsigned long long>(KeyboradCode::KEY_J);
		}

		SystemManager::getInstance()->getSystem<ControllerSystem>()->notify_keyboard_skill_event_changed();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(skill_listener, this);
	/*
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	*/
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
