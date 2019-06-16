#include "BJGraphics.h"

BJGraphics::BJGraphics(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer) 
: Sprite(filename, xpos, ypos, width, height, renderer)
{
	/** Create a new Jump action */
	
}

BJGraphics::~BJGraphics()
{
	/** Delete Jump action that was created */
	
}

void BJGraphics::walkLeft()
{
	/** Call animate function with appropriate frames */
	animate(2, 5);

	/** Call move function with appropriate speed */
	//move(-10, 0);
}

void BJGraphics::lookUpLeft()
{
	animate(0, 0);
	setCurrentFrame(0);
}

void BJGraphics::duckLeft()
{
	animate(1, 1);
	setCurrentFrame(1);
}

void BJGraphics::walkRight()
{
	/** Call animate function with appropriate frames */
	animate(6, 9);

	/** Call move function with appropriate speed */
	
	//move(10, 0);
}

void BJGraphics::lookUpRight()
{
	animate(11, 11);
	setCurrentFrame(11);
}

void BJGraphics::duckRight()
{
	animate(10, 10);
	setCurrentFrame(10);
}

void BJGraphics::stop()
{
	/** Check frame Sprite is in to make Sprite face that direction */
	if (getCurrentFrame() < 6)
		/** Set frame to Idle in appropriate direction */
		setCurrentFrame(5);
	else
		/** Set frame to Idle in appropriate direction */
		setCurrentFrame(6);
}

void BJGraphics::startJump()
{
	/** Keep trak of Y position of Sprite */
	jump->start(getYPos());
}

void BJGraphics::updateJump()
{
	/** Update Y position of Sprite */
	jump->update(this);
}


