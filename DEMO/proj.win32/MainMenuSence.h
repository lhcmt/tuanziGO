/*主菜单界面*/
#ifndef __MAINMENUSENCE_H__
#define __MAINMENUSENCE_H__

#include "cocos2d.h"
USING_NS_CC;


class MainMenuSence :public cocos2d::CCLayer
{
public:
	~MainMenuSence(void);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuSence);
	void showTutorial (CCObject* pSender);
    void chooseLv(CCObject* pSender);
	void createGameScreen();
public:
	CCSpriteBatchNode * _gameBatchNode;
    CCLabelTTF * _tutorialLabel;
	//CCSprite * _intro;
	CCSprite * _background;
    CCSprite * _foreground;
	CCMenu* _start;
	CCSize _screenSize;
	CCMenu* _setting;
	
};


#endif