#ifndef BJGraphics_H
#define BJGraphics_H

#include "Sprite.h"
#include "Jump.h"

class BJGraphics:public Sprite
{
public:
	BJGraphics(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
	~BJGraphics();

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

#endif //BJGraphics_H
