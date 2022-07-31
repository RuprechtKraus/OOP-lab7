#pragma once
#include "IRacer.h"
#include "PersonImpl.h"

class Racer : public PersonImpl<IRacer>
{
public:
	Racer(const std::string& name, size_t awardsCount = 0);

	size_t GetAwardsCount() const noexcept final;

private:
	size_t m_awardsCount;
};