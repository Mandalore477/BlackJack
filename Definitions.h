#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <string>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>
#include "CollisionDetection.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


const int AUDIO_RATE = 44100;
const Uint16 AUDIO_FORMAT = AUDIO_S16;
const int AUDIO_CHANNELS = 2; //stereo
const int AUDIO_BUFFERS = 2048;


#endif