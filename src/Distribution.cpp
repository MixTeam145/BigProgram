#include "pch.h"
#include "Distribution.h"

void PoissonDistribution::CalculateNStates(double eps)
{
	InitProb();
	double s{ current_probability_ };
	while (1 - s >= eps) {
		NextProb();
		s += current_probability_;
	}
	nstates_ = current_state_ + 1;
}


PoissonDistribution& PoissonDistribution::operator=(PoissonDistribution&& obj) noexcept
{
	param_ = obj.param_;
	current_probability_ = obj.current_probability_;
	current_state_ = obj.current_state_;
	nstates_ = obj.nstates_;
	obj.param_ = 0;
	obj.current_probability_ = 0;
	obj.current_state_ = 0;
	obj.nstates_ = 0;
	return *this;
}


PoissonDistribution::PoissonDistribution(PoissonDistribution&& obj) noexcept
	: param_(obj.param_)
	, nstates_(obj.nstates_)
	, current_probability_(obj.current_probability_)
	, current_state_(obj.current_state_)
{
	obj.param_ = 0;
	obj.current_probability_ = 0;
	obj.current_state_ = 0;
	obj.nstates_ = 0;
}


int PoissonDistribution::GetNStates() {
	if (!nstates_)
		CalculateNStates();
	return nstates_;
}


void PoissonDistribution::InitProb()
{
	current_state_ = 0;
	current_probability_ = exp(-param_);
}


void PoissonDistribution::NextProb()
{
	++current_state_;
	current_probability_ *= param_ / current_state_;
}
