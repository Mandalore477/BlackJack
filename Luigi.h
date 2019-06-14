#ifndef LUIGI_H
#define LUIGI_H

#include "Sprite.h"
#include "Jump.h"

class Luigi:public Sprite
{
public:
	Luigi(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
	~Luigi();

	void walkLeft();
	void lookUpLeft();
	void duckLeft();
	void walkRight();
	void lookUpRight();
	void duckRight();
	void stop();
	void startJump();
	void updateJump();

private:
	Jump* jump;
};

#endif //LUIGI_H
