#include <iostream> // input and output
#include <string>
#include "Definitions.h"
#include "FBlackJackGame.h"
#include "FPlayer.h"
#include "FDealer.h"
#include "BJGraphics.h"

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

//FBlackJackGame BJGame(renderer, background);

int main(int argc, char** argv)
{
	/** Inialize Game Variables */
	bool game = false;
	bool			done = false;
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;



	/** Initialize Event Variables */
	SDL_Event event;

	/** Initialize timer variables */
	Uint32			deltaT = 75;			// defines delay in time for updating game loop
	Uint32			updatedTime = 0;			// used to determine if frame rate interval has elapsed

	/** Initialize joystick handling variables */


	/** Initialize sprite variables */
	Sprite *background = nullptr;


	

	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cerr << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}
	// Close SDL at program end
	atexit(SDL_Quit);

	/** Create Window for Project */
	window = SDL_CreateWindow("Black Jack Game", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
	{
		cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		return 1;
	}

	/** Create Renderer to draw to */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		return 1;
	}

	/** Initialize sprite properties */
	background = new Sprite("Images/BlackJack_Background.bmp", 0, 0, 705, 530, renderer);


	background->draw();

	/** Update display */
	SDL_RenderPresent(renderer);
	
	FBlackJackGame BJGame(renderer, background);
	//BJGame.PrintIntro();
	BJGame.SetGame();
	BJGame.PlayGame();

	system("pause");

	/** Free memory used for sprites */
	delete background;


	/** Free SDL resources */
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);


	return 0;
}


