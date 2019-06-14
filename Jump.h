#ifndef JUMP_H
#define JUMP_H

#include "Definitions.h"
#include "Sprite.h"

class Jump
{
public:
	Jump();
	void start(int startYPos);
	void update( Sprite * sprite );
	
private:
	bool jumping;
	int deltaY;
	int startYPos;
	int gravity;
};

#endif