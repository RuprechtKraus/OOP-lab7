#pragma once
#include "Interfaces/IBus.h"
#include "VehicleImpl.h"

class Bus : public VehicleImpl<IBus>
{
public:
	explicit Bus(size_t placeCount);
};