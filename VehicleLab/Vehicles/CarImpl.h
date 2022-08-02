#pragma once
#include "VehicleImpl.h"
#include "CarBrand.h"

template <typename Base>
class CarImpl : public VehicleImpl<Base>
{
public:
	using PassengerType = typename Base::PassengerType;

	CarBrand GetCarBrand() const noexcept override;

protected:
	CarImpl(size_t placeCount, CarBrand carBrand);

private:
	CarBrand m_carBrand;
};

template <typename Base>
CarImpl<Base>::CarImpl(size_t placeCount, CarBrand carBrand)
	: VehicleImpl<Base>(placeCount)
	, m_carBrand(carBrand)
{
}

template <typename Base>
CarBrand CarImpl<Base>::GetCarBrand() const noexcept
{
	return m_carBrand;
}