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