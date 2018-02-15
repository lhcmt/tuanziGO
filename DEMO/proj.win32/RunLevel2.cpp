#include "cocos2d.h"
#include "RunLevel2.h"
#include "ChooseLV.h"
using namespace cocos2d;
using namespace CocosDenshion;

///////第二关地形//////////////////////

int bktype2[211] = {table,table,table,table,table,table,table,table,
			table,table,table,table,table,table,table,R,
			nth,nth,nth,nth,nth,nth, 	L,table,fork,fork,fork,	fork,fork,fork,table,R,	nth,nth,nth,nth,nth,nth,
			L,R,nth,nth,nth,table,	nth,nth,nth,nth,nth,L,R,nth,nth,nth,table,nth,nth,nth,

			L,table,fork,fork,fork,fork,	L,table,table,fork,fork,L,hangboard1,hangboard1,hangboard1,
			fork,fork,fork,table,hangboard1,hangboard1,table,fork,fork,	nth,hangboard1,hangboard1,hangboard1,hangboard1,
			fork,nth,fork,nth,L,table,R,	nth,nth,nth,nth,nth,L,R, nth,nth,fork,fork,nth,nth,L,table,R,
			nth,cupboard,cupboard,cupboard,nth,nth,L,table,fork,fork,nth,nth,hangboard1,hangboard1,hangboard1,nth,nth,nth,nth,nth,L,R,

			nth,nth,fork,table,table,table,fork,table,R,nth,nth,nth,nth,L,R,nth,fork,nth,nth,fork,nth,L,table,table,table,fork,fork,
			nth,nth,fork,nth,L,table,table,R, cupboard,cupboard,cupboard,cupboard,cupboard,nth,nth,nth,L,table,table,table,fork,
			nth,nth,nth,nth,L,R,nth,nth,fork,fork,fork,table,table,table,fork,fork,table,table,R,nth,nth,fork,nth,cpbl,cupboard,cpbr,nth,nth,
			cpbl,flag,cpbr
};
int bkheight2[211] ={	1,1,1,1, 1,1,1,1,
						1,1,1,1, 1,1,1,1,
						0,0,0,0,0,0, 	3,3,3,3,3,	3,3,3,3,3,	0,0,0,0,0,0,
						1,1,0,0,0,1,	0,0,0,0,0,1,1,0,0,0,1,0,0,0,

						1,1,1,1,1,1,	2,2,2,2,2, 4,240,241,240,
						4,4,4,4,240,240,4,4,4,	0,200,200,210,200,
						3,0,2,0,1,1,1,	0,0,0,0,0,1,1, 0,0,3,3,0,0,1,1,1,
						0,404,404,414,0,0,2,2,2,2, 0,0,140,140,140,0,0,0,0,0,1,1,

						0,0,3,3,3,3,3,3,3, 0,0,0,0,1,1,0, 2,0,0,3,0,1,1,1,1,1,1,
						0,0,1,0,1,1,1,1, 304,303,300,300,304,0,0,0,1,1,1,1,1,
						0,0,0,0,1,1, 0,0,1,1,1,1,1,1,1,1,1,1,1, 0,0,3,0,2,200,2,0,0,
						4,4,4
};

RunLevel2::~RunLevel2(void)
{
}
CCScene* RunLevel2::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        RunLevel2 *layer = RunLevel2::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool RunLevel2::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
		bkX = 0;
		for(BlockIndex = 0;BlockIndex<1024;BlockIndex++)
			BlockArray[BlockIndex]=NULL;
		BlockIndex = 0;
		//获取屏幕大小
		_screenSize = CCDirector::sharedDirector()->getWinSize();

		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(M_BGM);
		SimpleAudioEngine::sharedEngine()->preloadEffect("jump.wav");
		SimpleAudioEngine::sharedEngine()->preloadEffect("die.wav");
		//创建游戏界面
		createGameScreen();
		
		resetGame();
		_state = kGamePlay;
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(M_BGM, true);
		//listen for touches
		this->setTouchEnabled(true);
		//create main loop
		this->schedule(schedule_selector(RunLevel2::update));

        bRet = true;
    } while (0);

    return bRet;
}
//重新开始游戏
void RunLevel2::resetGame () {

	//初始化配置
    _state = kGameIntro;
	_running = true;
	CheckCollision = 0;
}
void RunLevel2::restartGame () {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel2::scene()));
}


