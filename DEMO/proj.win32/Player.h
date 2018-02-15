/*
主角类，
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

//主角初始速度
#define PLAYER_INITIAL_SPEED 4
//#define PLAYER_JUMP 42
#define PLAYER_JUMP 10
#define GRAVITY 0.6f
#define FLOATNG_GRAVITY 1.0f
#define TERMINAL_VELOCITY 60
#define FLOATING_FRICTION 0.98f
#define AIR_FRICTION 0.99f
#define M_BGM "mbgm.mp3"

#include "cocos2d.h"
#include "GameSprite.h"
#include "Block.h"
#include "SimpleAudioEngine.h"
#include "MainMenuSence.h"

USING_NS_CC;

typedef enum {
	kGameStop,//游戏暂停
	kGamePlay,//开始游戏
    kGameOver,//开始游戏
    kGameIntro,
	kGameWin
} GameState;

typedef enum
{
	kPlayerMoving,//主角在移动
	kPlayerFirstFalling,//主角在降落
	kPlayerSecondFalling,
	kPlayerFirstJumping,
	kPlayerSecondJumping,
	kPlayerFlying,
	kPlayerDying,//主角死亡
	kPlayerWin
} PlayerState;  //对应属性_state


//主角继承于游戏精灵类
class Player : public GameSprite {
    
    CCAction * _runAnimation;
	CCAction * _jumpAnimation;
    CCAction * _floatAnimation;
	CCAction * _fallAnimation;
    float _speed;

	CCSize _screenSize;

	void initPlayer (void);

public:

	Player(void);
	~Player(void);

	//定义变量，并且直接定义默认的get/set方法
	PlayerState _state;
	PlayerState getState()
		{
			return _state;
	}
	void setState(PlayerState state){
		//animationControl();
		_state = state;
	}
	

	static Player * create (void);

	virtual void update (float dt);

	//void setFloating (bool value);
	//动画控制
	void animationControl(void);
	//重置人物
	void reset (void);
	//碰撞检测
	void checkCollision (Block * block);

	//主角位置的真正实现
	inline virtual void place () { 
		this->setPositionY( _nextPosition.y );
		this->setPositionX( _nextPosition.x );
		/*if (_vector.x > 0 && this->getPositionX() < _screenSize.width * 0.2f) {
			this->setPositionX(this->getPositionX() + _vector.x);
			if (this->getPositionX() > _screenSize.width * 0.2f) {
				this->setPositionX(_screenSize.width * 0.2f);
			}
		}*/
	};

	//主角在X轴上的位置[左侧有效碰撞]
	inline int left() {
		return this->getPositionX() - _width * 0.5f;
	}

	//主角在X轴上的位置[右侧有效碰撞]
	inline int right() {
		return this->getPositionX() + _width * 0.5f;
	}

	//主角在Y轴上的位置
	inline int top() {
		return this->getPositionY() ;
	}

	//主角在Y轴上的位置【底部有效碰撞】
	inline int bottom() {
		return this->getPositionY() - _height ;
	}

	//主角下一个位置的左侧
	inline int next_left() {
		return _nextPosition.x - _width * 0.5f;
	}

	//主角下一个位置的右侧
	inline int next_right() {
		return _nextPosition.x + _width * 0.5f;
	}

	//主角下一个位置的上部
	inline int next_top() {
		return _nextPosition.y ;
	}

	//主角下一个位置的底部
	inline int next_bottom() {
		return _nextPosition.y - _height;
	}
};

#endif // __PLAYER_H__

