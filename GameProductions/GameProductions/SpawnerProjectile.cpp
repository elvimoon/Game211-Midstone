#include "SpawnerProjectile.h"
#include "Randomizer.h"
#include "AssetManager.h"

SpawnerProjectile::SpawnerProjectile(AssetManager* _AssetMan) {
	assets = _AssetMan;
	rng = new Randomizer(0);
}

SpawnerProjectile::~SpawnerProjectile() {
	if (rng != nullptr) {
		delete rng;
		rng = nullptr;
	}
}

void SpawnerProjectile::SpawnProjectile() {
	float spawnPoint((rng->GetRandomInteger(3) * 200.0f) + 20.0f);
	assets->CreateProjectile(Vector2D(800, spawnPoint), Vector2D(-2, 0), 800, 2, "projectile");
	assets->CreateProjectile(Vector2D(800, spawnPoint - 40.0f), Vector2D(-2, 0), 800, 2, "projectile");
}