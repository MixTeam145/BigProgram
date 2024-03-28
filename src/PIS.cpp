#include "pch.h"
#include "PIS.h"

PIS& PIS::operator=(const PIS& obj)
{
	if (this == &obj)
		PoissonSampleGenerator::operator=(obj);
	return *this;
}

PIS& PIS::operator=(PIS&& obj) noexcept
{
	if (this == &obj)
		PoissonSampleGenerator::operator=(std::move(obj));
	return *this;
}

int PIS::SimulateOne()
{
	distribution_.InitProb();
	double s{ distribution_.GetCurrentProb() };
	double a = runif(engine);
	while (a > s) {
		distribution_.NextProb();
		s += distribution_.GetCurrentProb();
	}
	return distribution_.GetCurrentState();
}
