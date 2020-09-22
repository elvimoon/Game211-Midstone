#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Game.h"
using namespace std;

Game* game = nullptr;

int main(int argc, const char* argv[])
{
	//target framerate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	//game time and how long to run
	Uint32 frameStart;
	int frameTime;


	game = new Game();
	game->init("GameWindow", 800, 640, false); 
	//800,600 is window size, false/true to enable or disable fullscreen

	while (game->running())
	{
		frameStart = SDL_GetTicks(); //will set to how many miliseconds since we've first initialized sdl

		game->handleEvents();
		game->update();
		game->render();

		//will give in miliseconds how long taken from handling events, updating objects and rendering it
		frameTime = SDL_GetTicks() - frameStart;

		//if we dont delay, frames will go super fast, will see character just zoom to the right, limiting frames will make smoother
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}