
#include "stdafx.h"
#include "SDL_until.h"
#include "gamebase.h"
#include "LTexture.h"
#include "Crew.h"
#include "Enemy.h"
#include "Button.h"


const std::string LAYER[BACKGROUND_LAYER] = {
	"img/TrackRun/layer01.png",
	"img/TrackRun/layer02.png",
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Color textcolor = { 0, 226, 226 };
TTF_Font* gFont = NULL;
Mix_Music* gMusic = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Chunk* gClick = NULL;
Mix_Chunk* gJump = NULL;
Mix_Chunk* gLose = NULL;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCrewClips[CREW_MATE];
SDL_Rect gEnemyClips[FLYING_FRAMES];
SDL_Rect gEnemyClips1[FLY_SET_FRAMES];
SDL_Rect gEnemyClips4[FLY_STAR3_FRAMES];
SDL_Rect gEnemy2Clips[ENEMY2_FRAMES];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture[BACKGROUND_LAYER];
LTexture gCrewTexture;
LTexture gTrackRunTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

Crew crew;

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("music/musicbkg3.wav");
	if (gMusic == NULL)
	{
		LogError("Failed to load bkg music", MIX_ERROR);
		success = false;
	}
	gMenuMusic = Mix_LoadMUS("music/SneakySnitch_bkg.wav");
	if (gMenuMusic == NULL)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}
	gClick = Mix_LoadWAV("music/mouse_click.wav");
	if (gClick == NULL)
	{
		LogError("Failed to load mouse click music ", MIX_ERROR);
		success = false;
	}
	gJump = Mix_LoadWAV("music/jump_music.wav");
	if (gJump == NULL)
	{
		LogError("Failed to load Jump muisc", MIX_ERROR);
		success = false;
	}
	gLose = Mix_LoadWAV("music/lose_music.wav");
	if (gLose == NULL)
	{
		LogError("Failed to load lose music", MIX_ERROR);
		success = false;
	}
	else
	{
		gFont = TTF_OpenFont("font/Font_game.ttf", 18);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			success = false;
		}
		else
		{
			SDL_Color textcolor = { 255, 255, 255 };
			if (!gText1Texture.loadFromRenderedText("Your score: ", gFont, textcolor, gRenderer))
			{
				std::cout << "Failed to render text1 texture" << std::endl;
				success = false;
			}

			if (!gText2Texture.loadFromRenderedText("High score: ", gFont, textcolor, gRenderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}

			if (!gMenuTexture.loadFromFile("img/TrackRun/Menu.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.loadFromFile("img/TrackRun/huongdan.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.loadFromFile("img/Button/ButtonPlay.png", gRenderer))
			{
				std::cout << " Failed to load Button-Play image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 167.5 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 167.5;
					gPlayButton[i].h = 70;
				}
			}
			if (!gHelpButtonTexture.loadFromFile("img/Button/Howtoplay.png", gRenderer))
			{
				std::cout << "Failed to load Button_Howtoplay image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = 167.5 * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = 167.5;
					gHelpButton[i].h = 70;
				}
			}
			if (!gBackButtonTexture.loadFromFile("img/Button/ButtonBack.png", gRenderer))
			{
				std::cout << "Failed to load Button_Back image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = 134.5 * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = 134.5;
					gBackButton[i].h = 71;
				}
			}
			if (!gExitButtonTexture.loadFromFile("img/Button/ButtonExit.png", gRenderer))
			{
				std::cout << "Failed to load Button-Exit image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = 167.5 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 167.5;
					gExitButton[i].h = 70;
				}
			}
			if (!gPauseButtonTexture.loadFromFile("img/Button/ButtonPause.png", gRenderer))
			{
				std::cout << "Failed to load Button_Pause image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = 14 * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = 14;
					gPauseButton[i].h = 36;
				}
			}
			if (!gContinueButtonTexture.loadFromFile("img/Button/ButtonContinue.png", gRenderer))
			{
				std::cout << "Failed to load Button-Continue image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i].x = 34.5 * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = 34.5;
					gContinueButton[i].h = 39;
				}
			}
			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!gBackgroundTexture[i].loadFromFile(LAYER[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			if (!gTrackRunTexture.loadFromFile("img/TrackRun/TrackRun.png", gRenderer))
			{
				std::cout << "Failed to load OnTrackRun image\n";
				success = false;
			}
			if (!gCrewTexture.loadFromFile("img/crew/crew.png", gRenderer))
			{
				std::cout << "Failed to load sprite sheet texture!\n";
				success = false;
			}
			else
			{

				gCrewClips[0].x = 0;
				gCrewClips[0].y = 0;
				gCrewClips[0].w = 68;
				gCrewClips[0].h = 68;

				//Set top right sprite
				gCrewClips[1].x = 68;
				gCrewClips[1].y = 0;
				gCrewClips[1].w = 68;
				gCrewClips[1].h = 68;

				//Set bottom left sprite
				gCrewClips[2].x = 68 * 2;
				gCrewClips[2].y = 0;
				gCrewClips[2].w = 68;
				gCrewClips[2].h = 68;

				//Set bottom right sprite
				gCrewClips[3].x = 68 * 3;
				gCrewClips[3].y = 0;
				gCrewClips[3].w = 68;
				gCrewClips[3].h = 68;
			}

			if (!gLoseTexture.loadFromFile("img/TrackRun/lose.png", gRenderer))
			{
				std::cout << "Failed to load lose image." << std::endl;
				success = false;
			}
		}
	}
	return success;
}

