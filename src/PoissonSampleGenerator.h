#pragma once
#include "..\BigProgram.h"
#include "Distribution.h"
/**
* The PoissonSampleGenerator abstract class stores an object of PoissonDistribution class and a sample of random values.  
*/
class PoissonSampleGenerator
{
public:
	/**
	* Constructs a PoissonSampleGenerator object with given PoissonDistribution and empty sample with given size.
	* 
	* @param t_d PoissonDistribution object.
	* @param t_sample_size Size of the sample.
	*/ 
	PoissonSampleGenerator(PoissonDistribution t_d, int t_sample_size)
		: distribution_(std::move(t_d))
		, sample_size_(t_sample_size)
		, sample_(new int[t_sample_size])
	{}

	PoissonSampleGenerator(const PoissonSampleGenerator& obj);

	PoissonSampleGenerator(PoissonSampleGenerator&& obj) noexcept;

	PoissonSampleGenerator& operator=(const PoissonSampleGenerator& obj);

	PoissonSampleGenerator& operator=(PoissonSampleGenerator&& obj) noexcept;

	virtual ~PoissonSampleGenerator() { delete[] sample_; }

	int* GetSample() const { return sample_; }

	int GetSampleSize() const { return sample_size_; }

	PoissonDistribution& GetDistribution() { return distribution_; }

	void SetSampleSize(int t_sample_size);

	void SetDistributionParameter(double t_param) { distribution_.SetParam(t_param); }

	/**
	* Generates one random number of the given PoissonDistribution.
	*/ 
	virtual int SimulateOne() = 0;

	/**
	* Generates sample of random numbers of the given of the given PoissonDistribution.
	*/ 
	void Simulate();

	enum class generator_type
	{
		UNDEF,
		PEXP,
		PIS,
	};

	generator_type GetGeneratorType() { return generator_type_; }

protected:
	/*
	* A sample of realizations of a random variable with a given Poisson distribution.
	*/
	int* sample_;

	/**
	* A Size of the sample.
	*/
	int sample_size_;

	/**
	* A type of genetator.
	*/
	generator_type generator_type_{ generator_type::UNDEF };

	/**
	* An object of PoissonDistribution class.
	*/ 
	PoissonDistribution distribution_;
};

