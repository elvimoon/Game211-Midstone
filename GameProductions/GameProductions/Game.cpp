#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "SpawnerProjectile.h"

using namespace std;

Map* maps;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);
SpawnerProjectile* Game::spawner = new SpawnerProjectile(Game::assets);
bool Game::isRunning = false;
bool onGround = false;

auto& player(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	//add textures for terrain (map), player, and projectile
	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("player", "Assets/player_anims.png");
	assets->AddTexture("projectile", "Assets/proj.png");

	maps = new Map("terrain", 2, 32); //map name, map scale size, tile size 
	maps->LoadMap("Assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(3); //scale the player size
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player"); //set tag as player
	player.addGroup(groupPlayers);


	//this will create projectiles - first set of vector2d sets spawn position, then velocity, range and speed
	assets->CreateProjectile(Vector2D(700, 315), Vector2D(-2, 0), 800, 2, "projectile"); //position of projectile
	assets->CreateProjectile(Vector2D(700, 275), Vector2D(-2, 0), 800, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));


void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	player.getComponent<TransformComponent>().mass = 1.0f;

	manager.refresh();
	manager.update();
	spawner->Update();

	//if statements for spawner collision
	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			cout << "hit player" << endl;
			p->destroy();
		}
	}
}


void Game::render()
{
	SDL_RenderClear(renderer);

	//render map
	for (auto& t : tiles)
	{
		t->draw();
	}
	
	//render player
	for (auto& p : players)
	{
		p->draw();
	}

	//render projectile
	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


