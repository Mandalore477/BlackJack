#ifndef CARDStruct
#define CARDStruct
#include<string>
#include"Definitions.h"
#include"Sprite.h"
#include"BJGraphics.h"

using FString = std::string;
using int32 = int;

struct Card
{
	int32 value = 0;
	FString suit = " ";
	FString face = " ";
};
#endif