void RunLevel2::createGameScreen () {
	//设置游戏背景
    bg = CCSprite::create("bg2.png");
    bg->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg, kBackground);

	bg1 = CCSprite::create("bg2.png");
	bg1->setPosition(ccp(bg->getContentSize().width+_screenSize.width/2-1, _screenSize.height/2));
	this->addChild(bg1,0);
    
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero_block.plist","hero_block.png");
	Level1Node = CCSpriteBatchNode::create("hero_block.png",200);
	this->addChild(Level1Node,1);
	//CCSpriteFrameCache（精灵帧缓存）主要用来存放CCSpriteFrame，它没有提供特别的属性，而是提供一系列用于管理CCSpriteFrame的方法

	//创建主角类 
	_player = Player::create();
	Level1Node->addChild(_player, 4);
 	//加入重试

	_tryAgain = CCSprite::create("again.png");
    _tryAgain->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _tryAgain->setVisible(false);
    this->addChild(_tryAgain, 3);
	//胜利画面
	_win = CCSprite::create("win.png");
    _win->setPosition(ccp(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _win->setVisible(false);
    this->addChild(_win, 3);
	//确认重试
	_yes = CCSprite::createWithSpriteFrameName("yes.png");
	_yes ->setPosition(ccp(_screenSize.width * 0.8f, _screenSize.height * 0.2f));
    _yes ->setVisible(false);
    this->addChild(_yes, 4);
	//下一关
	_next = CCSprite::createWithSpriteFrameName("next.png");
	_next->setPosition(ccp(_screenSize.width * 0.8f, _screenSize.height * 0.2f));
    _next->setVisible(false);
    this->addChild(_next, 4);
	//返回
	_back = CCSprite::createWithSpriteFrameName("back.png");
	_back->setPosition(ccp(_screenSize.width * 0.2f, _screenSize.height * 0.2f));
    _back->setVisible(false);
    this->addChild(_back, 4);
	createMap();
    
}

void RunLevel2::update(float dt) {
	if (!_running) 
	return;
	//移动背景
	int posX1 = bg->getPositionX();		//移动坐标
	int posX2 = bg1->getPositionX();
	int x = Level1Node->getPositionX();
	if(bkX>_screenSize.width)
	{
		posX1 -= 2;
		posX2 -= 2;
		x -= 4;
	}


	auto mapsize = bg1->getContentSize();

	if(posX1 < (-mapsize.width/2))
	{
		posX2 = mapsize.width/2;
		posX1 = mapsize.width + posX2-1;
	}

	if(posX2 < (-mapsize.width/2))
	{
		posX1 = mapsize.width/2;
		posX2 = mapsize.width + posX1-1;
	}


	bg->setPositionX(posX1);
	bg1->setPositionX(posX2);	//移动结束
	Level1Node->setPositionX(x);		//移动地图

/*	
		//获取主角位置
	if (_player->getPositionY() < -_player->getHeight() ||
		_player->getPositionX() < -_player->getWidth() * 0.5f) {
        if (_state == kGamePlay) {
            
            _running = false;

            //create GAME OVER state           
            _state = kGameOver;
            //_tryAgain->setVisible(true);
        }
    }*/

	if (_player->getPositionY() < -_player->getHeight())
		{
			if (_state == kGamePlay) {
            //_player->reset();   
            //resetGame();
            _running = false;

            //create GAME OVER state           
           _state = kGameOver;
		   SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		   SimpleAudioEngine::sharedEngine()->playEffect("die.wav");
           _tryAgain->setVisible(true);
		   _yes->setVisible(true);
		   _back->setVisible(true);
        }
    }
	//更新主角状态
	_player->update(dt);

	//检查碰撞冲突
	if (_player->getState() != kPlayerDying) 
	{

		for(int i =0; i <= 15;i++)
		{
			_player->checkCollision(BlockArray[i+CheckCollision]);
			
		}
		if(BlockArray[CheckCollision]->right() <= _player->left())
			CheckCollision++;
		if(_player->getState() == kPlayerWin){
			_state = kGameWin;
			_running = false;
			_win->setVisible(true);
			_next->setVisible(true);
			_back->setVisible(true);

		}
		if(354 == CheckCollision)
		{
			_running = false;
			_state = kGameOver;
		   _tryAgain->setVisible(true);
		   _back->setVisible(true);
		}
	}
	//放置主角
	_player->place();
	
	/* //作用是移动整个节点
	if (_player->getNextPosition().y > _screenSize.height * 0.6f) {
		_gameBatchNode->setPositionY( (_screenSize.height * 0.6f - _player->getNextPosition().y) * 0.8f);
	} else {
		_gameBatchNode->setPositionY  ( 0 );
	}*/

}

void RunLevel2::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
	
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
    
    if (touch) {
	    
	    CCPoint tap = touch->getLocation();
        
        switch (_state) {
            
            case kGameIntro:
                break;
			case kGameWin:
				if (_back->boundingBox().containsPoint(tap)) {
					CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,MainMenuSence::scene())); 
                }
				if (_next->boundingBox().containsPoint(tap)) {
					CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,RunLevel3::scene())); 
                }
				break;
            case kGameOver:
                if (_back->boundingBox().containsPoint(tap)) {
					CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,MainMenuSence::scene())); 
                }

				else if (_yes->boundingBox().containsPoint(tap)) {
                  
                    _tryAgain->setVisible(false);
                    _player->reset();
                    resetGame();
					restartGame();
                }
                break;
                
            case kGamePlay:
				if (_player->getState() == kPlayerMoving)
				{
					_player->setState(kPlayerFirstJumping);
					SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");
				}
				if (_player->getState() == kPlayerFirstFalling)
				{
					_player->setState(kPlayerSecondJumping);
					_player->setVector(ccp(PLAYER_INITIAL_SPEED,0));
					SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");
					_player->setVector(ccp(_player->getVector().x,0));
				}
               /* 
                if (_player->getState() == kPlayerFalling) {
                    _player->setFloating ( _player->getFloating() ? false : true );
                
                } else {
                    if (_player->getState() !=  kPlayerDying) {
                        //SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");
                        _player->setJumping(true);
                    }
                }
                */
                //_terrain->activateChimneysAt(_player);
                
                break;
        }
	//_player->animationControl();
    }

}

