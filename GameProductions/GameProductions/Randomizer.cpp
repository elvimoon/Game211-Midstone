#include "Randomizer.h"
#include <cmath>

Randomizer::Randomizer(unsigned int seed) {
	rngValue = seed;
	rngCount = 0;
}

Randomizer::~Randomizer() {}

void Randomizer::InitializeValue(unsigned int seed) {
	rngValue = seed;
	rngCount = 0;
}

void Randomizer::AdvanceValue() {
	rngValue += (rngValue * rngCount) + (rngCount * rngCount) + 1;
	rngCount++;
}

int Randomizer::GetRandomIntegerRange(int lowerBound, int upperBound)
{
	unsigned int range = static_cast<unsigned int>(upperBound - lowerBound) + 1;
	int result = static_cast<int>(rngValue % range) + lowerBound;
	AdvanceValue();
	return result;
}

int Randomizer::GetRandomInteger(int range)
{
	int result = static_cast<int>(rngValue % range);
	AdvanceValue();
	return result;
}
