#pragma once
#include <string>

template<typename Base>
class PersonImpl : public Base
{
public:
	std::string GetName() const noexcept final;
	void Speak(const std::string& phrase, std::ostream& os = std::cout) const override;

protected:
	PersonImpl(const std::string& name);

	std::string m_name;
};

template <typename Base>
PersonImpl<Base>::PersonImpl(const std::string& name)
	: m_name(name)
{
}

template <typename Base>
void PersonImpl<Base>::Speak(const std::string& phrase, std::ostream& os) const
{
	os << phrase << std::endl;
}

template<typename Base>
std::string PersonImpl<Base>::GetName() const noexcept
{
	return m_name;
}