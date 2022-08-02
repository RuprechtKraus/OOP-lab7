#pragma once
#include "CarImpl.h"
#include "ITaxi.h"

class Taxi : public CarImpl<ITaxi>
{
public:
	Taxi(size_t placeCount, CarBrand carBrand);
};