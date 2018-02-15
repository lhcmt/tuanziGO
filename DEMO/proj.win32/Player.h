/*
�����࣬
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

//���ǳ�ʼ�ٶ�
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
	kGameStop,//��Ϸ��ͣ
	kGamePlay,//��ʼ��Ϸ
    kGameOver,//��ʼ��Ϸ
    kGameIntro,
	kGameWin
} GameState;

typedef enum
{
	kPlayerMoving,//�������ƶ�
	kPlayerFirstFalling,//�����ڽ���
	kPlayerSecondFalling,
	kPlayerFirstJumping,
	kPlayerSecondJumping,
	kPlayerFlying,
	kPlayerDying,//��������
	kPlayerWin
} PlayerState;  //��Ӧ����_state


//���Ǽ̳�����Ϸ������
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

	//�������������ֱ�Ӷ���Ĭ�ϵ�get/set����
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
	//��������
	void animationControl(void);
	//��������
	void reset (void);
	//��ײ���
	void checkCollision (Block * block);

	//����λ�õ�����ʵ��
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

	//������X���ϵ�λ��[�����Ч��ײ]
	inline int left() {
		return this->getPositionX() - _width * 0.5f;
	}

	//������X���ϵ�λ��[�Ҳ���Ч��ײ]
	inline int right() {
		return this->getPositionX() + _width * 0.5f;
	}

	//������Y���ϵ�λ��
	inline int top() {
		return this->getPositionY() ;
	}

	//������Y���ϵ�λ�á��ײ���Ч��ײ��
	inline int bottom() {
		return this->getPositionY() - _height ;
	}

	//������һ��λ�õ����
	inline int next_left() {
		return _nextPosition.x - _width * 0.5f;
	}

	//������һ��λ�õ��Ҳ�
	inline int next_right() {
		return _nextPosition.x + _width * 0.5f;
	}

	//������һ��λ�õ��ϲ�
	inline int next_top() {
		return _nextPosition.y ;
	}

	//������һ��λ�õĵײ�
	inline int next_bottom() {
		return _nextPosition.y - _height;
	}
};

#endif // __PLAYER_H__

