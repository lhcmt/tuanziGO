/*
    文件名：    Player.h
    描　述：    游戏主角的实现
*/
#include "Player.h"

Player::~Player(){

    CC_SAFE_RELEASE(_runAnimation);
	CC_SAFE_RELEASE(_jumpAnimation);
    CC_SAFE_RELEASE(_floatAnimation);
	CC_SAFE_RELEASE(_fallAnimation);
}

//默认构造函数
Player::Player() {
	_screenSize = CCDirector::sharedDirector()->getWinSize();
	//_floatingTimerMax = 2;
	//_floatingTimer = 0;
	_speed = PLAYER_INITIAL_SPEED;
	_nextPosition = CCPointZero;
	_nextPosition.y = _screenSize.height * 0.4f;
	_state = kPlayerMoving;
}
//创建方法
Player * Player::create () {

	Player * player = new Player();
	if (player && player->initWithSpriteFrameName("player2.png")) {
		player->autorelease();
		player->setSize();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer () {

	//设置锚点
	this->setAnchorPoint(ccp(0.5f, 1.0f));
	this->setPosition(ccp(_screenSize.width * 0.2f, _nextPosition.y));

	_height = 40;
	_width =30;
	//跑动动画
    CCAnimation* animation;

	//创建一个空白的序列帧动画信息
    animation = CCAnimation::create();
	
	//CCSpriteFrame对应的就是帧，将CCSpriteFrame添加到CCAnimation生成动画数据，
	//用CCAnimation生成CCAnimate（就是最终的动画动作），最后可以用CCSprite执行这个动作。
    CCSpriteFrame * frame;
    int i;
	//共有3帧，这里用for循环将对应的序列图加入到动画中
    for(i = 1; i <= 2; i++) {
        char szName[100] = {0};
        sprintf(szName, "walking%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        animation->addSpriteFrame(frame);
		if(2==i)
		frame->setOffset(ccp(0,5));
    }
    
	//设置每两帧间时间间隔
    animation->setDelayPerUnit(0.9f / 3.0f);
	//设置动画结束后是否保留动画帧信息
    animation->setRestoreOriginalFrame(false);
	//设置循环播放次数 (-1:无限循环)
    animation->setLoops(-1);
	//由这个动画信息创建一个序列帧动画
    _runAnimation = CCAnimate::create(animation);
	//保存这个动画
    _runAnimation->retain();

	//跳跃动画
    CCAnimation* animation2;
	animation2 = CCAnimation::create(); 
	CCSpriteFrame * frame2;
	frame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump.png");
	animation2->addSpriteFrame(frame2);
    animation2->setDelayPerUnit(0.9f / 3.0f);
    animation2->setRestoreOriginalFrame(false);
    animation2->setLoops(-1);
    _jumpAnimation = CCAnimate::create(animation2);
    _jumpAnimation->retain();

	//飞行动画
	CCAnimation* animation3;
	animation3 = CCAnimation::create();
	CCSpriteFrame * frame3;
	frame3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("player1.png");
	animation3->addSpriteFrame(frame3);
	frame3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("player3.png");
	animation3->addSpriteFrame(frame3);
	animation3->setDelayPerUnit(0.4f / 3.0f);
    animation3->setRestoreOriginalFrame(false);
    animation3->setLoops(-1);
    _floatAnimation = CCAnimate::create(animation3);
    _floatAnimation->retain();
		
    //下降动画
    CCAnimation* animation4;
	animation4 = CCAnimation::create(); 
	CCSpriteFrame * frame4;
	frame4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("player2.png");
	animation4->addSpriteFrame(frame4);
    animation4->setDelayPerUnit(0.9f / 3.0f);
    animation4->setRestoreOriginalFrame(false);
    animation4->setLoops(-1);
    _fallAnimation = CCAnimate::create(animation4);
    _fallAnimation->retain();

	this->runAction(_runAnimation);
}

void Player::reset () {

	_speed = PLAYER_INITIAL_SPEED;
	_vector = ccp(0,0);
	this->setRotation(0);
	_nextPosition.y = _screenSize.height * 0.25f+10;
	this->setPosition(ccp( _screenSize.width * 0.2f, _nextPosition.y ));
	_state = kPlayerMoving;
	this->stopAllActions();
	this->runAction(_runAnimation);
}
//主角位子更新
void Player::update (float dt) {
	_vector.x = _speed;
	
	switch (_state) {
	case kPlayerMoving:        //移动时如果没有障碍在脚下会下落
		_vector.y -= GRAVITY;
		break;
	case kPlayerFirstJumping:
		_vector.y += PLAYER_JUMP * 0.15f;

		if (_vector.y > PLAYER_JUMP )
			_state = kPlayerFirstFalling;
		break;

	case kPlayerFirstFalling:
		
		_vector.y -= GRAVITY;
		//_vector.x *= AIR_FRICTION;
		break;

	case kPlayerDying:
		_vector.y -= GRAVITY;
		_vector.x = -_speed;
		this->setPositionX(this->getPositionX() + _vector.x);
		break;

	case kPlayerSecondJumping:
		_vector.y += PLAYER_JUMP * 0.15f;
		if (_vector.y > PLAYER_JUMP)
			_state = kPlayerSecondFalling;
		break;

	case kPlayerFlying:
		_vector.y = -FLOATNG_GRAVITY;
		//_vector.x *= FLOATING_FRICTION;
		break;

	case kPlayerSecondFalling:
		_vector.y -= GRAVITY;
		//_vector.x *= AIR_FRICTION;
		break;

	default:
		break;
		}
	if (_vector.y < -TERMINAL_VELOCITY) 
		_vector.y = -TERMINAL_VELOCITY;
	/*if (_vector.x * _vector.x < 0.01) 
		_vector.x = 0;
	if (_vector.y * _vector.y < 0.01) 
		_vector.y = 0;*/
	_nextPosition.y = this->getPositionY() + _vector.y;
	_nextPosition.x = this->getPositionX() + _vector.x;
	/*if (_vector.y < -TERMINAL_VELOCITY) 
	_vector.y = -TERMINAL_VELOCITY;*/
}

void Player::animationControl(void)
{
	this->stopAllActions();
	switch(_state){
	/*case kPlayerMoving:

		this->runAction(_runAnimation);
	break;
	case kPlayerFirstJumping:
	case kPlayerSecondJumping:
	case kPlayerFirstFalling:
	case kPlayerSecondFalling:
	this->runAction(_jumpAnimation);

	break;
	*/
	case kPlayerFlying:
		this->runAction(_floatAnimation);
		break;
	default:
		this->runAction(_runAnimation);
		break;
	}
}

void Player::checkCollision (Block * block)
{
	if(block ==NULL) 
		return;
	if (this->getState() == kPlayerDying) 
		return;
	//当主角在障碍物顶上时
	
	if (this->right() >= block->left() 
		&& this->left() <=  block->right() ) {
	//当障碍物是盘子或桌子时t
		//if(Fork != block->getiType())
			if (this->bottom() >= block->top() && this->next_bottom() <= block->top()
				&& this->top() > block->top()) {
				if(Fork != block->getiType() && Flag != block->getiType()){
					this->setNextPosition(ccp(this->getNextPosition().x, block->top() + this->getHeight()));
					this->setVector ( ccp(this->getVector().x, 0) );
					// Sets the rotation (angle) of the node in degrees
					this->setState(kPlayerMoving);
					//inAir = false;
				}
	//当障碍物是叉子时
				if(Fork == block->getiType())
					this->setState(kPlayerDying);	
				if(Flag == block->getiType())
					this->setState(kPlayerWin);	
		}
	}
	
	//右侧碰撞
			if ((this->bottom() < block->top() && this->top() > block->bottom())) {

				if (this->right() >= block->left() && this->left() < block->left()) 
				if(Flag != block->getiType())
					{
						this->setPositionX(block->left() - this->getWidth() * 0.5f );
						this->setNextPosition(ccp(block->left() - this->getWidth() * 0.5f , this->getNextPosition().y));
						this->setVector (ccp(this->getVector().x * -0.5f, this->getVector().y) );
						//主角装墙上了
						this->setState(kPlayerDying);
						return;
					}
				else
				{
					this->setState(kPlayerWin);	
					return;
				}
		}
	//顶部碰撞
	if (this->right() >= block->left() 
		&& this->left() <=  block->right() ){
	//当障碍物是盘子或桌子时 不会挂
		//if(1 == block->getType() || 2 == block->getType())
			if (this->top() <= block->bottom() && this->next_top() >= block->bottom()
				&& this->bottom() < block->bottom()) {
               this->setNextPosition(ccp(this->getNextPosition().x, block->bottom()));
				this->setVector ( ccp(this->getVector().x, -GRAVITY) );
				this->setState(kPlayerSecondFalling);
			}
	}
	
}