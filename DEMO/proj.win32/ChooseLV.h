#ifndef __RunGame__LEVELCHOOSE__
#define __RunGame__LEVELCHOOSE__
#include "CCGameScrollView.h"        //����ͷ�ļ�
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
	static cocos2d::CCScene* scene();        //���������������̳�        
	//��������        
	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView *view );        
	//���Ŵ���        
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView *view );        
	//��ʼ��ÿ������ҳ��,pPageΪ���ҳ�������,nPage�����ҳ���ID        
	virtual bool scrollViewInitPage( cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage );        
	//���ĳ��ҳ�洦��        
	virtual void scrollViewClick( const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage );        
	//ÿһ�λ���������Ļص�,���������ﴦ��һЩ����        
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