#ifndef RAND_H
#define RAND_H

#include <array>

class RandNum
{
public:
	RandNum();
	void setRange(const int& min, const int& max);
	int generate_rand_num();
	int generate_rand_num(const std::array<int, 3>& arr);

private:
	int m_min;
	int m_max;
};

#endif	// RAND_H