#include "GameScene.h"
#include "HelloWorldScene.h"
//#include <afxsock.h>
//#define _AFXDLL

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


void GameScene::bubbleSetInvisible(float dt)
{
	this->Bubble1->setVisible(false);
	this->Bubble2->setVisible(false);
	this->Bubble3->setVisible(false);
	this->Bubble4->setVisible(false);
	

}

void GameScene::wordSetInvisible(float dt)
{
	this->PassWord->setVisible(false);
	this->CMyCardWord->setVisible(false);
	this->UndoWord->setVisible(false);
	this->QuitWord->setVisible(false);
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
			auto moveTo = CCMoveTo::create(0.5, ccp(cardPosition*30, 20));
			selectedCard->runAction(moveTo);
			
			

			CCOrbitCamera * flipYAction = CCOrbitCamera::create(0.5f, 1, 0, 90, -90, 0, 0);
			selectedCard->runAction(flipYAction);
			selectedCard->setTag(cardPosition);
			this->addChild(selectedCard, cardPosition);
			//this->addChild(selectedCard, 1);
			cardPosition++;


		}
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardBackListener, cardBack);
	//------------- BackCard Listener Ended -------

	PassWord = LabelTTF::create("Pass!", "Arial", 20);
	PassWord->setPosition(300, 700);
	PassWord->setVisible(false);
	CMyCardWord = LabelTTF::create("See my cards!", "Arial", 20);
	CMyCardWord->setPosition(300, 700);
	CMyCardWord->setVisible(false);
	UndoWord = LabelTTF::create("Undo...Sorry...!", "Arial", 20);
	UndoWord->setPosition(300, 700);
	UndoWord->setVisible(false);
	QuitWord = LabelTTF::create("Going to quit, bye!", "Arial", 20);
	QuitWord->setPosition(300, 700);
	QuitWord->setVisible(false);
	

	this->addChild(PassWord, 3);
	this->addChild(CMyCardWord, 3);
	this->addChild(UndoWord, 3);
	this->addChild(QuitWord, 3);

	//players and bubbles
	auto Player1 = Sprite::create("player1.png");
	Player1->setPosition(100,410);
	Player1->setScale(0.2);
	//Size playerSize = Player1->getContentSize();
	//CCLog("player size is %d witdh and %d height", playerSize.width, playerSize.height);

	auto Player2 = Sprite::create("player2.png");
	Player2->setPosition(100,470);
	Player2->setScale(0.2);
	//Size playerSize = Player1->getContentSize();
	//CCLog("player size is %d witdh and %d height", playerSize.width, playerSize.height);
	auto Player3 = Sprite::create("player3.png");
	Player3->setPosition(100,530);
	Player3->setScale(0.2);

	auto Player4 = Sprite::create("player4.png");
	Player4->setPosition(100,590);
	Player4->setScale(0.2);

	this->addChild(Player1, 0);
	this->addChild(Player2, 0);
	this->addChild(Player3, 0);
	this->addChild(Player4, 0);
	
	Bubble1 = Sprite::create("Bubble1.png");
	Bubble1->setPosition(300, 690);
	Bubble1->setVisible(false);
	this->addChild(Bubble1, 2);

	Bubble2 = Sprite::create("Bubble2.png");
	Bubble2->setPosition(200, 690);
	Bubble2->setVisible(false);
	this->addChild(Bubble2, 2);

	Bubble3 = Sprite::create("Bubble3.png");
	Bubble3->setPosition(200, 690);
	Bubble3->setVisible(false);
	this->addChild(Bubble3, 2);

	Bubble4 = Sprite::create("Bubble4.png");
	Bubble4->setPosition(200, 690);
	Bubble4->setVisible(false);
	this->addChild(Bubble4, 2);
	

	//cardBack->setRotation(-45.0);

	//-------------HandCard Listener --------

	auto handCardListener = EventListenerTouchOneByOne::create();
	//handCardListener->setSwallowTouches(true);

	handCardListener->onTouchBegan = [=](Touch* touch, Event* e){
		int i, j;
		float card_y =  20.0;
		for(i = cardPosition - 1; i >= 1; i--){
			Rect rect = Rect( i * 30, card_y, 150, 225);
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

	shuffleButton->setPosition(129, 310);
	passButton->setPosition(220, 310);
	undoButton->setPosition(295, 310);
	playCardButton->setPosition(373,310);
	quitButton->setPosition(444, 310);

	shuffleButton->setScale(0.75);
	passButton->setScale(0.75);

	undoButton->setScale(0.75);
	playCardButton->setScale(0.75);
	quitButton->setScale(0.75);

    auto buttons = Menu::create(shuffleButton, passButton, undoButton, playCardButton, quitButton, NULL);



    buttons->setPosition(0,0);
    this->addChild(buttons);


	log("Init GameScene Fnished. card position: %d", cardPosition);
	return true;
}

void GameScene::shuffleCard(Ref* pSend)
{
	log("Shuffle Card Pressed!");
}

void GameScene::passCard(Ref* pSend)
{
	log("Pass Card Pressed!");
	wordSetInvisible(0);
	PassWord->setVisible(true);
	Bubble1->setVisible(true);		
	this->scheduleOnce(schedule_selector(GameScene::bubbleSetInvisible), 2.0f); 
	this->scheduleOnce(schedule_selector(GameScene::wordSetInvisible), 2.0f); 

}

void GameScene::quitCard(Ref* pSend)
{
	log("Quit Card Pressed!");
	wordSetInvisible(0);
	//QuitWord->setVisible(true);
	//Bubble1->setVisible(true);		
	//this->scheduleOnce(schedule_selector(GameScene::wordSetInvisible), 2.0f); 
	//this->scheduleOnce(schedule_selector(GameScene::bubbleSetInvisible), 2.0f); 
	auto helloWordScene = HelloWorld::createScene();
	auto animation = TransitionFlipX::create(1, helloWordScene);
	Director::getInstance()->replaceScene(animation);
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
		auto moveTo = MoveTo::create(0.4, Point(cardPosition * 30, 20.0));
		(*iter)->setTag(cardPosition);
		(*iter)->setZOrder(cardPosition);
		(*iter)->runAction(moveTo);
		cardPosition++;
	}

	log("%d card in last hand, %d card in public deck", lastHand.size(), public_deck.size());
	wordSetInvisible(0);
	UndoWord->setVisible(true);
	Bubble1->setVisible(true);		
	this->scheduleOnce(schedule_selector(GameScene::bubbleSetInvisible), 2.0f); 
	this->scheduleOnce(schedule_selector(GameScene::wordSetInvisible), 2.0f); 
}

void GameScene::playCard(Ref* pSender)
{
    int i, j, k;
    float public_x = 200, public_y = 390;
	float card_y = 20.0;
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
		//card->setZOrder(1);

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
		auto moveTo = MoveTo::create(0.4, Point(position * 30, card_y));
		card->runAction(moveTo);
		card->setTag(position);
		card->setZOrder(position);
	}
	cardPosition = remain.size() + 1;
	wordSetInvisible(0);
	CMyCardWord->setVisible(true);
	Bubble1->setVisible(true);		
	this->scheduleOnce(schedule_selector(GameScene::bubbleSetInvisible), 2.0f); 
	this->scheduleOnce(schedule_selector(GameScene::wordSetInvisible), 2.0f); 

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

