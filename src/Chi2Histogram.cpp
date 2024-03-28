#include "pch.h"
#include "PROBDIST.H"
#include "Chi2Histogram.h"
#include "PEXP.h"
#include "PIS.h"

Chi2Histogram::Chi2Histogram(PoissonSampleGenerator* t_g, PoissonDistribution t_d0)
	: generator_(t_g)
	, distribution0_(std::move(t_d0))
	, df(0)
	, chi2stat(0)
	, plevel(0)
{
	generator_->Simulate();
	int* sample = generator_->GetSample();
	int nstates = distribution0_.GetNStates();
	int nsample = generator_->GetSampleSize();
	observed_ = new int[nstates] {};
	for (int i = 0; i < nsample; ++i) {
		if (sample[i] > nstates - 1) sample[i] = nstates - 1;
		++observed_[sample[i]];
	}
	expected_ = new double[nstates];
	distribution0_.InitProb();
	expected_[0] = distribution0_.GetCurrentProb() * nsample;
	for (int i = 1; i < nstates; ++i) {
		distribution0_.NextProb();
		expected_[i] = distribution0_.GetCurrentProb() * nsample;
	}
}

Chi2Histogram::Chi2Histogram(const Chi2Histogram& obj)
	: distribution0_(obj.distribution0_)
	, df(obj.df)
	, chi2stat(obj.chi2stat)
	, plevel(obj.plevel)
{
	switch (obj.generator_->GetGeneratorType())
	{
	case PoissonSampleGenerator::generator_type::PEXP:
		generator_ = new PEXP(obj.generator_);
		break;
	case PoissonSampleGenerator::generator_type::PIS:
		generator_ = new PIS(obj.generator_);
		break;
	}
	int nstates = generator_->GetSampleSize();
	observed_ = new int[nstates];
	expected_ = new double[nstates];
	memcpy(observed_, obj.observed_, nstates * sizeof(int));
	memcpy(expected_, obj.expected_, nstates * sizeof(double));
}

Chi2Histogram::Chi2Histogram(Chi2Histogram&& obj) noexcept
	: distribution0_(std::move(obj.distribution0_))
	, df(obj.df)
	, chi2stat(obj.chi2stat)
	, plevel(obj.plevel)
	, observed_(obj.observed_)
	, expected_(obj.expected_)
{
	generator_ = obj.generator_;
	obj.df = 0;
	obj.chi2stat = 0;
	obj.plevel = 0;
	obj.observed_ = nullptr;
	obj.expected_ = nullptr;
	obj.generator_ = nullptr;
}

void Chi2Histogram::SetData(PoissonSampleGenerator* t_g, PoissonDistribution t_d0)
{
	generator_ = t_g;
	distribution0_ = t_d0;
	int* sample = generator_->GetSample();
	int nstates = distribution0_.GetNStates();
	int nsample = generator_->GetSampleSize();
	delete[] observed_;
	observed_ = new int[nstates] {};
	for (int i = 0; i < nsample; ++i) {
		if (sample[i] > nstates - 1) sample[i] = nstates - 1;
		++observed_[sample[i]];
	}
	delete[] expected_;
	expected_ = new double[nstates];
	distribution0_.InitProb();
	expected_[0] = distribution0_.GetCurrentProb() * nsample;
	for (int i = 1; i < nstates; ++i) {
		distribution0_.NextProb();
		expected_[i] = distribution0_.GetCurrentProb() * nsample;
	}
}

void Chi2Histogram::Chi2()
{
	int n = distribution0_.GetNStates();
	double* expected_copy = new double[n];
	int* observed_copy = new int[n];
	memcpy(expected_copy, expected_, n * sizeof(double));
	memcpy(observed_copy, observed_, n * sizeof(int));
	for (int j = 0; j < n - 1; ++j) {
		if (expected_copy[j] < 5) {
			expected_copy[j + 1] += expected_copy[j];
			expected_copy[j] = 0;
			observed_copy[j + 1] += observed_copy[j];
			observed_copy[j] = -1;
		}
	}
	if (expected_copy[n - 1] < 5) {
		int index;
		for (index = n - 2; observed_copy[index] == -1; --index);
		observed_copy[index] += observed_copy[n - 1];
		observed_copy[n - 1] = -1;
		expected_copy[index] += expected_copy[n - 1];
		expected_copy[n - 1] = 0;
	}
	chi2stat = 0;
	df = 0;
	for (int i = 0; i < n; ++i) {
		if (observed_copy[i] != -1) {
			++df;
			double diff = observed_copy[i] - expected_copy[i];
			chi2stat += (diff * diff) / expected_copy[i];
		}
	}
	plevel = 1 - pChi(chi2stat, df - 1);
	delete[] expected_copy;
	delete[] observed_copy;
}
