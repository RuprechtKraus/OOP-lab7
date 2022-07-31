#pragma once
#include <string>
#include <iostream>

class IPerson
{
public:
	virtual std::string GetName() const = 0;
	virtual void Speak(const std::string& phrase, std::ostream& os = std::cout) const = 0;
	virtual ~IPerson() = default;
};