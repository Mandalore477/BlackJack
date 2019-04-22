#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct Card
{
	int32 value = 0;
	FString suit = " ";
	FString face = " ";
};
