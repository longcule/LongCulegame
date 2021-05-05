
#include "stdafx.h"
#include "Crew.h"

Crew::Crew()
{
	//Initialize the offsets
	PosX = SCREEN_WIDTH - 900;
	PosY = TRACK_RUN;

	status = 0;
}
bool Crew::OnTrackRun()
{
	return PosY == TRACK_RUN;
}
void Crew::handleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
						if (OnTrackRun())
						{
							Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
							status = JUMP;
						}
		}
		}
	}
}

void Crew::move()
{
	if (status == JUMP && PosY >= MAX_HEIGHT)
	{
		PosY += -JUMP_SPEED;
	}
	if (PosY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && PosY < TRACK_RUN)
	{
		PosY += FALL_SPEED;
	}

}

void Crew::render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gCrewTexture)
{

	gCrewTexture.render(PosX, PosY, gRenderer, currentClip);
}
int Crew::GetPosX()
{
	return PosX;
}
int Crew::GetPosY()
{
	return PosY;
}
