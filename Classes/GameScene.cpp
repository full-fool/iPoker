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
			this->addChild(selectedCard, 1);
			cardPosition++;


		}
		return true;
	};
	
	


	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardBackListener, cardBack);
	//------------- BackCard Listener Ended -------

	//players and bubbles
	auto Player1 = Sprite::create("player1.png");
	Player1->setPosition(100,350);
	Player1->setScale(0.2);
	//Size playerSize = Player1->getContentSize();
	//CCLog("player size is %d witdh and %d height", playerSize.width, playerSize.height);

	auto Player2 = Sprite::create("player2.png");
	Player2->setPosition(100,410);
	Player2->setScale(0.2);
	//Size playerSize = Player1->getContentSize();
	//CCLog("player size is %d witdh and %d height", playerSize.width, playerSize.height);
	auto Player3 = Sprite::create("player3.png");
	Player3->setPosition(100,470);
	Player3->setScale(0.2);

	auto Player4 = Sprite::create("player4.png");
	Player4->setPosition(100,530);
	Player4->setScale(0.2);

	this->addChild(Player1, 0);
	this->addChild(Player2, 0);
	this->addChild(Player3, 0);
	this->addChild(Player4, 0);

	auto Bubble = Sprite::create("bubble.png");
	Bubble->setPosition(200, 410);
	Bubble->setVisible(false);
	this->addChild(Bubble, 2);
	

	auto PlayersListener = EventListenerTouchOneByOne::create();
	auto label = LabelTTF::create("", "Arial", 20);
	label->setColor(Color3B(130,130,150));
	label->setVisible(false);		
	this->addChild(label, 2);
	PlayersListener->onTouchBegan = [=](Touch* touch, Event* e){

		Bubble->setVisible(true);
		Point touchLocation = this->convertTouchToNodeSpace(touch);
		if (Player1->getBoundingBox().containsPoint(touchLocation) )
        {
            CCLog("player1 touched!");
			//auto moveToBubble = MoveTo::create(0.1, Point(200, 410));
			//Bubble->runAction(moveToBubble);
			label->setString("player1: ");
			label->setPosition(210, 420);
			label->setVisible(true);

			Bubble->setPosition(200, 410);
        }
		else if(Player2->getBoundingBox().containsPoint(touchLocation))
		{
			//auto moveToBubble = MoveTo::create(0.1, Point(200, 470));
			//Bubble->runAction(moveToBubble);
			label->setString("player2: ");
			label->setPosition(210, 480);
			label->setVisible(true);
			Bubble->setPosition(200, 470);
		}
		else if(Player3->getBoundingBox().containsPoint(touchLocation))
		{
			//auto moveToBubble = MoveTo::create(0.1, Point(200, 530));
			//Bubble->runAction(moveToBubble);
			label->setString("player3: ");
			label->setPosition(210, 540);
			label->setVisible(true);
			Bubble->setPosition(200, 530);
		}
		else if(Player4->getBoundingBox().containsPoint(touchLocation))
		{
			//auto moveToBubble = MoveTo::create(0.1, Point(200, 590));
			//Bubble->runAction(moveToBubble);
			label->setString("player4: ");
			label->setPosition(210, 600);
			label->setVisible(true);
			Bubble->setPosition(200, 590);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(PlayersListener, 1);

	


	


	//cardBack->setRotation(-45.0);

	//-------------HandCard Listener --------

	auto handCardListener = EventListenerTouchOneByOne::create();
	handCardListener->setSwallowTouches(true);

	handCardListener->onTouchBegan = [=](Touch* touch, Event* e){
		int i, j;
		float card_y =  3.0;
		for(i = cardPosition - 1; i >= 1; i--){
			Rect rect = Rect( i * 30 + 16, card_y, 150, 225);
			if(rect.containsPoint(touch->getLocation())){
				
				auto card = getChildByTag(i);

				log("Card %d %f", i, card->getScale());
				log("x:%f y:%f", card->getPosition().x, card->getPosition().y);
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
	//auto playCardButton = MenuItemLabel::create(Label::create("[Play Card]", "Arial", 20), CC_CALLBACK_1(GameScene::playCard, this));
	auto playCardButton = MenuItemImage::create("play.png", "pplay.png", "play.png", CC_CALLBACK_1(GameScene::playCard, this));
	auto shuffleButton = MenuItemImage::create("shuffle.png", "pshuffle.png", "disabledShuffle.png", CC_CALLBACK_1(GameScene::shuffleCard, this));
	auto passButton = MenuItemImage::create("pass.png", "ppass.png", "pass.png", CC_CALLBACK_1(GameScene::passCard, this));
	auto undoButton = MenuItemImage::create("undo.png", "pundo.png", "undo.png", CC_CALLBACK_1(GameScene::undoCard, this));
	auto quitButton = MenuItemImage::create("quit.png", "pquit.png", "quit.png", CC_CALLBACK_1(GameScene::quitCard, this));
    
	shuffleButton->setAnchorPoint(Point(0,0));
	passButton->setAnchorPoint(Point(0,0));
	undoButton->setAnchorPoint(Point(0,0));
	playCardButton->setAnchorPoint(Point(0,0));
	quitButton->setAnchorPoint(Point(0,0));

	shuffleButton->setPosition(130, 280);
	passButton->setPosition(220, 280);
	undoButton->setPosition(295, 280);
	playCardButton->setPosition(375,280);
	quitButton->setPosition(450, 280);

	shuffleButton->setScale(0.75);
	passButton->setScale(0.75);
	undoButton->setScale(0.75);
	playCardButton->setScale(0.75);
	quitButton->setScale(0.75);

    auto buttons = Menu::create(shuffleButton, passButton, undoButton, playCardButton, quitButton, NULL);



    buttons->setPosition(0,0);
    this->addChild(buttons);

	return true;
}

void GameScene::shuffleCard(Ref* pSend)
{
	log("Shuffle Card Pressed!");
}

void GameScene::passCard(Ref* pSend)
{
	log("Pass Card Pressed!");
}

void GameScene::quitCard(Ref* pSend)
{
	log("Quit Card Pressed!");
}

void GameScene::undoCard(Ref* pSend)
{
	log("Undo Card Pressed!");
	std::vector<Node*> lastHand;
	int i, j, k;
	std::vector<Node*>::iterator iter;

	for(iter = public_deck.begin(); iter != public_deck.end(); ){
		if( (*iter)->getOpacity() > 100){
			lastHand.push_back(*iter);
			iter = public_deck.erase(iter);
		} else {
			iter++;
		}
	}

	for(iter = lastHand.begin(); iter != lastHand.end(); iter++){
		auto moveTo = MoveTo::create(1, Point(cardPosition * 30 + 16, 3.0));
		(*iter)->setTag(cardPosition);
		(*iter)->setZOrder(cardPosition);
		(*iter)->runAction(moveTo);
		cardPosition++;
	}

	log("%d card in last hand, %d card in public deck", lastHand.size(), public_deck.size());
}

void GameScene::playCard(Ref* pSender)
{
    int i, j, k;
    float public_x = 200, public_y = 330;
	float card_y = 3.0;
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
	if (selected.size() == 0 )
		return;

	for(i = 0; i < public_deck.size(); i++){
		public_deck[i]->setOpacity(20);
		public_deck[i]->setZOrder(0);
	}

    for(i = 0; i < selected.size(); i++){
        Node* card = selected[i];
		card->setZOrder(1);
        auto moveTo = MoveTo::create(0.4, Point(public_x, public_y));
        auto scaleTo = ScaleTo::create(0.4, 1.0);
        auto spawn = Spawn::create(moveTo, scaleTo, NULL);
        card->runAction(spawn);
        public_x += 30.0;
		card->setTag(0);

		public_deck.push_back(card);

    }
	for(i = 0; i < remain.size(); i++){
		int position = i + 1;
		Node* card = remain[i];
		auto moveTo = MoveTo::create(0.4, Point(position * 30 + 16.0, card_y));
		card->runAction(moveTo);
		card->setTag(position);
		card->setZOrder(position);
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

