#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__



#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

enum {table,
	fork,
	nth,
	plate,
	R,L,
	forkOnPlate,
	hangboard1,
	hangboard2,
	cupboard,
	cpbl,
	cpbr,
	flag
};
enum{
	Fork,
	Table,
	TableL,
	TableR,
	Plate,
	Hangboard1, //
	Hangboard2, //
	Hangboard3,
	Cpbm,//×ØÉ«Ìõ×Ó
	Cpbl, //×ó
	Cpbr,  //ÓÒ
	Flag
};
class Block : public GameSprite
{
public:
	Block(void);
	~Block(void);
	CC_SYNTHESIZE(int, _type, Type);
	int iType;

	int getiType(){return iType;}

	static Block * Block ::createWithSpriteFrameName(const char *filename);

	inline virtual int left() {
		return this->getPositionX();
	}

	inline virtual int right() {
		return this->getPositionX() + this->getContentSize().width;
	}

	inline virtual int top() {
		return this->getContentSize().height + this->getPositionY();
	}

	inline virtual int bottom() {
		return this->getPositionY();
	}

};

#endif