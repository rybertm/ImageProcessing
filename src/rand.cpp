#include "rand.h"

#include <random>
#include <array>

RandNum::RandNum() : m_min(0), m_max(0)
{
}

void RandNum::setRange(const int& min, const int& max)
{
	m_min = min;
	m_max = max;
}

int RandNum::generate_rand_num()
{
	std::random_device	rd;
	std::mt19937		gen(rd());
	std::uniform_int_distribution<int> distr(m_min, m_max);
	return distr(gen);
}

int RandNum::generate_rand_num(const std::array<int, 3>& arr)
{
	std::random_device	rd;
	std::mt19937		gen(rd());
	std::uniform_int_distribution<int> distr(0, arr.size() - 1);
	return distr(gen);
}
