#ifndef __LEVEL_1__
#define __LEVEL_1__

#include "cocos2d.h"
#include "Player.h"
#include "Block.h"
#include "RunLevel2.h"
USING_NS_CC;


class RunLevel1 :public cocos2d::CCLayer
{
public:
	
	~RunLevel1(void);
	virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(RunLevel1);
	
public:
	void resetGame();
	void createGameScreen();
	
	void update (float dt);
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	void createMap();
	void restartGame () ;
public:
	
	CCSpriteBatchNode * Level1Node;
	Player * _player;
	CCSize _screenSize;
	CCSprite * _tryAgain;
	CCSprite * _yes;
	CCSprite * _win;
	CCSprite * _next;
	CCSprite * _back;
    CCSprite * _background;
    CCSprite * _foreground;
    GameState _state;
	bool _running;
	CCSprite * bg;
	CCSprite * bg1;
	int bkX;
	Block *BlockArray[1024];
	int BlockIndex;
	int CheckCollision;
	

};

#endif