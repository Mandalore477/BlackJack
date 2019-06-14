#include "Jump.h"

Jump::Jump()
{
	this->jumping = false;
	this->startYPos = 0;
	this->deltaY = 24;
	this->gravity = 6;
}

void Jump::start(int startYPos)
{
	if(!this->jumping)
	{
		this->jumping = true;
		this->startYPos = startYPos;
		this->deltaY = 24;
	}
}

void Jump::update(Sprite *sprite)
{
	if(this->jumping)
	{
		sprite->setYPos(sprite->getYPos() - this->deltaY);
		this->deltaY -= this->gravity;

		if(sprite->getYPos() > this->startYPos)
		{
			sprite->setYPos(this->startYPos);
			this->jumping = false;
		}
	}
}