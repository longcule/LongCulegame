
#include "stdafx.h"
#include "SDL_until.h"

std::string GetHighScoreFromFile(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(std::string path,
	const int& score,
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

int UpdateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER], SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER; i++)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].getWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].render(offsetSpeed[i], 0, gRenderer);
		gBackgroundTexture[i].render(offsetSpeed[i] + gBackgroundTexture[i].getWidth(), 0, gRenderer);
	}
}

void RenderScollingTrackRun(int& speed, const int acceleration, LTexture gTrackRunTexture
	, SDL_Renderer* gRenderer)
{
	speed -= TRACKRUN_SPEED + acceleration;
	if (speed < -gTrackRunTexture.getWidth())
	{
		speed = 0;
	}
	gTrackRunTexture.render(speed, 0, gRenderer);
	gTrackRunTexture.render(speed + gTrackRunTexture.getWidth(), 0, gRenderer);
}

void handlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &Quit_game,
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						Close();
					}

					else if (BackButton.IsInside(e, COMMON_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.IsInside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
											ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
											Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
											Mix_ResumeMusic();
											Game_State = true;
											Back_To_Game = true;
				}
					break;
				}
			}
			else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}

			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}

void handlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	Button& PauseButton,
	Button ContinueButton,
	LTexture gContinueButtonTexture,
	bool &Game_State,
	Mix_Chunk *gClick)
{
	if (PauseButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			handleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void GenerateEnemy(Enemy& enemy1, Enemy& enemy2, Enemy& enemy3, Enemy& enemy4, Enemy& enemy6,
	SDL_Rect(&gEnemyClips)[FLYING_FRAMES], SDL_Rect(&gEnemyClips1)[FLY_SET_FRAMES],
	SDL_Rect(&gEnemy2Clips)[ENEMY2_FRAMES],
	SDL_Rect(&gEnemyClips4)[FLY_STAR3_FRAMES], SDL_Renderer* gRenderer)
{
	enemy1.loadFromFile("img/enemy/electric.png", gRenderer);
	enemy2.loadFromFile("img/enemy/fly.png", gRenderer);
	{
		gEnemyClips[0].x = 0;
		gEnemyClips[0].y = 52 * 0;
		gEnemyClips[0].w = 65;
		gEnemyClips[0].h = 52;

		gEnemyClips[1].x = 0;
		gEnemyClips[1].y = 52 * 1;
		gEnemyClips[1].w = 65;
		gEnemyClips[1].h = 52;

		gEnemyClips[2].x = 0;
		gEnemyClips[2].y = 52 * 2;
		gEnemyClips[2].w = 65;
		gEnemyClips[2].h = 52;

		gEnemyClips[3].x = 0;
		gEnemyClips[3].y = 52 * 3;
		gEnemyClips[3].w = 65;
		gEnemyClips[3].h = 52;

		gEnemyClips[4].x = 0;
		gEnemyClips[4].y = 52 * 4;
		gEnemyClips[4].w = 65;
		gEnemyClips[4].h = 52;

		gEnemyClips[5].x = 0;
		gEnemyClips[5].y = 52 * 5;
		gEnemyClips[5].w = 65;
		gEnemyClips[5].h = 52;
	}
	enemy3.loadFromFile("img/TrackRun/set.png", gRenderer);
	{
		gEnemyClips1[0].x = 0;
		gEnemyClips1[0].y = 0;
		gEnemyClips1[0].w = 76;
		gEnemyClips1[0].h = 80;

		gEnemyClips1[1].x = 76;
		gEnemyClips1[1].y = 0;
		gEnemyClips1[1].w = 76;
		gEnemyClips1[1].h = 80;

		gEnemyClips1[2].x = 76 * 2;
		gEnemyClips1[2].y = 0;
		gEnemyClips1[2].w = 76;
		gEnemyClips1[2].h = 80;

		gEnemyClips1[3].x = 76 * 3;
		gEnemyClips1[3].y = 0;
		gEnemyClips1[3].w = 76;
		gEnemyClips1[3].h = 80;

		gEnemyClips1[4].x = 76 * 4;
		gEnemyClips1[4].y = 0;
		gEnemyClips1[4].w = 76;
		gEnemyClips1[4].h = 80;

	}
	enemy4.loadFromFile("img/enemy/enemy2.png", gRenderer);
	{
		gEnemy2Clips[0].x = 0;
		gEnemy2Clips[0].y = 52.125 * 0;
		gEnemy2Clips[0].w = 52;
		gEnemy2Clips[0].h = 50;

		gEnemy2Clips[1].x = 0;
		gEnemy2Clips[1].y = 52.125 * 1;
		gEnemy2Clips[1].w = 52.125;
		gEnemy2Clips[1].h = 50;

		gEnemy2Clips[2].x = 0;
		gEnemy2Clips[2].y = 52.125 * 2;
		gEnemy2Clips[2].w = 52.125;
		gEnemy2Clips[2].h = 50;

		gEnemy2Clips[3].x = 0;
		gEnemy2Clips[3].y = 52.125 * 3;
		gEnemy2Clips[3].w = 52.125;
		gEnemy2Clips[3].h = 50;

		gEnemy2Clips[4].x = 0;
		gEnemy2Clips[4].y = 52.125 * 4;
		gEnemy2Clips[4].w = 52.125;
		gEnemy2Clips[4].h = 50;

		gEnemy2Clips[5].x = 0;
		gEnemy2Clips[5].y = 52.125 * 5;
		gEnemy2Clips[5].w = 52.125;
		gEnemy2Clips[5].h = 50;

		gEnemy2Clips[6].x = 0;
		gEnemy2Clips[6].y = 52.125 * 6;
		gEnemy2Clips[6].w = 52.125;
		gEnemy2Clips[6].h = 50;

		gEnemy2Clips[7].x = 0;
		gEnemy2Clips[7].y = 52.125 * 7;
		gEnemy2Clips[7].w = 52.125;
		gEnemy2Clips[7].h = 50;

	}
	enemy6.loadFromFile("img/TrackRun/star3.png", gRenderer);
	{
		gEnemyClips4[0].x = 0;
		gEnemyClips4[0].y = 0;
		gEnemyClips4[0].w = 92;
		gEnemyClips4[0].h = 83;

		gEnemyClips4[1].x = 92;
		gEnemyClips4[1].y = 0;
		gEnemyClips4[1].w = 92;
		gEnemyClips4[1].h = 83;

		gEnemyClips4[2].x = 92 * 2;
		gEnemyClips4[2].y = 0;
		gEnemyClips4[2].w = 92;
		gEnemyClips4[2].h = 83;

		gEnemyClips4[3].x = 92 * 3;
		gEnemyClips4[3].y = 0;
		gEnemyClips4[3].w = 92;
		gEnemyClips4[3].h = 83;

		gEnemyClips4[4].x = 92 * 4;
		gEnemyClips4[4].y = 0;
		gEnemyClips4[4].w = 92;
		gEnemyClips4[4].h = 83;

		gEnemyClips4[5].x = 92 * 5;
		gEnemyClips4[5].y = 0;
		gEnemyClips4[5].w = 92;
		gEnemyClips4[5].h = 83;

		gEnemyClips4[6].x = 92 * 6;
		gEnemyClips4[6].y = 0;
		gEnemyClips4[6].w = 92;
		gEnemyClips4[6].h = 83;
	}

}

bool CheckColission(Crew crew,
	SDL_Rect* char_clip,
	Enemy enemy,
	SDL_Rect* enemy_clip)// check va cham
{
	bool collide = false; // va cham
	int left_a = crew.GetPosX();
	int right_a = crew.GetPosX() + char_clip->w;
	int top_a = crew.GetPosY();
	int bottom_a = crew.GetPosY() + char_clip->h;

	if (enemy.GetType() == ON_TRACKRUN_ENEMY)
	{
		const int x1 = 25;
		const int x2 = 30;
		int left_b = enemy.GetPosX();
		int right_b = enemy.GetPosX() + enemy.GetWidth();
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy.GetHeight();

		if (right_a - x1 >= left_b && left_a + x1 <= right_b)
		{
			if (bottom_a - x2 >= top_b)
			{
				collide = true;
			}
		}
	}
	else
	{
		const int x1 = 22;
		const int x2 = 18;
		int left_b = enemy.GetPosX() + x1;
		int right_b = enemy.GetPosX() + enemy_clip->w - x1;
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy_clip->h - x2;

		if (right_a >= left_b && left_a <= right_b)
		{
			if (top_a <= bottom_b && top_a >= top_b)
			{
				collide = true;
			}

			if (bottom_a >= bottom_b && bottom_a <= top_b)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool CheckEnemyColission(Crew crew,
	Enemy enemy1,
	Enemy enemy2,
	Enemy enemy4,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip,
	SDL_Rect* enemy2_clip)
{
	if (CheckColission(crew, char_clip, enemy1))
	{
		return true;
	}
	if (CheckColission(crew, char_clip, enemy2, enemy_clip))
	{
		return true;
	}
	if (CheckColission(crew, char_clip, enemy4, enemy2_clip))
	{
		return true;
	}
	return false;
}
void ControlCrewFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= CREW_MATE)
	{
		frame = 0;
	}
}

void ControlEnemyFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
	{
		frame = 0;
	}
}

void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont,
	const int& score)
{
	gTextTexture.render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
	if (gScoreTexture.loadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}

void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const std::string& HighScore)
{
	gTextTexture.render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.loadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e,
	SDL_Renderer *gRenderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			gLoseTexture.render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}
