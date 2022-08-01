#pragma once
#include "Interfaces/IVehicle.h"
#include <stdexcept>
#include <vector>

template <typename Base>
class VehicleImpl : public Base
{
public:
	using PassengerType = typename Base::PassengerType;

	void AddPassenger(std::shared_ptr<PassengerType> pPassenger) final;
	const PassengerType& GetPassenger(size_t index) const final;
	void RemovePassenger(size_t index) final;
	void RemoveAllPassengers() noexcept final;
	size_t GetPlaceCount() const noexcept final;
	size_t GetPassengerCount() const noexcept final;
	bool IsEmpty() const noexcept final;
	bool IsFull() const noexcept final;

	VehicleImpl(size_t placeCount);

	size_t m_placeCount;
	std::vector<std::shared_ptr<PassengerType>> m_passengers;
};

template <typename Base>
VehicleImpl<Base>::VehicleImpl(size_t placeCount)
	: m_placeCount(placeCount)
{
	try
	{
		m_passengers.reserve(placeCount);
	}
	catch (const std::exception&)
	{
		m_placeCount = 0;
		throw;
	}
}

template <typename Base>
void VehicleImpl<Base>::AddPassenger(std::shared_ptr<typename Base::PassengerType> pPassenger)
{
	if (IsFull())
	{
		throw std::logic_error("No free seats");
	}
	m_passengers.push_back(pPassenger);
}

template <typename Base>
const typename VehicleImpl<Base>::PassengerType&
VehicleImpl<Base>::GetPassenger(size_t index) const
{
	return *m_passengers.at(index);
}

template <typename Base>
void VehicleImpl<Base>::RemovePassenger(size_t index)
{
	if (index >= GetPassengerCount())
	{
		throw std::out_of_range("Index is out of range");
	}

	m_passengers.erase(std::next(m_passengers.begin(), index));
}

template <typename Base>
void VehicleImpl<Base>::RemoveAllPassengers() noexcept
{
	m_passengers.clear();
}

template <typename Base>
size_t VehicleImpl<Base>::GetPlaceCount() const noexcept
{
	return m_placeCount;
}

template <typename Base>
size_t VehicleImpl<Base>::GetPassengerCount() const noexcept
{
	return m_passengers.size();
}

template <typename Base>
bool VehicleImpl<Base>::IsEmpty() const noexcept
{
	return m_passengers.empty();
}

template <typename Base>
bool VehicleImpl<Base>::IsFull() const noexcept
{
	return m_passengers.size() == m_placeCount;
}