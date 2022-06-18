#pragma once
#include <vector>

template<typename T, typename Less = std::less<>>
bool FindMax(const std::vector<T>& vec, T& maxValue, const Less& less = Less{}) noexcept
{
	if (vec.empty())
	{
		return false;
	}

	typename std::vector<T>::const_iterator maxIt{ vec.cbegin() };

	for (typename std::vector<T>::const_iterator it = ++vec.cbegin(); it < vec.cend(); it++)
	{
		if (less(*maxIt, *it))
		{
			maxIt = it;
		}
	}

	maxValue = *maxIt;

	return true;
}