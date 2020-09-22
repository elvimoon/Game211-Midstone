#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->ApplyForce(Vector2D(0, -5));
				//transform->velocity.y = -1;
				sprite->Play("Walk");
				break;
				
			case SDLK_a:
				transform->ApplyForce(Vector2D(-5, 0));
				//transform->velocity.x = -1;
				sprite->Play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL; //flip or character will end up moonwalking
				break;
			case SDLK_d:
				transform->ApplyForce(Vector2D(5, 0));
				//transform->velocity.x = 1;
				sprite->Play("Walk");
				break;
			case SDLK_s:
				transform->ApplyForce(Vector2D(0, 5));
				//transform->velocity.y = 1;
				sprite->Play("Walk");
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{

			case SDLK_w:
				transform->ApplyForce(Vector2D(0, 0));
				//transform->velocity.y = 0;
				sprite->Play("Idle");
				break;
			case SDLK_a:
				transform->ApplyForce(Vector2D(0, 0));
				//transform->velocity.x = 0;
				sprite->Play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				transform->ApplyForce(Vector2D(0, 0));
				//transform->velocity.x = 0;
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