void RunLevel2::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
	    if (_state == kGamePlay) {
			switch(_player->getState()){
				case kPlayerFirstJumping:
					 _player->setState(kPlayerFirstFalling);
					 break;
				case kPlayerSecondJumping:
					_player->setState(kPlayerSecondFalling);
					break;
				/*case kPlayerFlying:
					_player->setState(kPlayerSecondFalling);
					break;*/
			}
    }
	//_player->animationControl();
}

void RunLevel2::createMap()
{
	//设置障碍物
	int bkindex = 0;
	for(int state=2;bkindex<211;bkindex++)
	{
		Block *temp = NULL;
		int tempSize;
		int i;
		bool isfork=false;
		switch(bktype2[bkindex])
		{
		case nth:						//地图为空不绘制
			bkX += 36;
			break;

		case fork:
			isfork = true;

		case table:
			for(i = 0;i<bkheight2[bkindex]-1;i++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
			}

			temp = NULL;
			temp = Block::createWithSpriteFrameName("bd_m.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

			tempSize = temp->getContentSize().width;

			temp->iType = Table;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,2);

			if(isfork)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX+10,bkheight2[bkindex]*45));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);
				isfork = false;
			}

			bkX += tempSize-1;
			break;

		case R:									//桌子右侧
			for(i = 0;i<bkheight2[bkindex]-1;i++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
			}

			temp = NULL;
			temp =Block::createWithSpriteFrameName("bd_r.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

			temp->iType = TableR;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,2);
			bkX += temp->getContentSize().width;
			break;
		case L:										//桌子左侧
			for(i = 0;i<bkheight2[bkindex]-1;i++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
			}

			temp = NULL;
			temp = Block::createWithSpriteFrameName("bd_l.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX, temp->getContentSize().height*i));

			temp->iType = TableL;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,2);

			bkX += temp->getContentSize().width-1;
			break;
		case hangboard1:
			tempSize = bkheight2[bkindex]/100;								//百位标志hangboard的类型，高度固定

			if(1==tempSize)
			{
				temp = NULL;
				temp =Block::createWithSpriteFrameName("hangboard1.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX, temp->getContentSize().height*3));

				temp->iType = Hangboard1;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);

			}
			if(2==tempSize)
			{
				temp = NULL;
				temp =Block::createWithSpriteFrameName("hangboard3.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,  temp->getContentSize().height*7));

				temp->iType = Hangboard3;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
			}
			tempSize = (bkheight2[bkindex]-tempSize*100)/10;

			for(i =0;i<tempSize-1;i++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,45*i));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);	

				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX+36,45*i));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);	
			}

			i = tempSize;
			tempSize = bkheight2[bkindex]/100;
			tempSize = bkheight2[bkindex] - tempSize*100 - i*10;

			for(int j =0;j<2;j++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_m.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,45*(i-1)));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
				bkX += temp->getContentSize().width-1;
			}

			if(tempSize == 1)
			{
				temp = NULL;
				temp =Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-72+10,i*45));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);
			}
			else
			{
				if(tempSize == 2)
				{
					temp = NULL;
					temp = Block::createWithSpriteFrameName("fork.png");
					temp->setAnchorPoint(ccp(0,0));
					temp->setPosition(ccp(bkX-72+10,i*45));

					temp->iType = Fork;
					BlockArray[BlockIndex]=temp;
					BlockIndex++;
					Level1Node->addChild(temp,1);

					temp = NULL;
					temp =Block::createWithSpriteFrameName("fork.png");
					temp->setAnchorPoint(ccp(0,0));
					temp->setPosition(ccp(bkX-36+10,i*45));

					temp->iType = Fork;
					BlockArray[BlockIndex]=temp;
					BlockIndex++;
					Level1Node->addChild(temp,1);
				}
			}
			break;

		case cupboard:
			tempSize = tempSize = bkheight2[bkindex]/100;

			temp = NULL;
			temp = Block::createWithSpriteFrameName("cpb_m.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX, tempSize*45));

			temp->iType = Cpbm;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,2);

			tempSize = (bkheight2[bkindex]-tempSize*100)/10;

			for(i =0;i<tempSize-1;i++)
			{
				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,temp->getContentSize().height*i));

				temp->iType = Plate;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);

				temp = NULL;
				temp = Block::createWithSpriteFrameName("bd_b.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX+36,temp->getContentSize().height*i));

				temp->iType = Plate;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
			}

			for(i =0 ;i<2;i++)
			{
				temp = NULL;
				temp =Block::createWithSpriteFrameName("bd_m.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX,(tempSize-1)*temp->getContentSize().height));

				temp->iType = Table;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,2);
				bkX += temp->getContentSize().width-1;
			}
			i = tempSize;
			tempSize = bkheight2[bkindex]/100;
			tempSize = bkheight2[bkindex] - tempSize*100 - i*10;

			if(tempSize == 2)
			{
				temp = NULL;
				temp =Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-72+10,i*45));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);

				temp = NULL;
				temp = Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-36+10,i*45));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);
			}
			if(tempSize == 3)
			{
				tempSize = bkheight2[bkindex]/100;
				temp = NULL;
				temp = Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-72+10,tempSize*45+26));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);
			}
			if(tempSize ==4 )
			{
				tempSize = bkheight2[bkindex]/100;
				temp = NULL;
				temp = Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-72+10,tempSize*45+26));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);

				temp = NULL;
				temp =Block::createWithSpriteFrameName("fork.png");
				temp->setAnchorPoint(ccp(0,0));
				temp->setPosition(ccp(bkX-36+10,tempSize*45+26));

				temp->iType = Fork;
				BlockArray[BlockIndex]=temp;
				BlockIndex++;
				Level1Node->addChild(temp,1);
			}
			break;

		case cpbl:
			temp = NULL;
			temp = Block::createWithSpriteFrameName("cpb_l.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,bkheight2[bkindex]*45));

			temp->iType = Cpbl;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,1);
			bkX += temp->getContentSize().width-1;
			break;
		case cpbr:
			temp = NULL;
			temp =Block::createWithSpriteFrameName("cpb_r.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,bkheight2[bkindex]*45));

			temp->iType = Cpbr;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,1);
			bkX += temp->getContentSize().width;
			break;
		case flag:
			temp = NULL;
			temp =Block::createWithSpriteFrameName("cpb_m.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,bkheight2[bkindex]*45));

			temp->iType = Cpbr;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,1);

			temp = Block::createWithSpriteFrameName("flag.png");
			temp->setAnchorPoint(ccp(0,0));
			temp->setPosition(ccp(bkX,bkheight2[bkindex]*45+26));

			temp->iType = Flag;
			BlockArray[BlockIndex]=temp;
			BlockIndex++;
			Level1Node->addChild(temp,1);
			bkX += temp->getContentSize().width-1;
			break;
		default:break;
		}
	}

}