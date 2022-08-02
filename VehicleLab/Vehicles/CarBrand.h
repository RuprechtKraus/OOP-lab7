#pragma once
#include <string>
#include <map>

enum class CarBrand
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INIFINITI
};

constexpr std::string CarBrandToString(CarBrand carBrand)
{
	switch (carBrand)
	{
	case CarBrand::BMW:
		return "BMW";
	case CarBrand::MITSUBISHI:
		return "MITSUBISHI";
	case CarBrand::FORD:
		return "FORD";
	case CarBrand::MERCEDES:
		return "MERCEDES";
	case CarBrand::TOYOTA:
		return "TOYOTA";
	case CarBrand::KIA:
		return "KIA";
	case CarBrand::FERRARI:
		return "FERRARI";
	case CarBrand::PORSCHE:
		return "PORSCHE";
	case CarBrand::LEXUS:
		return "LEXUS";
	case CarBrand::NISSAN:
		return "NISSAN";
	case CarBrand::INIFINITI:
		return "INIFINITI";
	default:
		return "CAR_BRAND_NOT_EXISTS";
	}
}