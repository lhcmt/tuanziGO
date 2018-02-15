#include "MainMenuSence.h"
#include "ChooseLV.h"
using namespace cocos2d;


MainMenuSence::~MainMenuSence(void)
{
}
CCScene* MainMenuSence::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainMenuSence *layer = MainMenuSence::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool MainMenuSence::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		//获取屏幕大小
		_screenSize = CCDirector::sharedDirector()->getWinSize();

		//创建游戏界面
		createGameScreen();

		//listen for touches
		this->setTouchEnabled(true);
		//create main loop
		//this->schedule(schedule_selector(MainMenuSence::update));

        bRet = true;
    } while (0);

    return bRet;
}
void MainMenuSence::showTutorial (CCObject* pSender) {
    _tutorialLabel->setString("Tap the screen to make the player jump.");
    //_intro->setVisible(false);
    _start->setVisible(false);
	_setting->setVisible(false);
    //SimpleAudioEngine::sharedEngine()->playEffect("start.wav");
    _tutorialLabel->setVisible(true);
}

void MainMenuSence::chooseLv(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,ChooseLV::scene()));
}

void MainMenuSence::createGameScreen () {
	//设置游戏背景
    CCSprite * bg = CCSprite::create("mainmenu.png");
    bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
	//CCSpriteFrameCache（精灵帧缓存）主要用来存放CCSpriteFrame，它没有提供特别的属性，而是提供一系列用于管理CCSpriteFrame的方法
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_level.plist","ui_level.png");
    _gameBatchNode = CCSpriteBatchNode::create("ui_level.png", 200);
    this->addChild(_gameBatchNode, kMiddleground);
    /*
    CCSprite * repeat;
    
    _background = CCSprite::createWithSpriteFrameName("background.png");
    _background->setAnchorPoint(ccp(0,0));
    _gameBatchNode->addChild(_background, kBackground);
    
    repeat = CCSprite::createWithSpriteFrameName("background.png");
    repeat->setAnchorPoint(ccp(0,0));
    repeat->setPosition(ccp(repeat->getContentSize().width - 1, 0));
    _background->addChild(repeat, kBackground);
    
    repeat = CCSprite::createWithSpriteFrameName("background.png");
    repeat->setAnchorPoint(ccp(0,0));
    repeat->setPosition(ccp(2 * (repeat->getContentSize().width - 1), 0));
    _background->addChild(repeat, kBackground);
    
 */
	/*
	//加入logo
    _intro = CCSprite::createWithSpriteFrameName("logo.png");
    _intro->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.7f));
    _gameBatchNode->addChild(_intro, kForeground);
	*/

	
    //add menu
    CCSprite * menuItemOn;
    CCSprite * menuItemOff;
    //菜单有两个状态，平时展示的样子和点击的样子
    menuItemOn = CCSprite::createWithSpriteFrameName("start2.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("start2.png");
    //New Game 菜单
    CCMenuItemSprite * starGametItem = CCMenuItemSprite::create(
                                                                menuItemOff,
                                                                menuItemOn,
                                                                this,
																//这个最重要，点击菜单调用系统哪个方法
                                                                menu_selector(MainMenuSence::chooseLv));
    
    menuItemOn = CCSprite::createWithSpriteFrameName("btn_setting_normal.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("btn_setting_hover.png");
    //How to Play 菜单
    CCMenuItemSprite * howToItem = CCMenuItemSprite::create(
                                                            menuItemOff,
                                                            menuItemOn,
                                                            this,
                                                            menu_selector(MainMenuSence::showTutorial));
    _start = CCMenu::create(starGametItem, NULL);//创建菜单
    //_mainMenu->alignItemsVerticallyWithPadding(50);
    _start->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.3));
    this->addChild(_start, kForeground);

	_setting = CCMenu::create(howToItem, NULL);//创建菜单
    _setting->setPosition(ccp(20, _screenSize.height-20));
    this->addChild(_setting, kForeground);
      
    _tutorialLabel = CCLabelTTF::create("", "Times New Roman", 25);
    _tutorialLabel->setPosition(ccp (_screenSize.width * 0.5f, _screenSize.height * 0.6f) );
    this->addChild(_tutorialLabel, kForeground);
    _tutorialLabel->setVisible(false);
    
}