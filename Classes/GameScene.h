#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include <vector>
#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void shuffleCard(Ref* pSend);
	void passCard(Ref* pSend);
	void undoCard(Ref* pSend);
	void playCard(Ref* pSend);
	void quitCard(Ref* pSend);	
	void bubbleSetInvisible(float dt);
	void wordSetInvisible(float dt);



	int cardPosition;
	std::vector<Node*> public_deck;
	
	cocos2d::Sprite* Bubble1;
	cocos2d::Sprite* Bubble2;
	cocos2d::Sprite* Bubble3;
	cocos2d::Sprite* Bubble4;

	cocos2d::LabelTTF* PassWord;
	cocos2d::LabelTTF* CMyCardWord;
	cocos2d::LabelTTF* UndoWord;
	cocos2d::LabelTTF* QuitWord;
	


	
};

#endif // __HELLOWORLD_SCENE_H__
