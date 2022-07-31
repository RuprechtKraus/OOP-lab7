#pragma once
#include <functional>
#include <vector>

template <typename T>
bool FindMax(const std::vector<T>& vec, T& maxValue,
	std::function<bool(const T&, const T&)> less = std::less<>{}) noexcept
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