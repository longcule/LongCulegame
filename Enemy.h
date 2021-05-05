#ifndef ENEMY_H_
#define ENEMY_H_

#include "LTexture.h"

#define ENEMY_MAX_HEIGHT 300
#define ENEMY_MIN_HEIGHT 320

#define ENEMY_POSITION_RANGE 250
#define ENEMY1_RANGE 100
#define ENEMY2_RANGE 350
#define ENEMY3_RANGE 500
#define ENEMY4_RANGE 110
#define ENEMY5_RANGE 210
#define ENEMY6_RANGE 310
#define ENEMY7_RANGE 410

class Enemy
{
public:
	Enemy(int _type = 0);

	~Enemy();

	void loadFromFile(std::string path, SDL_Renderer* gRenderer);

	void move(const int& acceleration);//tang toc

	void render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetType();

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int eWidth, eHeight;

	int type;

	SDL_Texture *EnemyTexture;
};

#endif // !ENEMY_H_