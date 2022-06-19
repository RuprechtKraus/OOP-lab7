#include "pch.h"
#include "CppUnitTest.h"
#include "MyList.h"
#include <optional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

template <typename T>
void VerifyMyList(const MyList<T>& list, size_t expectedSize, bool expectedToBeEmpty,
	const std::optional<T>& expectedFront, const std::optional<T>& expectedBack)
{
	Assert::AreEqual(expectedSize, list.GetSize(), L"Actual size doesn't match expected");
	Assert::AreEqual(expectedToBeEmpty, list.IsEmpty());

	if (expectedFront)
	{
		Assert::AreEqual(expectedFront.value(), list.GetFront(), L"Actual front element doesn't match expected");
	}

	if (expectedBack)
	{
		Assert::AreEqual(expectedBack.value(), list.GetBack(), L"Actual back element doesn't match expected");
	}
}

template <typename T>
bool AreListsEqual(const MyList<T>& left, const MyList<T>& right)
{
	return std::equal(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

namespace MyListTest
{
	#pragma warning(push)
	#pragma warning(disable : 26800)

	TEST_CLASS(StringMyListTest)
	{
	public :

		TEST_METHOD(ConstructEmptyList)
		{
			MyList<std::string> list;
			VerifyMyList<std::string>(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(CopyConstruct)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2(l1);
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveConstruct)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2(std::move(l1));
			VerifyMyList<std::string>(l1, 0, true, std::nullopt, std::nullopt);
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
		}

		TEST_METHOD(CopyAssign)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2 = l1;
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveAssign)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2 = std::move(l1);
			VerifyMyList<std::string>(l1, 0, true, std::nullopt, std::nullopt);
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
		}

		TEST_METHOD(RangeConstruct)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");
			l1.PushBack("4");
			l1.PushBack("5");

			MyList<std::string> l2(++l1.begin(), --l1.end());
			VerifyMyList<std::string>(l2, 3, false, "2", "4");
		}

		TEST_METHOD(AssignMethod)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2;
			l2.Assign(l1.cbegin(), l1.cend());
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(SwapMethod)
		{
			MyList<std::string> l1;
			l1.PushBack("1");
			l1.PushBack("2");
			l1.PushBack("3");

			MyList<std::string> l2;
			l2.PushBack("4");
			l2.PushBack("5");

			l1.Swap(l2);
			VerifyMyList<std::string>(l1, 2, false, "4", "5");
			VerifyMyList<std::string>(l2, 3, false, "1", "3");
		}

		TEST_METHOD(GetBackAndFrontElements)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, list.GetFront(), L"Actual front element doesn't match expected");
			Assert::AreEqual(str2, list.GetBack(), L"Actual back element doesn't match expected");
		}

		TEST_METHOD(PushBackOneElement)
		{
			MyList<std::string> list;
			std::string str("New string");
			list.PushBack(str);
			VerifyMyList<std::string>(list, 1, false, str, str);
		}

		TEST_METHOD(PushBackTwoElements)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			VerifyMyList<std::string>(list, 2, false, str1, str2);
		}

		TEST_METHOD(PushFrontOneElement)
		{
			MyList<std::string> list;
			std::string str("New string");
			list.PushFront(str);
			VerifyMyList<std::string>(list, 1, false, str, str);
		}

		TEST_METHOD(PushFrontTwoElements)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushFront(str1);
			list.PushFront(str2);
			VerifyMyList<std::string>(list, 2, false, str2, str1);
		}

		TEST_METHOD(ClearList)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushFront(str1);
			list.PushFront(str2);
			list.Clear();

			VerifyMyList<std::string>(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(PopBack)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			list.PopBack();
			VerifyMyList<std::string>(list, 1, false, str1, str1);
		}

		TEST_METHOD(PopFront)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");

			list.PushBack(str1);
			list.PushBack(str2);
			list.PopFront();
			VerifyMyList<std::string>(list, 1, false, str2, str2);
		}

		TEST_METHOD(InsertElementInTheBeginning)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			auto it{ list.Insert(list.begin(), str2) };

			VerifyMyList<std::string>(list, 2, false, str2, str1);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEnd)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			auto it{ list.Insert(list.end(), str2) };

			VerifyMyList<std::string>(list, 2, false, str1, str2);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheMiddle)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			VerifyMyList<std::string>(list, 3, false, str1, str2);
			Assert::AreEqual(*(++list.begin()), str3, L"Actual second element doesn't match expected");
			Assert::AreEqual(str3, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheBeginningOfEmptyList)
		{
			MyList<std::string> list;
			std::string str1("First string");
			auto it{ list.Insert(list.begin(), str1) };

			VerifyMyList<std::string>(list, 1, false, str1, str1);
			Assert::AreEqual(str1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEndOfEmptyList)
		{
			MyList<std::string> list;
			std::string str1("First string");
			auto it{ list.Insert(list.end(), str1) };

			VerifyMyList<std::string>(list, 1, false, str1, str1);
			Assert::AreEqual(str1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(IncrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			Assert::AreEqual(str2, *(++it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(DecrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Insert(++list.begin(), str3) };

			Assert::AreEqual(str1, *(--it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheBeginning)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Erase(list.begin()) };

			VerifyMyList<std::string>(list, 1, false, str2, str2);
			Assert::AreEqual(str2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheEnd)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			auto it{ list.Erase(--list.end()) };

			VerifyMyList<std::string>(list, 1, false, str1, str1);
			Assert::IsTrue(list.end() == it, L"Returned iterator doesn't point to end");
		}

		TEST_METHOD(EraseInTheMiddle)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			std::string str3("Third string");
			list.PushBack(str1);
			list.PushBack(str2);
			list.PushBack(str3);
			auto it{ list.Erase(++list.begin()) };

			VerifyMyList<std::string>(list, 2, false, str1, str3);
			Assert::AreEqual(str3, *it, L"Returned iterator points to wrong element");
		}
	};

	TEST_CLASS(StringMyListConstIteratorTest)
	{
	public:

		TEST_METHOD(DereferenceIterator)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, *list.cbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughList)
		{
			MyList<std::string> list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (const auto& str : list)
			{
				ss << str << " ";
			}

			Assert::AreEqual("1 2 3 "s, ss.str(), L"Iteration through list failed");
		}

		TEST_METHOD(DereferenceReverseIterator)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str2, *list.crbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughMyStringReversively)
		{
			MyList<std::string> list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (MyList<std::string>::ConstReverseIterator it = list.crbegin(); it != list.crend(); it++)
			{
				ss << *it << " ";
			}

			Assert::AreEqual("3 2 1 "s, ss.str(), L"Iteration through list failed");
		}
	};

	TEST_CLASS(StringMyListIteratorTest)
	{
	public:

		TEST_METHOD(DereferenceIterator)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str1, *list.begin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(ChangeElementValueThroughIterator)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);
			*list.begin() = "Third string";

			Assert::AreEqual("Third string"s, *list.begin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(DereferenceReverseIterator)
		{
			MyList<std::string> list;
			std::string str1("First string");
			std::string str2("Second string");
			list.PushBack(str1);
			list.PushBack(str2);

			Assert::AreEqual(str2, *list.rbegin(), L"Iterator points to wrong element");
		}

		TEST_METHOD(IterateThroughMyStringReversively)
		{
			MyList<std::string> list;
			list.PushBack("1");
			list.PushBack("2");
			list.PushBack("3");

			std::ostringstream ss;
			for (MyList<std::string>::ConstReverseIterator it = list.rbegin(); it != list.rend(); it++)
			{
				ss << *it << " ";
			}

			Assert::AreEqual("3 2 1 "s, ss.str(), L"Iteration through list failed");
		}
	};

	TEST_CLASS(IntMyListTest)
	{
	public:

		TEST_METHOD(ConstructEmptyList)
		{
			MyList<int> list;
			VerifyMyList<int>(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(CopyConstruct)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2(l1);
			VerifyMyList<int>(l2, 3, false, 1, 3);
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveConstruct)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2(std::move(l1));
			VerifyMyList<int>(l1, 0, true, std::nullopt, std::nullopt);
			VerifyMyList<int>(l2, 3, false, 1, 3);
		}

		TEST_METHOD(CopyAssign)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2 = l1;
			VerifyMyList<int>(l2, 3, false, 1, 3);
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(MoveAssign)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2 = std::move(l1);
			VerifyMyList<int>(l1, 0, true, std::nullopt, std::nullopt);
			VerifyMyList<int>(l2, 3, false, 1, 3);
		}

		TEST_METHOD(RangeConstruct)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);
			l1.PushBack(4);
			l1.PushBack(5);

			MyList<int> l2(++l1.begin(), --l1.end());
			VerifyMyList<int>(l2, 3, false, 2, 4);
		}

		TEST_METHOD(AssignMethod)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2;
			l2.Assign(l1.cbegin(), l1.cend());
			VerifyMyList<int>(l2, 3, false, 1, 3);
			Assert::IsTrue(AreListsEqual(l1, l2), L"Lists aren't equal");
		}

		TEST_METHOD(SwapMethod)
		{
			MyList<int> l1;
			l1.PushBack(1);
			l1.PushBack(2);
			l1.PushBack(3);

			MyList<int> l2;
			l2.PushBack(4);
			l2.PushBack(5);

			l1.Swap(l2);
			VerifyMyList<int>(l1, 2, false, 4, 5);
			VerifyMyList<int>(l2, 3, false, 1, 3);
		}

		TEST_METHOD(GetBackAndFrontElements)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);

			Assert::AreEqual(1, list.GetFront(), L"Actual front element doesn't match expected");
			Assert::AreEqual(2, list.GetBack(), L"Actual back element doesn't match expected");
		}

		TEST_METHOD(PushBackOneElement)
		{
			MyList<int> list;
			list.PushBack(1);
			VerifyMyList<int>(list, 1, false, 1, 1);
		}

		TEST_METHOD(PushBackTwoElements)
		{
			MyList<int> list;

			list.PushBack(1);
			list.PushBack(2);
			VerifyMyList<int>(list, 2, false, 1, 2);
		}

		TEST_METHOD(PushFrontOneElement)
		{
			MyList<int> list;
			list.PushFront(1);
			VerifyMyList<int>(list, 1, false, 1, 1);
		}

		TEST_METHOD(PushFrontTwoElements)
		{
			MyList<int> list;

			list.PushFront(1);
			list.PushFront(2);
			VerifyMyList<int>(list, 2, false, 2, 1);
		}

		TEST_METHOD(ClearList)
		{
			MyList<int> list;

			list.PushFront(1);
			list.PushFront(1);
			list.Clear();

			VerifyMyList<int>(list, 0, true, std::nullopt, std::nullopt);
		}

		TEST_METHOD(PopBack)
		{
			MyList<int> list;

			list.PushBack(1);
			list.PushBack(2);
			list.PopBack();
			VerifyMyList<int>(list, 1, false, 1, 1);
		}

		TEST_METHOD(PopFront)
		{
			MyList<int> list;
			std::string str1("First string");

			list.PushBack(1);
			list.PushBack(2);
			list.PopFront();
			VerifyMyList<int>(list, 1, false, 2, 2);
		}

		TEST_METHOD(InsertElementInTheBeginning)
		{
			MyList<int> list;
			list.PushBack(1);
			auto it{ list.Insert(list.begin(), 2) };

			VerifyMyList<int>(list, 2, false, 2, 1);
			Assert::AreEqual(2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEnd)
		{
			MyList<int> list;
			list.PushBack(1);
			auto it{ list.Insert(list.end(), 2) };

			VerifyMyList<int>(list, 2, false, 1, 2);
			Assert::AreEqual(2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheMiddle)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			auto it{ list.Insert(++list.begin(), 3) };

			VerifyMyList<int>(list, 3, false, 1, 2);
			Assert::AreEqual(*(++list.begin()), 3, L"Actual second element doesn't match expected");
			Assert::AreEqual(3, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheBeginningOfEmptyList)
		{
			MyList<int> list;
			auto it{ list.Insert(list.begin(), 1) };

			VerifyMyList<int>(list, 1, false, 1, 1);
			Assert::AreEqual(1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(InsertElementInTheEndOfEmptyList)
		{
			MyList<int> list;
			auto it{ list.Insert(list.end(), 1) };

			VerifyMyList<int>(list, 1, false, 1, 1);
			Assert::AreEqual(1, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(IncrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			auto it{ list.Insert(++list.begin(), 3) };

			Assert::AreEqual(2, *(++it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(DecrementReturnedIteratorAfterInsertingElementInTheMiddle)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			auto it{ list.Insert(++list.begin(), 3) };

			Assert::AreEqual(1, *(--it), L"Incremented returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheBeginning)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			auto it{ list.Erase(list.begin()) };

			VerifyMyList<int>(list, 1, false, 2, 2);
			Assert::AreEqual(2, *it, L"Returned iterator points to wrong element");
		}

		TEST_METHOD(EraseInTheEnd)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			auto it{ list.Erase(--list.end()) };

			VerifyMyList<int>(list, 1, false, 1, 1);
			Assert::IsTrue(list.end() == it, L"Returned iterator doesn't point to end");
		}

		TEST_METHOD(EraseInTheMiddle)
		{
			MyList<int> list;
			list.PushBack(1);
			list.PushBack(2);
			list.PushBack(3);
			auto it{ list.Erase(++list.begin()) };

			VerifyMyList<int>(list, 2, false, 1, 3);
			Assert::AreEqual(3, *it, L"Returned iterator points to wrong element");
		}
	};

	#pragma warning(pop)
}