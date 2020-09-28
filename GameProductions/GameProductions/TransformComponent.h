#pragma once
#include "Components.h"
#include "Vector2D.h"

struct TransformComponent : public Component
{

public:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D force;

	int height = 32;
	int width = 32;
	int scale = 1;
	float mass;

	TransformComponent()
	{
		mass = 1.0f;
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.x = 101; //player spawn
		position.y = 150;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x + 0.5 * acceleration.x;
		position.y += velocity.y + 0.5 * acceleration.y;
	}

	void ApplyForce(Vector2D force)
	{
		acceleration.x = force.x / mass;
		acceleration.y = force.y / mass;
	}
};