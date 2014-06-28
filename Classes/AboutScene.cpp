#include "AboutScene.h"
#include "HelloWorldScene.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>


USING_NS_CC;

Scene* AboutScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = AboutScene::create();
    // add layer as a child to scene
    scene->addChild(layer,1);	
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool AboutScene::init()
{
	
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("about-content.png");
	background->setAnchorPoint(Point(0,0));
	background->setPosition(0,0);
	background->setZOrder(0);
	this->addChild(background);

	
	
	
	auto BackButton = MenuItemImage::create("back.png", "back.png", "back.png", CC_CALLBACK_1(AboutScene::Back, this));
    
	BackButton->setPosition(visibleSize.width/2, 90);

	
	//BackButton->setScale(1.0);

	auto buttons = Menu::create(BackButton, NULL);



    buttons->setPosition(0,0);
    this->addChild(buttons);

	return true;

	
}

void AboutScene::Back(Ref* pSend)
{
	log("Quit Card Pressed!");
	auto helloWordScene = HelloWorld::createScene();
	auto animation = TransitionFlipX::create(1, helloWordScene);
	Director::getInstance()->replaceScene(animation);
}

void AboutScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

