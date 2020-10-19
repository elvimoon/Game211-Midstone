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

	void InitializeValue(unsigned int seed);
	void AdvanceValue();
	
	int GetRandomIntegerRange(int lowerBound, int upperBound);
	int GetRandomInteger(int range);
};

#endif