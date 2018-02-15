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

		//��ȡ��Ļ��С
		_screenSize = CCDirector::sharedDirector()->getWinSize();

		//������Ϸ����
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
	//������Ϸ����
    CCSprite * bg = CCSprite::create("mainmenu.png");
    bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);
    
	//CCSpriteFrameCache������֡���棩��Ҫ�������CCSpriteFrame����û���ṩ�ر�����ԣ������ṩһϵ�����ڹ���CCSpriteFrame�ķ���
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
	//����logo
    _intro = CCSprite::createWithSpriteFrameName("logo.png");
    _intro->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.7f));
    _gameBatchNode->addChild(_intro, kForeground);
	*/

	
    //add menu
    CCSprite * menuItemOn;
    CCSprite * menuItemOff;
    //�˵�������״̬��ƽʱչʾ�����Ӻ͵��������
    menuItemOn = CCSprite::createWithSpriteFrameName("start2.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("start2.png");
    //New Game �˵�
    CCMenuItemSprite * starGametItem = CCMenuItemSprite::create(
                                                                menuItemOff,
                                                                menuItemOn,
                                                                this,
																//�������Ҫ������˵�����ϵͳ�ĸ�����
                                                                menu_selector(MainMenuSence::chooseLv));
    
    menuItemOn = CCSprite::createWithSpriteFrameName("btn_setting_normal.png");
    menuItemOff = CCSprite::createWithSpriteFrameName("btn_setting_hover.png");
    //How to Play �˵�
    CCMenuItemSprite * howToItem = CCMenuItemSprite::create(
                                                            menuItemOff,
                                                            menuItemOn,
                                                            this,
                                                            menu_selector(MainMenuSence::showTutorial));
    _start = CCMenu::create(starGametItem, NULL);//�����˵�
    //_mainMenu->alignItemsVerticallyWithPadding(50);
    _start->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.3));
    this->addChild(_start, kForeground);

	_setting = CCMenu::create(howToItem, NULL);//�����˵�
    _setting->setPosition(ccp(20, _screenSize.height-20));
    this->addChild(_setting, kForeground);
      
    _tutorialLabel = CCLabelTTF::create("", "Times New Roman", 25);
    _tutorialLabel->setPosition(ccp (_screenSize.width * 0.5f, _screenSize.height * 0.6f) );
    this->addChild(_tutorialLabel, kForeground);
    _tutorialLabel->setVisible(false);
    
}