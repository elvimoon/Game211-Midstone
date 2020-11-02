#ifndef SPAWNERPROJECTILE_H
#define SPAWNERPROJECTILE_H

class SpawnerProjectile {
protected:
	class Randomizer* rng;
	class AssetManager* assets;

	int lanes;
	float laneWidth;
	float offsetTop;
	int delay;
public:
	SpawnerProjectile(AssetManager* _AssetMan);
	~SpawnerProjectile();

	//spawns a set of projectiles according to RNG
	void SpawnProjectile();
	//updates the delay timer, calls SpawnProjectile at timing
	void Update();
};

#endif