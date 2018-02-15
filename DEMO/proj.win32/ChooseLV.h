#ifndef __RunGame__LEVELCHOOSE__
#define __RunGame__LEVELCHOOSE__
#include "CCGameScrollView.h"        //导入头文件
#include "cocos2d.h"
#include "RunLevel1.h"
#include "RunLevel2.h"
#include "RunLevel3.h"
USING_NS_CC;
class ChooseLV :public cocos2d::CCLayer, public CCCGameScrollViewDelegate
{
public:
	ChooseLV(void);
	~ChooseLV(void);      
	bool init();        
	static cocos2d::CCScene* scene();        //以下五个方法必须继承        
	//滚动触发        
	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView *view );        
	//缩放触发        
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView *view );        
	//初始化每个单独页面,pPage为这个页面的容器,nPage是这个页面的ID        
	virtual bool scrollViewInitPage( cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage );        
	//点击某个页面处理        
	virtual void scrollViewClick( const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage );        
	//每一次滑动后结束的回调,可以在这里处理一些事情        
	virtual void scrollViewScrollEnd( cocos2d::CCNode *pPage, int nPage );        
	CREATE_FUNC(ChooseLV);
private:        
	CCCGameScrollView *m_ScrollView;
	CCSize _screenSize;
	CCSprite * bg;
	CCSprite *right_bt;
	CCSprite *left_bt;
};

#endif