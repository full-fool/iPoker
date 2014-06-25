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
	cardBack->setPosition(40,730);
	cardBack->setRotation(-45.0);

	this->addChild(cardBack);
	//-------------BackCard Listener --------

	auto cardBackListener = EventListenerTouchOneByOne::create();

	
	cardBackListener->onTouchBegan = [=](Touch* touch, Event* e){

		Point p = touch->getLocation();
		if(p.x <= 27 && p.y >= 720){
			/*
			auto fade = FadeIn::create(0.5);
			auto selectedCard = Sprite::create("clubs_jack.png");
			selectedCard->setAnchorPoint(Point(0,0));
			selectedCard->setPosition(cardPosition * 30,20);
			selectedCard->setOpacity(0);
			selectedCard->runAction(fade);
			selectedCard->setTag(cardPosition);
			this->addChild(selectedCard);
			cardPosition++;
			*/
			auto selectedCard = Sprite::create("clubs_jack.png");
			

			selectedCard->setAnchorPoint(Point(0,0));
			
			selectedCard->setPosition(26,721);
			selectedCard->setRotation(-45.0);
			Size winSize = Director::getInstance()->getWinSize();
			selectedCard->runAction(RotateTo::create(0.5, 0));
			CCActionInterval * moveBy = CCMoveBy::create(0.5,ccp(cardPosition * 30 - 10, 50 - winSize.height));
			
			selectedCard->runAction(moveBy);
			
			

			CCOrbitCamera * flipYAction = CCOrbitCamera::create(0.5f, 1, 0, 90, -90, 0, 0);
			selectedCard->runAction(flipYAction);
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


	// Add play card button
	auto playCardButton = MenuItemLabel::create(Label::create("[Play Card]", "Arial", 20), CC_CALLBACK_1(GameScene::playCard, this));
    
    playCardButton->setPosition(400,300);
    auto buttons = Menu::create(playCardButton, NULL);
    buttons->setPosition(0,0);
    this->addChild(buttons);

	return true;
}


void GameScene::playCard(Ref* pSender)
{
    int i, j, k;
    float public_x = 200, public_y = 330;

    log("Play Card Button Pressed!");
    std::vector<Node*> selected;
    std::vector<Node*> remain;
    for(i = 1; i < cardPosition; i++){
        // Check status of all cards 
        Node* card = getChildByTag(i);
        
        if(card->getScale() < 1.1)
            remain.push_back(card);
        else
            selected.push_back(card);
    }

	for(i = 0; i < public_deck.size(); i++){
		public_deck[i]->setOpacity(20);
		public_deck[i]->setZOrder(0);
	}

    for(i = 0; i < selected.size(); i++){
        Node* card = selected[i];
		card->setZOrder(1);
        auto moveTo = MoveTo::create(1, Point(public_x, public_y));
        auto scaleTo = ScaleTo::create(1, 1.0);
        auto spawn = Spawn::create(moveTo, scaleTo, NULL);
        card->runAction(spawn);
        public_x += 30.0;
		card->setTag(0);

		public_deck.push_back(card);

    }
	for(i = 0; i < remain.size(); i++){
		int position = i + 1;
		Node* card = remain[i];
		auto moveTo = MoveTo::create(0.5, Point(position * 30, 0));
		card->runAction(moveTo);
		card->setTag(position);
	}
	cardPosition = remain.size() + 1;

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

