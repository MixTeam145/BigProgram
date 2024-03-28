#pragma once
#include "PoissonSampleGenerator.h"

/**
* The PEXP class stores an object of PoissonDistribution class, a sample of random values and provides the
* Poisson Exponential method for the generation of the sample.
*/
class PEXP : public PoissonSampleGenerator
{
public:
	/**
	* Constructs a PEXP object with given PoissonDistribution and an empty sample with given size.
	*
	* @param t_d The PoissonDistribution object.
	* @param t_sample_size The size of the sample.
	*/
	PEXP(PoissonDistribution& t_d, int t_sample_size);

	PEXP(const PEXP& obj) : PoissonSampleGenerator(obj) {}

	PEXP(PEXP&& obj) noexcept : PoissonSampleGenerator(std::move(obj)) {}

	PEXP(const PoissonSampleGenerator* pobj) : PoissonSampleGenerator(*pobj) {}

	PEXP& operator=(const PEXP& obj);

	PEXP& operator=(PEXP&& obj) noexcept;

	/**
	* Generates one random number of the given PoissonDistribution.
	*/
	int SimulateOne() override;
};

