#ifndef CREW_H_
#define CREW_H_

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0

class Crew
{
public:
	static const int JUMP_SPEED = 8;
	static const int FALL_SPEED = 8;

	Crew();

	bool OnTrackRun();

	void handleEvent(SDL_Event& e, Mix_Chunk *gJump);

	void move();

	void render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

private:
	int PosX, PosY;

	int status;
};

#endif // !CHARACTER_H_