#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <windows.h>


class AssetManager;
class ColliderComponent;
//class SpawnerProjectile;
using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	
	static SDL_Rect camera;
	static AssetManager* assets;
	//static SpawnerProjectile* spawner;
	enum groupLabels : size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private:
	int cnt = 0;
	SDL_Window* window;
};


