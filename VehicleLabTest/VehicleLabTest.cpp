#include "pch.h"
#include "CppUnitTest.h"
#include "Person.h"
#include "PoliceMan.h"
#include "Racer.h"
#include "Bus.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

using iPersonPtr = std::shared_ptr<IPerson>;

const std::vector<iPersonPtr> TEST_PERSONS{
	std::make_shared<Person>("Mark Vagner"),
	std::make_shared<Person>("Venera Vagner")
};

void VerifyVehicle(
	const IBasicVehicle& vehicle, 
	size_t expectedPlaceCount, 
	size_t expectedPassengerCount,
	bool expectedToBeEmpty,
	bool expectedToBeFull)
{
	Assert::AreEqual(expectedPlaceCount, vehicle.GetPlaceCount(),
		L"Place count is incorrect");
	Assert::AreEqual(expectedPassengerCount, vehicle.GetPassengerCount(), 
		L"Passenger count is incorrect");
	Assert::AreEqual(expectedToBeEmpty, vehicle.IsEmpty());
	Assert::AreEqual(expectedToBeFull, vehicle.IsFull());
}

Bus CreateBus(size_t placesCount, size_t peopleCount, const std::vector<iPersonPtr>& passengers)
{
	Bus b(placesCount);
	for (int i = 0; i < placesCount && i < peopleCount; i++)
	{
		b.AddPassenger(passengers[i]);
	}
	return b;
}

namespace VehicleLabTest
{
	TEST_CLASS(PersonTest)
	{
	public:
		
		TEST_METHOD(TestGetName)
		{
			Person p("Mark Vagner");
			Assert::AreEqual("Mark Vagner"s, p.GetName(), L"Names are not equal");
		}

		TEST_METHOD(TestSpeak)
		{
			Person p("Mark Vagner");
			std::ostringstream ss;
			p.Speak("Hello! My name is "s + p.GetName(), ss);
			Assert::AreEqual("Hello! My name is Mark Vagner\n"s, ss.str(), L"Spoken phrases are not equal");
		}
	};

	TEST_CLASS(PoliceManTest) 
	{
	public:

		TEST_METHOD(TestGetDepartmentName)
		{
			PoliceMan p("John Smith", "North-West police department");
			Assert::AreEqual("North-West police department"s, p.GetDepartmentName(), 
				L"Department names are not equal");
		}
	};

	TEST_CLASS(RacerTest)
	{
	public:

		TEST_METHOD(TestGetAwardsCount)
		{
			Racer p("Michael Schumacher", 91);
			Assert::AreEqual(size_t{ 91 }, p.GetAwardsCount(), L"Awards count are not equal");
		}
	};

	TEST_CLASS(BusTest) 
	{
	public:

		TEST_METHOD(TestEmptyBusProperties)
		{
			Bus b(50);
			VerifyVehicle(b, 50, 0, true, false);
		}

		TEST_METHOD(TestBusPropertiesWithOnePassenger)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			VerifyVehicle(b, 50, 1, false, false);
		}

		TEST_METHOD(TestFullBusProperties)
		{
			Bus b = CreateBus(2, 2, TEST_PERSONS);
			VerifyVehicle(b, 2, 2, false, true);
		}

		TEST_METHOD(TestAddPassengerToFullBus)
		{
			Bus b = CreateBus(1, 1, TEST_PERSONS);
			auto addPassenger = [&]() { b.AddPassenger(std::make_shared<Person>("Venera Vagner")); };
			Assert::ExpectException<std::logic_error>(addPassenger, 
				L"Cannot add passenger to a full bus");
		}

		TEST_METHOD(TestGetPassenger)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			const IPerson& p = b.GetPassenger(0);
			Assert::AreEqual("Mark Vagner"s, p.GetName(), 
				L"Name of bus passenger is incorrect");
		}

		TEST_METHOD(TestGetPassengerWithWrongIndex)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			auto getPassenger = [&]() { b.GetPassenger(10); };
			Assert::ExpectException<std::out_of_range>(getPassenger, 
				L"Cannot get passenger with wrong index");
		}

		TEST_METHOD(TestRemovePassenger)
		{
			Bus b = CreateBus(50, 2, TEST_PERSONS);
			b.RemovePassenger(1);
			VerifyVehicle(b, 50, 1, false, false);
		}

		TEST_METHOD(TestRemoveSinglePassenger)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			b.RemovePassenger(0);
			VerifyVehicle(b, 50, 0, true, false);
		}

		TEST_METHOD(TestRemovePassengerWithWrongIndex)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			auto removePassenger = [&]() { b.RemovePassenger(2); };
			Assert::ExpectException<std::out_of_range>(removePassenger, 
				L"Cannot remove passenger with wrong index");
		}

		TEST_METHOD(TestRemovePassengerWithLastPassengerIndex)
		{
			Bus b = CreateBus(50, 1, TEST_PERSONS);
			auto removePassenger = [&]() { b.RemovePassenger(1); };
			Assert::ExpectException<std::out_of_range>(removePassenger,
				L"Cannot remove passenger with wrong index");
		}

		TEST_METHOD(TestRemoveAllPassengers)
		{
			Bus b = CreateBus(50, 2, TEST_PERSONS);
			b.RemoveAllPassengers();
			VerifyVehicle(b, 50, 0, true, false);
		}

		TEST_METHOD(TestRemoveAllPassengersFromEmptyBus)
		{
			Bus b(50);
			b.RemoveAllPassengers();
			VerifyVehicle(b, 50, 0, true, false);
		}
	};
}