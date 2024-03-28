#pragma once
#include "PoissonSampleGenerator.h"

/**
* The PIS class stores an object of PoissonDistribution class, a sample of random values and provides the
* Poisson Inverse Sequential method for the generation of the sample.
*/ 
class PIS : public PoissonSampleGenerator
{
public:
	/**
	* Constructs a PIS object with given PoissonDistribution and an empty sample with given size.
	*
	* @param t_d The PoissonDistribution object.
	* @param t_sample_size The size of the sample.
	*/
	PIS(PoissonDistribution& t_d, int t_sample_size) : PoissonSampleGenerator(t_d, t_sample_size) {};

	PIS(const PIS& obj) : PoissonSampleGenerator(obj) {}

	PIS(PIS&& obj) noexcept : PoissonSampleGenerator(std::move(obj)) {}

	PIS(const PoissonSampleGenerator* pobj) : PoissonSampleGenerator(*pobj) {}

	PIS& operator=(const PIS& obj);

	PIS& operator=(PIS&& obj) noexcept;

	/**
	* Generates one random number of the given PoissonDistribution.
	*/
	int SimulateOne() override;
};

