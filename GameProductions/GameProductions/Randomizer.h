#ifndef RANDOMIZER_H
#define RANDOMIZER_H

class Randomizer
{
protected:
	unsigned int rngValue;
	unsigned int rngCount;
public:
	Randomizer(unsigned int seed);
	~Randomizer();

	//goal is to link this randomizer class with projectile spawn, setup where initial loading of game will require input from player of how many lanes they
	//want for endless generator, goal is to have randomzer spawn from 3-lane up to 5-lane via drag-down window user input


	// resets the RNG with the given seed value
	void InitializeValue(unsigned int seed);
	// advances the RNG one step
	void AdvanceValue();
	
	// returns an integer between the two given values, inclusive
	int GetRandomIntegerRange(int lowerBound, int upperBound);
	// returns an integer between 0 (inclusive) and the given value (exclusive)
	int GetRandomInteger(int range);
};

#endif