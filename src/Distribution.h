#pragma once

/**
* The PoissonDistribution class stores the theoretical information about Poisson distribution,
* e.g. the distribution parameter, the last calculated state and the last calculated probability.
*/
class PoissonDistribution
{
public:
	/**
	* Constructs a PoissonDistribution object with given parameter.
	* 
	* @param t_param The distribution parameter.
	*/
	PoissonDistribution(double t_param)
		: param_(t_param)
		, nstates_(0)
		, current_probability_(exp(-param_))
		, current_state_(1)
	{}

	PoissonDistribution(const PoissonDistribution& obj) = default;

	PoissonDistribution(PoissonDistribution&& obj) noexcept;

	PoissonDistribution& operator=(const PoissonDistribution& obj) = default;

	PoissonDistribution& operator=(PoissonDistribution&& obj) noexcept;

	double GetParam() { return param_; }

	int GetNStates();

	double GetCurrentProb() { return current_probability_; }

	int GetCurrentState() { return current_state_; }

	void SetParam(double t_param) { param_ = t_param; }

	/**
	* Sets the initial state and probability.
	*/
	void InitProb();

	/**
	* Calculates the following probability.
	*/
	void NextProb();

	/**
	* Calculates the number of states with a given accuracy.
	* 
	* @param eps The probability of getting in the tail of the distribution.
	*/
	void CalculateNStates(double eps = 1e-5);
	
private:
	/**
	* The distribution parameter.
	*/
	double param_;

	/**
	* The number of states.
	*/
	int nstates_;

	/**
	* The last state for which the probability was calculated.
	*/
	int current_state_;

	/**
	* The last calculated probability.
	*/
	double current_probability_;
};

