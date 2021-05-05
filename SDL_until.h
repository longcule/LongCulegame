#ifndef SDL_UTILS_H_
#define SDL_UTILS_H_

#include "gamebase.h"
#include "Button.h"
#include "Enemy.h"
#include "Crew.h"

bool Init();
bool LoadMedia();
void Close();

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path,
	const int& score,
	const std::string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer);

void RenderScollingTrackRun(int& speed, const int acceleration, LTexture gTrackRunTexture
	, SDL_Renderer* gRenderer);


void handlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick);

void handleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer* gRenderer,
	bool& Quit_game,
	Mix_Chunk* gClick);

void handleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick);

void handleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State, Mix_Chunk* gClick);

void handlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	Button& PauseButton,
	Button ContinueButton,
	LTexture gContinueButtonTexture,
	bool& game_state,
	Mix_Chunk* gClick);

void GenerateEnemy(Enemy& enemy1, Enemy& enemy2, Enemy& enemy3, Enemy& enemy4, Enemy& enemy6,
	SDL_Rect(&gEnemyClips)[FLYING_FRAMES], SDL_Rect(&gEnemyClips1)[FLY_SET_FRAMES],
	SDL_Rect(&gEnemy2Clips)[ENEMY2_FRAMES],
	SDL_Rect(&gEnemyClips4)[FLY_STAR3_FRAMES], SDL_Renderer* gRenderer);

bool CheckColission(Crew crew,
	SDL_Rect* char_clip,
	Enemy enemy,
	SDL_Rect* enemy_clip = nullptr);

bool CheckEnemyColission(Crew crew,
	Enemy enemy1,
	Enemy enemy2,
	Enemy enemy4,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip = nullptr,
	SDL_Rect* enemy2_clip = nullptr);

void ControlCrewFrame(int& frame);

void ControlEnemyFrame(int& frame);

void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const std::string& HighScore);

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	bool& Play_Again);

#endif // !GAME_UTILS_H_