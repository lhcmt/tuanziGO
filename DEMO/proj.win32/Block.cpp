#include "Block.h"


Block::Block(void)
{
}


Block::~Block(void)
{
}

Block * Block::createWithSpriteFrameName(const char *filename)
{
	Block *sprite = new Block();
	if(sprite && sprite->initWithSpriteFrameName((filename)))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}