#include "pch.h"
#include "CppUnitTest.h"
#include "FindMaxExLib.h"
#include <tuple>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace FindMaxExTest
{
	TEST_CLASS(FindMaxExIntTest)
	{
	public:
		
		TEST_METHOD(FindMaxIntUsingDefaultPredicate)
		{
			std::vector<int> vec{ 4, 8, 0, 1, 6, -5, 4 };
			int max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxIntUsingDefaultPredicateWhereMaxElemIsFirst)
		{
			std::vector<int> vec{ 8, 4, 0, 1, 6, -5, 4 };
			int max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxIntUsingDefaultPredicateWhereMaxElemIsLast)
		{
			std::vector<int> vec{ 4, 4, 0, 1, 6, -5, 8 };
			int max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxIntUsingCustomPredicate)
		{
			std::vector<int> vec{ 4, 8, 0, 1, 6, -5, 4 };
			int max{};
			Assert::IsTrue(FindMax(vec, max, [](int left, int right) { return left < right; }), 
				L"FindMax on not empty vector returned false");
			Assert::AreEqual(8, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMinIntUsingCustomPredicate)
		{
			std::vector<int> vec{ 4, 8, 0, 1, 6, -5, 4 };
			int max{};
			Assert::IsTrue(FindMax(vec, max, [](int left, int right) { return left > right; }),
				L"FindMax on not empty vector returned false");
			Assert::AreEqual(-5, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FinMaxIntOnEmptyVector)
		{
			std::vector<int> vec;
			int max{};
			Assert::IsFalse(FindMax(vec, max), L"FindMax returned true on empty vector");
		}
	};

	TEST_CLASS(FindMaxExFloatTest)
	{
	public:

		TEST_METHOD(FindMaxFloatUsingDefaultPredicate)
		{
			std::vector<float> vec{ 4.5, 8.3, 0.3, 1.2, 6.7, -5.9, 4.2 };
			float max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8.3f, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxFloatUsingDefaultPredicateWhereMaxElemIsFirst)
		{
			std::vector<float> vec{ 8.3, 4.5, 0.3, 1.2, 6.7, -5.9, 4.2 };
			float max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8.3f, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxFloatUsingDefaultPredicateWhereMaxElemIsLast)
		{
			std::vector<float> vec{ 4.5, 0.3, 1.2, 6.7, -5.9, 4.2, 8.3 };
			float max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual(8.3f, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxFloatUsingCustomPredicate)
		{
			std::vector<float> vec{ 4.5, 8.3, 0.3, 1.2, 6.7, -5.9, 4.2 };
			float max{};
			Assert::IsTrue(FindMax(vec, max, [](float left, float right) { return left < right; }),
				L"FindMax on not empty vector returned false");
			Assert::AreEqual(8.3f, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMinFloatUsingCustomPredicate)
		{
			std::vector<float> vec{ 4.5, 8.3, 0.3, 1.2, 6.7, -5.9, 4.2 };
			float max{};
			Assert::IsTrue(FindMax(vec, max, [](float left, float right) { return left > right; }),
				L"FindMax on not empty vector returned false");
			Assert::AreEqual(-5.9f, max, L"Expected max value doesn't match actual");
		}
	};

	TEST_CLASS(FindMaxExStringTest)
	{
	public:

		TEST_METHOD(FindMaxStringUsingDefaultPredicate)
		{
			std::vector<std::string> vec{ 
				"pollution", "decide", "drain", "salmon", 
				"relaxation", "abnormal", "minimize"
			};
			std::string max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual("salmon"s, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxStringUsingDefaultPredicateWhereMaxElemIsFirst)
		{
			std::vector<std::string> vec{
				"salmon", "pollution", "decide", "drain",
				"relaxation", "abnormal", "minimize"
			};
			std::string max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual("salmon"s, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxStringUsingDefaultPredicateWhereMaxElemIsLast)
		{
			std::vector<std::string> vec{
				"pollution", "decide", "drain", 
				"relaxation", "abnormal", "minimize", "salmon"
			};
			std::string max{};
			Assert::IsTrue(FindMax(vec, max), L"FindMax on not empty vector returned false");
			Assert::AreEqual("salmon"s, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMaxStringUsingCustomPredicate)
		{
			std::vector<std::string> vec{
				"pollution", "decide", "drain", "salmon",
				"relaxation", "abnormal", "minimize"
			};
			std::string max{};
			Assert::IsTrue(FindMax(vec, max, [](std::string left, std::string right) { return left < right; }),
				L"FindMax on not empty vector returned false");
			Assert::AreEqual("salmon"s, max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindMinStringUsingCustomPredicate)
		{
			std::vector<std::string> vec{
				"pollution", "decide", "drain", "salmon",
				"relaxation", "abnormal", "minimize"
			};
			std::string max{};
			Assert::IsTrue(FindMax(vec, max, [](std::string left, std::string right) { return left > right; }),
				L"FindMax on not empty vector returned false");
			Assert::AreEqual("abnormal"s, max, L"Expected max value doesn't match actual");
		}
	};

	TEST_CLASS(FindMaxExSportsmanTest)
	{
		struct Sportsman
		{
			std::string m_fullName;
			int m_height{};
			int m_weight{};

			friend bool operator==(const Sportsman& left, const Sportsman& right)
			{
				auto Rank = [](const Sportsman& s)
				{
					return std::tie(s.m_fullName, s.m_height, s.m_weight);
				};
				return Rank(left) == Rank(right);
			};
		};

	public:
		TEST_METHOD(FindTallestSportsman)
		{
			Sportsman max{};
			Assert::IsTrue(FindMax(m_vec, max, [](const Sportsman& left, const Sportsman& right) { 
				return left.m_height < right.m_height;
			}), L"FindMax on not empty vector returned false");
			Assert::IsTrue(Sportsman{ "Ray Calderon", 196, 118 } == max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindFattestSportsman)
		{
			Sportsman max{};
			Assert::IsTrue(FindMax(m_vec, max, [](const Sportsman& left, const Sportsman& right) {
				return left.m_weight < right.m_weight;
			}), L"FindMax on not empty vector returned false");
			Assert::IsTrue(Sportsman{ "Ray Calderon", 196, 118 } == max, L"Expected max value doesn't match actual");
		}

		TEST_METHOD(FindShortestSportsman)
		{
			Sportsman min{};
			Assert::IsTrue(FindMax(m_vec, min, [](const Sportsman& left, const Sportsman& right) {
				return left.m_height > right.m_height;
			}),	L"FindMax on not empty vector returned false");
			Assert::IsTrue(Sportsman{ "Camilla Mays", 164, 59 } == min, L"Expected min value doesn't match actual");
		}

		TEST_METHOD(FindLightestSportsman)
		{
			Sportsman min{};
			Assert::IsTrue(FindMax(m_vec, min, [](const Sportsman& left, const Sportsman& right) {
				return left.m_weight > right.m_weight;
			}),
				L"FindMax on not empty vector returned false");
			Assert::IsTrue(Sportsman{ "Saniyah Walters", 173, 57 } == min, L"Expected min value doesn't match actual");
		}

	private:
		std::vector<Sportsman> m_vec{
			{ "Ray Calderon", 196, 118 },
			{ "Patrick Leblanc", 180, 78 },
			{ "Saniyah Walters", 173, 57 },
			{ "Madilynn Rose", 186, 82 },
			{ "Camilla Mays", 164, 59 },
		};
	};
}
