#pragma once
#include "IPoliceMan.h"
#include "PersonImpl.h"

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	PoliceMan(const std::string& name, const std::string& departmentName);

	std::string GetDepartmentName() const noexcept final;

private:
	std::string m_departmentName;
};