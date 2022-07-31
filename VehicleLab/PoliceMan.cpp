#include "PoliceMan.h"

PoliceMan::PoliceMan(const std::string& name, const std::string& departmentName)
	: PersonImpl(name)
	, m_departmentName(departmentName)
{
}

std::string PoliceMan::GetDepartmentName() const noexcept
{
	return m_departmentName;
}