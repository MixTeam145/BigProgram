#include "pch.h"
#include "PEXP.h"

PEXP::PEXP(PoissonDistribution& t_d, int t_sample_size) : PoissonSampleGenerator(t_d, t_sample_size)
{
	generator_type_ = generator_type::PEXP;
}

PEXP& PEXP::operator=(const PEXP& obj)
{
	if (this != &obj)
		PoissonSampleGenerator::operator=(obj);
	return *this;
}

PEXP& PEXP::operator=(PEXP&& obj) noexcept
{
	if (this != &obj)
		PoissonSampleGenerator::operator=(std::move(obj));
	return *this;
}

int PEXP::SimulateOne()
{
	int k{};
	double t{ 1 }, l{ exp(-distribution_.GetParam()) };
	for (; (t *= runif(engine)) >= l; ++k) {}
	return k;
}
