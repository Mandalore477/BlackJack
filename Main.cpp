#include <iostream> // input and output
#include "FBlackJackGame.h"
#include <string>
#include "FPlayer.h"
#include "FDealer.h"

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

FBlackJackGame BJGame;


int main()
{

	BJGame.SetGame();
	BJGame.PlayGame();
	
	return 0;
}


