#pragma once
#include "CarBrand.h"
#include <string>
#include <map>

const std::map<CarBrand, std::string> CAR_BRAND_STRING{
	{ CarBrand::BMW, "BMW" },
	{ CarBrand::MITSUBISHI, "MITSUBISHI" },
	{ CarBrand::FORD, "FORD" },
	{ CarBrand::MERCEDES, "MERCEDES" },
	{ CarBrand::TOYOTA, "TOYOTA" },
	{ CarBrand::KIA, "KIA" },
	{ CarBrand::FERRARI, "FERRARI" },
	{ CarBrand::PORSCHE, "PORSCHE" },
	{ CarBrand::LEXUS, "LEXUS" },
	{ CarBrand::NISSAN, "NISSAN" },
	{ CarBrand::INIFINITI, "INIFINITI" },
};