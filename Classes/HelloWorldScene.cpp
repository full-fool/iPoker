#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	auto colorLayer = LayerColor::create(Color4B(0,130,130,150));
    // add layer as a child to scene
    scene->addChild(layer,1);
	scene->addChild(colorLayer, 0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

 //   /////////////////////////////
 //   // 2. add a menu item with "X" image, which is clicked to quit the program
 //   //    you may modify it.

 //   // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Point::ZERO);
 //   this->addChild(menu, 1);

 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   auto label = LabelTTF::create("Hello World", "Arial", 24);
 //   
 //   // position the label on the center of the screen
 //   label->setPosition(Point(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - label->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(label, 1);

 //   // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(sprite, 0);
    
	auto label = LabelTTF::create("iPoker", "Arial", 72);
	label->setAnchorPoint(Point(0,1));
	label->setPosition(30,700);
	this->addChild(label);



	auto newGame = MenuItemLabel::create(Label::create("New Game", "Arial", 48), CC_CALLBACK_1(HelloWorld::toGameScene, this));
	auto about = MenuItemLabel::create(Label::create("About", "Arial", 48));
	auto exitGame = MenuItemLabel::create(Label::create("Exit Game", "Arial", 48), CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	newGame->setAnchorPoint(Point(0,0));
	about->setAnchorPoint(Point(0,0));
	exitGame->setAnchorPoint(Point(0,0));
	newGame->setPosition(200,300);
	about->setPosition(200,200);
	exitGame->setPosition(200,100);
	auto menu = Menu::create(newGame, about, exitGame, NULL);
	menu->setPosition(0,0);
	 



	this->addChild(menu);
	CCLog("haha");
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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


void HelloWorld::toGameScene(Ref* pSender)
{
	log("New game");
	auto gameScene = GameScene::createScene();
	auto animation = TransitionFlipX::create(1, gameScene);
	Director::getInstance()->replaceScene(animation);
}

