#ifndef SPRITE_H
#define SPRITE_H

#include "Definitions.h"

class Sprite
{
public:
	Sprite(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
	~Sprite();
	void animate ( Uint16 startFrame, Uint16 endFrame);
	void move (int deltaX, int deltaY);	
	void draw();
	
	void setCurrentFrame( Uint16 frame );
	void setRow( Uint16 row );
	Uint16 getRow();
	Uint16 getCurrentFrame();

	SDL_Texture *getImage();
	int getWidth();
	int getHeight();
	int getXPos();
	int getYPos();
	bool isVisible();

	void setWidth(int width);
	void setHeight(int height);
	void setXPos(int x);
	void setYPos(int y);
	void setVisible(bool visible);

private:
	void load(const char* filename);

	SDL_Texture *image;
	SDL_Rect rect;
	int xpos, ypos;
	bool visible;

	SDL_Renderer *renderer;
};


#endif //SPRITE_H
