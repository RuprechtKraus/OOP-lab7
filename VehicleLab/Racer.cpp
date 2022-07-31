#include "Racer.h"

Racer::Racer(const std::string& name, size_t awardsCount)
	: PersonImpl(name)
	, m_awardsCount(awardsCount)
{
}

size_t Racer::GetAwardsCount() const noexcept
{
	return m_awardsCount;
}