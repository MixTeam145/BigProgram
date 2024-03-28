#pragma once
#include "PoissonSampleGenerator.h"
#include "Distribution.h"

/**
 * The Chi2Histogram class performs the chi-squared test to calculate the statistic, p-level and the number of degrees of freedom..
 */
class Chi2Histogram
{
public:
	/**
	* Constructs a Chi2Histogram object with given PoissonSampleGenerator and PoissonDistribution.
	* Calculates the expected and observed frequencies.
	* 
	* @param t_g A pointer to an object of either PIS or PEXP class.
	* @param t_d0 A PoissonDistribution of the null hypothesis.
	*/ 
	Chi2Histogram(PoissonSampleGenerator* t_g, PoissonDistribution t_d0);

	Chi2Histogram(const Chi2Histogram& obj);

	Chi2Histogram(Chi2Histogram&& obj) noexcept;

	~Chi2Histogram() { delete[] observed_; delete[] expected_; }

	const int* GetObserved() const { return observed_; }

	const double* GetExpected() const { return expected_; }

	int GetNStates() { return distribution0_.GetNStates(); }

	/**
	* Calculates the expected and observed frequencies.
	* 
	* @param t_g A pointer to an object of either PIS or PEXP class.
	* @param t_d0 PoissonDistribution of the null hypothesis.
	*/
	void SetData(PoissonSampleGenerator* t_g, PoissonDistribution t_d0);

	/**
	* Performes chi-squared test. Calculates the statistic, p-level and the number of degrees of freedom.
	*/
	void Chi2();

	/**
	* A number of degrees of freedom.
	*/ 
	int df;

	/**
	* A chi-squared statistic.
	*/ 
	double chi2stat;

	/**
	* An p-value for the test.
	*/ 
	double plevel;
private:
	/**
	* An observed frequencies.
	*/
	int* observed_;

	/**
	* An expected frequencies under the null hypothesis.
	*/
	double* expected_;

	/**
	* A PoissonSampleGenerator, according to which a sample of random values is generated.
	*/ 
	PoissonSampleGenerator* generator_;

	/**
	* A PoissonDistribution of the null hypothesis
	*/ 
	PoissonDistribution distribution0_;
};

