#include <iostream> // input and output
#include <string>
#include "Definitions.h"
#include "FBlackJackGame.h"
#include "FPlayer.h"
#include "FDealer.h"
#include "Luigi.h"

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

FBlackJackGame BJGame;

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
	Sprite *coin = nullptr;
	Luigi *cardSheet = nullptr;
	Sprite *lives = nullptr;
	Sprite *menu = nullptr;
	Sprite *startButton = nullptr;



	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cerr << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}
	// Close SDL at program end
	atexit(SDL_Quit);

	/** Create Window for Project */
	window = SDL_CreateWindow("Luigi's Revenge", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
	background = new Sprite("Images/BlackJack_Background.bmp", 0, 0, 7251, 480, renderer);
	//coin = new Sprite("Images/Coin_Spritesheet.png", 420, 360, 28, 32, renderer);
	cardSheet= new Luigi("Images/CardDeck.png", 320, 365, 32, 64, renderer);
	//lives = new Sprite("Images/Luigi_Spritesheet.png", 10, 10, 32, 64, renderer);
	//menu = new Sprite("Images/Pong_MainMenu.bmp", 0, 0, 640, 480, renderer);
	//startButton = new Sprite("Images/Pong_MenuOp1.bmp", 125, 155, 387, 50, renderer);

	background->draw();
	
	/** Update display */
	SDL_RenderPresent(renderer);
	
	BJGame.PrintIntro();
	BJGame.SetGame();
	BJGame.PlayGame();

	system("pause");

	/** Free memory used for sprites */
	delete background;
	delete coin;
	delete cardSheet;
	delete lives;
	delete menu;
	delete startButton;


	/** Free SDL resources */
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);


	return 0;
}


