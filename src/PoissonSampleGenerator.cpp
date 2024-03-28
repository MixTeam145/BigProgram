#include "pch.h"
#include "PoissonSampleGenerator.h"

PoissonSampleGenerator::PoissonSampleGenerator(const PoissonSampleGenerator& obj)
	: distribution_(obj.distribution_)
	, sample_size_(obj.sample_size_)
	, sample_(new int[obj.sample_size_])
	, generator_type_(obj.generator_type_)
{
	for (int i = 0; i < sample_size_; ++i)
		sample_[i] = obj.sample_[i];
}


PoissonSampleGenerator::PoissonSampleGenerator(PoissonSampleGenerator&& obj) noexcept
	: distribution_(std::move(obj.distribution_))
	, sample_size_(obj.sample_size_)
	, generator_type_(obj.generator_type_)
{
	delete[] sample_;
	sample_ = obj.sample_;
	obj.sample_ = nullptr;
	obj.sample_size_ = 0;
	obj.generator_type_ = generator_type::UNDEF;
}


PoissonSampleGenerator& PoissonSampleGenerator::operator=(const PoissonSampleGenerator& obj)
{
	distribution_ = obj.distribution_;
	sample_size_ = obj.sample_size_;
	generator_type_ = obj.generator_type_;
	delete[] sample_;
	sample_ = new int[sample_size_];
	for (int i = 0; i < sample_size_; ++i)
		sample_[i] = obj.sample_[i];
	return *this;
}


PoissonSampleGenerator& PoissonSampleGenerator::operator=(PoissonSampleGenerator&& obj) noexcept
{
	distribution_ = std::move(obj.distribution_);
	sample_size_ = obj.sample_size_;
	generator_type_ = obj.generator_type_;
	delete[] sample_;
	sample_ = obj.sample_;
	obj.sample_size_ = 0;
	obj.sample_ = nullptr;
	obj.generator_type_ = generator_type::UNDEF;
	return *this;
}


void PoissonSampleGenerator::SetSampleSize(int t_sample_size)
{
	if (sample_size_ != t_sample_size) {
		delete[] sample_;
		sample_ = new int[t_sample_size];
		sample_size_ = t_sample_size;
	}
}


void PoissonSampleGenerator::Simulate()
{
	for (int i = 0; i < sample_size_; ++i)
		sample_[i] = SimulateOne();
}
