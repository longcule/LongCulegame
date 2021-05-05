#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define TRACK_RUN 390
#define MAX_HEIGHT 215

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 1   //tăng tốc 
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define TRACKRUN_SPEED 4
#define ENEMY_SPEED 4
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define IN_AIR_3 12
#define IN_AIR_2 11
#define IN_AIR_1 10
#define ON_TRACKRUN_ENEMY 0

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

const std::string WINDOW_TITLE = "Among Running";

const int SCREEN_WIDTH = 939;
const int SCREEN_HEIGHT = 528;

const double COMMON_BUTTON_WIDTH = 167.5;
const int COMMON_BUTTON_HEIGHT = 70;
const int SMALL_BUTTON_WIDTH = 31;
const int SMALL_BUTTON_HEIGHT = 35;

const int PLAY_BUTON_POSX = 386;
const int PLAY_BUTTON_POSY = 230;
const int HELP_BUTTON_POSX = 386;
const int HELP_BUTTON_POSY = 330;
const int EXIT_BUTTON_POSX = 386;
const int EXIT_BUTTON_POSY = 430;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 28;
const double CONTINUE_BUTTON_POSY = 28.5;

const int TEXT_1_POSX = 750;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 750;
const int TEXT_2_POSY = 50;
const int SCORE_POSX = 880;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 880;
const int HIGH_SCORE_POSY = 50;

const double LAYER_1_SPEED = 4.0;
const double LAYER_2_SPEED = 4.0;

const int CREW_MATE = 4;
const int FLYING_FRAMES = 6;
const int FLY_SET_FRAMES = 5;
const int FLY_STAR1_FRAMES = 3;
const int FLY_STAR2_FRAMES = 8;
const int FLY_STAR3_FRAMES = 7;
const int ENEMY2_FRAMES = 8;
const int BACKGROUND_LAYER = 2;


enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_