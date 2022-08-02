#pragma once
#include "CarImpl.h"
#include "IPoliceCar.h"

class PoliceCar : public CarImpl<IPoliceCar>
{
public:
	PoliceCar(size_t placeCount, CarBrand carBrand);
};