#pragma once
#include "IPerson.h"
#include "PersonImpl.h"

class Person : public PersonImpl<IPerson>
{
public:
	Person(const std::string& name);
};