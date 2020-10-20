#ifndef SPAWNERPROJECTILE_H
#define SPAWNERPROJECTILE_H

class SpawnerProjectile {
protected:
	class Randomizer* rng;
	class AssetManager* assets;
public:
	SpawnerProjectile(AssetManager* _AssetMan);
	~SpawnerProjectile();

	void SpawnProjectile();
};

#endif