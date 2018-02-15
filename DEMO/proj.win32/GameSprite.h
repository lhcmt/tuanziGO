/*
    文件名：    GameSprite.h
    描　述：    游戏中定义的一些精灵类
*/
#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"


USING_NS_CC;
enum {
	kBackground,//背景层
	kMiddleground,//中间层
	kForeground //最上层
};
enum {//场景障碍物枚举？？？？？
    kSpritePlayer,
    kSpriteTerrain,
    kSpriteBlock,
    kSpriteChimney,//
    kSpritePuff
};

class GameSprite : public CCSprite {

protected:
	CCSize _screenSize;

public:

	//定义变量，并且直接定义默认的get/set方法
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);

	CC_SYNTHESIZE(float, _width, Width);

	CC_SYNTHESIZE(float, _height, Height);

	CC_SYNTHESIZE(CCPoint, _vector, Vector);

	GameSprite(void);
	~GameSprite(void);

	//内联虚函数，只是一个接口
	inline virtual void place () { this->setPosition(_nextPosition); };

    inline virtual float radius () {
        return _width * 0.5f;
    }
	inline void setSize() {
		_width = this->boundingBox().size.width;
		_height = this->boundingBox().size.height;
	}
};

#endif // __GAMESPRITE_H__