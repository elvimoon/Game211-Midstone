#include "SpawnerProjectile.h"
#include "Randomizer.h"
#include "AssetManager.h"

SpawnerProjectile::SpawnerProjectile(AssetManager* _AssetMan) {
	assets = _AssetMan;
	rng = new Randomizer(0);

	lanes = 3;
	laneWidth = 200.0f;
	offsetTop = 110.0f;
	delay = 75;
}

SpawnerProjectile::~SpawnerProjectile() {
	if (rng != nullptr) {
		delete rng;
		rng = nullptr;
	}
}

void SpawnerProjectile::SpawnProjectile() {
	float spawnPoint((rng->GetRandomInteger(lanes) * laneWidth) + offsetTop);
	assets->CreateProjectile(Vector2D(800, spawnPoint), Vector2D(-2, 0), 800, 2, "projectile");
	assets->CreateProjectile(Vector2D(800, spawnPoint - 40.0f), Vector2D(-2, 0), 800, 2, "projectile");
}

void SpawnerProjectile::Update() {
	delay--;
	if (delay <= 0) {
		SpawnProjectile();
		delay = 75;
	}
}