#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int currentRow;
	int topRow = 100;
	int midRow = 200;
	int botRow = 300;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		//Movement Values
		currentRow = 200;
		topRow = 100;
		midRow = 200;
		botRow = 300;
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//Old movement
				//transform->ApplyForce(Vector2D(0, -5));
				//transform->velocity.y = -1;


				//Check for current Row then move Up if player can

				//Currently at topRow
				if (currentRow == topRow) {
					//Cant go up
				}
				//Currently at midRow
				else if (currentRow == midRow) {
					//Go to topRow
					transform->position.y = topRow;
					currentRow = topRow;
				}
				//Currently at botRow
				else {
					//Go to midRow
					transform->position.y = midRow;
					currentRow = midRow;
				}

				sprite->Play("Walk");
				break;

			case SDLK_s:
				//Old Movement
				//transform->ApplyForce(Vector2D(0, 5));
				//transform->velocity.y = 1;


				//Check for current Row then move Down if player can

				//Currently at topRow
				if (currentRow == topRow) {
					//Go to midRow
					transform->position.y = midRow;
					currentRow = midRow;
				}
				//Currently at midRow
				else if (currentRow == midRow) {
					//Go to botRow
					transform->position.y = botRow;
					currentRow = botRow;
				}
				//Currently at botRow
				else {
					//Cant go down
				}




				sprite->Play("Walk");
				break;
			default:
				break;
			}
		}


		//Not sure wether i need to keep this or edit will look later
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{

			case SDLK_w:
				//transform->ApplyForce(Vector2D(0, 0));
				//transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_s:
				transform->ApplyForce(Vector2D(0, 0));
				//transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false; //escape to quit the game
			default:
				break;
			}
		}
	}
};

