#include "pch.h"
#include "CppUnitTest.h"
#include "Person.h"
#include "PoliceMan.h"
#include "Racer.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

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
			Assert::AreEqual(static_cast<size_t>(91), p.GetAwardsCount(), L"Awards count are not equal");
		}
	};
}
