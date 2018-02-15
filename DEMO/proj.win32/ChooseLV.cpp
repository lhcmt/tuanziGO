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
	//����һ��scrollview        
	m_ScrollView->setDirection(kCCScrollViewDirectionHorizontal); 
	//���ù����ķ���Ŀǰ��˵ֻ�᷽ܺ����ݷ���

	//this,ҳ�������,ÿ��ҳ��ĳߴ�(Ӱ��ҳ���ľ���)
	m_ScrollView->createContainer(this, 3, _screenSize);        
	//һ����ԭ��        
	m_ScrollView->setPosition(ccp(0, 0));        
	//�ӿڵĳߴ�(һ������Ļ�ĳߴ�)        
	m_ScrollView->setViewSize(_screenSize);        
	this->addChild(m_ScrollView);


	return true;
}
//��������
void ChooseLV::scrollViewDidScroll( CCScrollView *view )
{
}
//���Ŵ���
void ChooseLV::scrollViewDidZoom( CCScrollView *view )
{
}
//��ʼ��ÿ������ҳ��,pPageΪ���ҳ�������,nPage�����ҳ���ID
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

//ÿһ�λ���������Ļص�,���������ﴦ��һЩ����
void ChooseLV::scrollViewScrollEnd( cocos2d::CCNode *pPage, int nPage )
{        
	CCLog("Current Page=%d", nPage);
}

//���ĳ��ҳ��Ĵ���
void  ChooseLV::scrollViewClick( const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage )
{        
	switch(nPage)        
	{ 
	case 0:        
	{        
		//������Ϸ������
		 CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel1::scene()));        
	}        
	break; case 1:        
	{        
		//������ĳ��ҳ��        
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel2::scene()));        
	}        
	break; case 2:        
	{        
		//���õ�ǰҳ��        
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel3::scene()));       
	}        
	break;        
	}
}