#pragma once
#include "IVehicle.h"
#include "CarBrand.h"

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual CarBrand GetCarBrand() const = 0;
};