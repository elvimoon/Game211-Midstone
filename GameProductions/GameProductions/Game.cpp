#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
//#include "SpawnerProjectile.h"

using namespace std;

Map* maps;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);
//SpawnerProjectile* Game::spawner = new SpawnerProjectile(Game::assets);
bool Game::isRunning = false;
bool onGround = false;

auto& player(manager.addEntity());
//auto& label(manager.addEntity());


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

	/*
	if (TTF_Init() == -1)
	{
		cout << "Error : SDL_TTF" << endl;
	}
	*/

	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("player", "Assets/player_anims.png");
	assets->AddTexture("projectile", "Assets/proj.png");

	//assets->AddFont("arial", "Assets/arial.ttf", 16);

	maps = new Map("terrain", 2, 32); //map name, map scale size, tile size 

	//maps->LoadMap("Assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(3); //scale the player size
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player"); //set tag as player
	player.addGroup(groupPlayers);

	//this if for UI labels, still a WIP ignore for now
	//SDL_Color white = { 255, 255, 255, 255 };
	//label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

	//this will create projectiles - first set of vector2d sets spawn position, then velocity, range and speed
	assets->CreateProjectile(Vector2D(700, 200), Vector2D(-2, 0), 800, 2, "projectile"); //position of projectile
	assets->CreateProjectile(Vector2D(700, 160), Vector2D(-2, 0), 800, 2, "projectile");
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
	Vector2D playerVel = player.getComponent<TransformComponent>().velocity;
	Vector2D playerFor = player.getComponent<TransformComponent>().force;


	player.getComponent<TransformComponent>().mass = 1.0f;

	manager.refresh();
	manager.update();

	//player.getComponent<TransformComponent>().ApplyForce(Vector2D(0, 1)); //this would apply constant downwrds force - gravity
	//spawner->Update();
	//if statements for collision
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			cout << "player hit collider" << endl;
			//player.getComponent<TransformComponent>().ApplyForce(Vector2D(0, 5));
			//player.getComponent<TransformComponent>().acceleration.y = 0;
			//player.getComponent<TransformComponent>().ApplyForce(Vector2D(0, -5));
			//player.getComponent<TransformComponent>().ApplyForce(Vector2D(0, 0));
			//player.getComponent<TransformComponent>().position.y = playerPos.y - 3;
		} 

		if (Collision::AABB(cCol, playerCol) && playerFor.x < 0)
		{
			cout << "player hit collider" << endl;
			//player.getComponent<TransformComponent>().ApplyForce(Vector2D(0, 0));
			player.getComponent<TransformComponent>().position.x = playerPos.x + 3;
		}

		if (Collision::AABB(cCol, playerCol) && playerVel.y == 0 && playerVel.x > 0)
		{
			cout << "player hit collider" << endl;
			player.getComponent<TransformComponent>().position.x = playerPos.x - 3;
		}

		//else if (Collision::AABB(cCol, playerCol) && playerVel.x < 0 || playerVel.x > 0)
	//	{
			// << "player hit collider" << endl;
				//playerVel.y = 0;
				//playerVel.x = 0;
				//player.getComponent<TransformComponent>().speed = 0;
				//player.getComponent<TransformComponent>().position = playerPos;
			//	player.getComponent<TransformComponent>().gravity = true;
			//	player.getComponent<TransformComponent>().velocity.x = 0;
				//player.getComponent<TransformComponent>().speed = 3;
				//player.getComponent<TransformComponent>().gravity = true;
	//	}
		
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			cout << "hit player" << endl;
			p->destroy();
		}
	}

	//to keep the camera following player in middle
	camera.x = player.getComponent<TransformComponent>().position.x - 400; //half of screen is 400 as map is 800 x 640
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
	{
		camera.x = 0;
	}

	if (camera.y < 0)
	{
		camera.y = 0;
	}
	
	if (camera.x > camera.w)
	{
		camera.x = camera.w;
	}

	if (camera.y > camera.h)
	{
		camera.y = camera.h;
	}
}


void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	//render out if you dont want to see the collision box
	for (auto& c : colliders)
	{
		c->draw();
	}
	

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	//label.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


