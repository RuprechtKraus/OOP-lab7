#include "Person.h"
#include "PoliceCar.h"
#include "PoliceMan.h"
#include "Taxi.h"
#include "Racer.h"
#include <format>
#include <iostream>

void SpeakWithName(const IPerson& person, const std::string& phrase, std::ostream& = std::cout);

int main()
{
	Taxi taxi(4, CarBrand::FORD);
	PoliceMan john("John Smith", "North-Carolina Department");
	Person mark("Mark Vagner");

	taxi.AddPassenger(std::make_shared<Person>(mark));
	taxi.AddPassenger(std::make_shared<PoliceMan>(john));

	std::cout << std::format("- Taxi has {} people: {} is a driver and {} is a passenger -",
		taxi.GetPassengerCount(), taxi.GetPassenger(0).GetName(), taxi.GetPassenger(1).GetName());
	std::cout << std::endl;

	Racer michael("Michael Schumacher", 91);
	PoliceMan clark("Clark Tompson", "South-Carolina Department");

	taxi.AddPassenger(std::make_shared<Racer>(michael));
	taxi.AddPassenger(std::make_shared<PoliceMan>(clark));

	std::cout << std::format("- Another two people got into taxi and now taxi has {} people in it -", 
		taxi.GetPassengerCount());
	std::cout << std::endl;

	std::cout << "- Driver was shocked by the number of people in the car -" << std::endl;
	SpeakWithName(mark, "What the heck?! Why there are two cops and legendary Michael Schumacher?!");
	SpeakWithName(michael, "I am just taking a day-off from all this racist.. erm.. racing things.");

	Person claire("Claire Chidowski");

	std::cout << "- A woman appears from the corner and tries to catch the taxi -" << std::endl;

	SpeakWithName(claire, "Wait! I need to get the downtown immediately! Can you pick me up??");
	SpeakWithName(mark, "But the car...");
	SpeakWithName(claire, "No time to talk! I need to hurry!");

	std::cout << std::format("- {} tries to get into the car but... -", claire.GetName());
	std::cout << std::endl;

	try
	{
		taxi.AddPassenger(std::make_shared<Person>(claire));
	}
	catch (const std::logic_error&)
	{
		SpeakWithName(claire, "No room??? YOU PIECE OF SHIT, TAKE ME TO THE DOWNTOWM SCUM");
	}

	std::cout << "- Unhinged woman tries to choke the driver but two policemen pull out their guns -" << std::endl;
	
	SpeakWithName(john, std::format("Calm down lady! I am {} from {} and you are under arrest.", 
		john.GetName(), john.GetDepartmentName()));
	SpeakWithName(claire, "No! It's a mistake!");

	std::cout << std::format("- {} twists her hands behind her back and handcuffs her -", clark.GetName());
	std::cout << std::endl;

	SpeakWithName(michael, "What a show.");

	std::cout << "-- THE END --";
}

void SpeakWithName(const IPerson& person, const std::string& phrase, std::ostream& os)
{
	os << std::format("{}: ", person.GetName());
	person.Speak(phrase, os);
}