#include "ChooseLV.h"
#include "SimpleAudioEngine.h"
#include "MainMenuSence.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
ChooseLV::ChooseLV(void)
{
}
ChooseLV::~ChooseLV(void)
{
}

CCScene* ChooseLV::scene()
{ 
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        // 'layer' is an autorelease object
        ChooseLV *layer = ChooseLV::create();
        CC_BREAK_IF(! layer);
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool ChooseLV::init()
{        
	if(!CCLayer::init())        
	{        
		return false;        
	}        
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	bg = CCSprite::create("bg3.png");
    bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg,0);
	
	right_bt =CCSprite::create("r_botton.png");
	right_bt->setPosition(ccp(_screenSize.width * 0.9f, _screenSize.height * 0.2f));
	this->addChild(right_bt,0);

	left_bt =CCSprite::create("l_botton.png");
	left_bt->setPosition(ccp(_screenSize.width * 0.1f, _screenSize.height * 0.2f));
	this->addChild(left_bt,0);
	// CCScrollView  
	m_ScrollView = CCCGameScrollView::create();        
	//创建一个scrollview        
	m_ScrollView->setDirection(kCCScrollViewDirectionHorizontal); 
	//设置滚动的方向，目前来说只能横方向和纵方向

	//this,页面的数量,每个页面的尺寸(影响页面间的距离)
	m_ScrollView->createContainer(this, 3, _screenSize);        
	//一般是原点        
	m_ScrollView->setPosition(ccp(0, 0));        
	//视口的尺寸(一般是屏幕的尺寸)        
	m_ScrollView->setViewSize(_screenSize);        
	this->addChild(m_ScrollView);


	return true;
}
//滚动触发
void ChooseLV::scrollViewDidScroll( CCScrollView *view )
{
}
//缩放触发
void ChooseLV::scrollViewDidZoom( CCScrollView *view )
{
}
//初始化每个单独页面,pPage为这个页面的容器,nPage是这个页面的ID
bool ChooseLV::scrollViewInitPage( cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage )
{        
	CCString str;  
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_level.plist","ui_level.png");
	//str.initWithFormat("level%d-img.png", nPage + 1);
	CCSprite *sprite =NULL;
	CCSprite *sprite2 =NULL;
	switch(nPage){
	case 0:
		str.initWithFormat("level1-img.png");
		sprite = CCSprite::createWithSpriteFrameName(str.getCString());
		sprite2= CCSprite::createWithSpriteFrameName("level1-font.png");
		break;
	case 1:
		str.initWithFormat("level2-img.png");
		sprite = CCSprite::createWithSpriteFrameName(str.getCString());
		sprite2= CCSprite::createWithSpriteFrameName("level2-font.png");
		break;
	case 2:
		str.initWithFormat("level3-img.png");
		sprite = CCSprite::createWithSpriteFrameName(str.getCString());
		sprite2= CCSprite::createWithSpriteFrameName("level3-font.png");
		break;
	}
	sprite->setPositionY(40);
	pPage->addChild(sprite);
	sprite2->setPositionY(-90);
	pPage->addChild(sprite2); 
	return true;
}

//每一次滑动后结束的回调,可以在这里处理一些事情
void ChooseLV::scrollViewScrollEnd( cocos2d::CCNode *pPage, int nPage )
{        
	CCLog("Current Page=%d", nPage);
}

//点击某个页面的处理
void  ChooseLV::scrollViewClick( const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage )
{        
	switch(nPage)        
	{ 
	case 0:        
	{        
		//进入游戏主界面
		 CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel1::scene()));        
	}        
	break; case 1:        
	{        
		//滚动到某个页面        
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel2::scene()));        
	}        
	break; case 2:        
	{        
		//设置当前页面        
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel3::scene()));       
	}        
	break;        
	}
}