void Close()
{
	gMenuTexture.free();
	gCrewTexture.free();
	gInstructionTexture.free();
	gTrackRunTexture.free();
	gPlayButtonTexture.free();
	gHelpButtonTexture.free();
	gExitButtonTexture.free();
	gPauseButtonTexture.free();
	gContinueButtonTexture.free();
	gBackButtonTexture.free();
	gLoseTexture.free();
	gText1Texture.free();
	gText2Texture.free();
	gScoreTexture.free();
	gHighScoreTexture.free();

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		gBackgroundTexture[i].free();
	}

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);

	gMusic = NULL;
	gMenuMusic = NULL;
	gClick = NULL;
	gLose = NULL;
	gJump = NULL;


	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;


	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool Quit_Menu = false;
			bool Play_Again = false;

			Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					bool Quit_Game = false;
					handlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);

					handleHelpButton(&e_mouse, gBackButton,
						HelpButton, BackButton,
						gInstructionTexture, gBackButtonTexture,
						gRenderer, Quit_Game, gClick);

					handleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

					if (Quit_Game == true)
					{
						return 0;
					}
				}

				gMenuTexture.render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);
			}

			while (Play_Again)
			{
				srand(time(NULL));
				int time = 0;
				int score = 0;
				int acceleration = 0;
				int frame_Crew = 0;
				int frame_Enemy = 0;
				std::string highscore = GetHighScoreFromFile("high_score.txt");

				SDL_Event e;
				Enemy enemy1(ON_TRACKRUN_ENEMY);
				Enemy enemy2(IN_AIR_ENEMY);
				Enemy enemy3(IN_AIR_1);
				Enemy enemy4(ON_TRACKRUN_ENEMY);
				Enemy enemy6(IN_AIR_1);


				Mix_PlayMusic(gMusic, IS_REPEATITIVE);
				GenerateEnemy(enemy1, enemy2, enemy3, enemy4, enemy6,
					gEnemyClips, gEnemyClips1, gEnemy2Clips, gEnemyClips4, gRenderer);

				int offsetSpeed_TrackRun = BASE_OFFSET_SPEED;
				std::vector <double> offsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

				bool Quit = false;
				bool Game_State = true;
				while (!Quit)
				{
					if (Game_State)
					{
						UpdateGameTimeAndScore(time, acceleration, score);

						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								Quit = true;
								Play_Again = false;
							}

							handlePauseButton(&e, gRenderer, gContinueButton,
								PauseButton, ContinueButton,
								gContinueButtonTexture, Game_State, gClick);

							crew.handleEvent(e, gJump);
						}
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						RenderScrollingBackground(offsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
						RenderScollingTrackRun(offsetSpeed_TrackRun, acceleration, gTrackRunTexture, gRenderer);


						crew.move();
						SDL_Rect* currentClip_Crew = NULL;
						if (crew.OnTrackRun())
						{

							currentClip_Crew = &gCrewClips[frame_Crew / SLOW_FRAME_CHAR];
							crew.render(currentClip_Crew, gRenderer, gCrewTexture);
						}
						else
						{
							currentClip_Crew = &gCrewClips[0];
							crew.render(currentClip_Crew, gRenderer, gCrewTexture);
						}

						enemy1.move(acceleration);
						enemy1.render(gRenderer);

						SDL_Rect* currentClip_Enemy = &gEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
						enemy2.move(acceleration);
						enemy2.render(gRenderer, currentClip_Enemy);

						SDL_Rect* currentClip_Set = &gEnemyClips1[frame_Enemy / SLOW_FRAME_ENEMY];
						enemy3.move(acceleration);
						enemy3.render(gRenderer, currentClip_Set);

						SDL_Rect* currentClip_Enemy2 = &gEnemy2Clips[frame_Enemy / SLOW_FRAME_ENEMY];
						enemy4.move(acceleration);
						enemy4.render(gRenderer, currentClip_Enemy2);

						SDL_Rect* currentClip_Star3 = &gEnemyClips4[frame_Enemy / SLOW_FRAME_ENEMY];
						enemy6.move(acceleration);
						enemy6.render(gRenderer, currentClip_Star3);


						SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
						PauseButton.render(currentClip_Pause, gRenderer, gPauseButtonTexture);


						DrawPlayerScore(gText1Texture, gScoreTexture, textcolor, gRenderer, gFont, score);
						DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textcolor, gRenderer, gFont, highscore);

						if (CheckEnemyColission(crew, enemy1, enemy2, enemy4, currentClip_Crew, currentClip_Enemy, currentClip_Enemy2))
						{
							Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
							UpdateHighScore("high_score.txt", score, highscore);
							Quit = true;
						}
						SDL_RenderPresent(gRenderer);

						ControlCrewFrame(frame_Crew);
						ControlEnemyFrame(frame_Enemy);
					}
				}
				DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again);
				if (!Play_Again)
				{
					enemy1.~Enemy();
					enemy2.~Enemy();
					enemy3.~Enemy();
					enemy4.~Enemy();
					enemy6.~Enemy();
				}
			}
		}
	}
	Close();
	system("pause");
	return 0;
}


