#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	auto colorLayer = LayerColor::create(Color4B(0,130,130,150));
    // add layer as a child to scene
    scene->addChild(layer,1);
	scene->addChild(colorLayer, 0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	cardPosition = 1;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	auto cardBack = Sprite::create("cardback.png");
	cardBack->setAnchorPoint(Point(1.0,0.0));
	cardBack->setPosition(40,775);
	cardBack->setRotation(-45.0);

	this->addChild(cardBack);
	//-------------BackCard Listener --------

	auto cardBackListener = EventListenerTouchOneByOne::create();


	cardBackListener->onTouchBegan = [=](Touch* touch, Event* e){

		Point p = touch->getLocation();
		if(p.x <= 27 && p.y >= 762){
			auto fade = FadeIn::create(2);
			auto selectedCard = Sprite::create("clubs_jack.png");
			selectedCard->setAnchorPoint(Point(0,0));
			selectedCard->setPosition(cardPosition * 30,20);
			selectedCard->setOpacity(0);
			selectedCard->runAction(fade);
			selectedCard->setTag(cardPosition);
			this->addChild(selectedCard);
			cardPosition++;
		}
		return true;
	};


	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardBackListener, cardBack);
	//------------- BackCard Listener Ended -------

	//-------------HandCard Listener --------

	auto handCardListener = EventListenerTouchOneByOne::create();
	handCardListener->setSwallowTouches(true);

	handCardListener->onTouchBegan = [=](Touch* touch, Event* e){
		int i, j;
		for(i = cardPosition - 1; i >= 1; i--){
			Rect rect = Rect( i * 30, 20, 150, 225);
			if(rect.containsPoint(touch->getLocation())){
				
				auto card = getChildByTag(i);
				log("Card %d %f", i, card->getScale());
				if(card->getScale() < 1.1)
					card->setScale(1.2);
				else
					card->setScale(1.0);
				break;
			}
			
		}
		return true;

	};


	
	_eventDispatcher->addEventListenerWithFixedPriority(handCardListener, 1);
	//------------- HandCard Listener Ended -------

	return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
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
