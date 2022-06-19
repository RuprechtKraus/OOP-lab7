#pragma once
#include <memory>

template <typename T>
class MyList
{
	friend class MyListIterator;
	friend class MyListConstIterator;

	class Node
	{
	public:
		Node(const T& data, Node* prev, std::unique_ptr<Node>&& next);

		T m_data;
		Node* m_prev{};
		std::unique_ptr<Node> m_next;
	};

public:
	using Iterator = MyListIterator;
	using ConstIterator = MyListConstIterator;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
	using ValueType = T;
	using Reference = ValueType&;
	using ConstReference = const ValueType&;
	using NodePtr = Node*;

	MyList() = default;
	MyList(const MyList& other);
	MyList(MyList&& other) noexcept;
	MyList(ConstIterator begin, ConstIterator end);
	~MyList() noexcept;

	MyList& operator=(const MyList& other);
	MyList& operator=(MyList&& other) noexcept;

	void PushBack(const T& str);
	void PushFront(const T& str);
	void Clear() noexcept;
	void PopBack() noexcept;
	void PopFront() noexcept;
	bool IsEmpty() const noexcept;
	void Assign(ConstIterator begin, ConstIterator end);
	void Swap(MyList& other) noexcept;
	Iterator Insert(ConstIterator position, const T& str);
	Iterator Erase(ConstIterator position) noexcept;
	Reference GetBack() noexcept;
	ConstReference GetBack() const noexcept;
	Reference GetFront() noexcept;
	ConstReference GetFront() const noexcept;
	size_t GetSize() const noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;
	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;
	ConstReverseIterator rbegin() const noexcept;
	ConstReverseIterator rend() const noexcept;
	ConstReverseIterator crbegin() const noexcept;
	ConstReverseIterator crend() const noexcept;

private:
	void ConstructRange(ConstIterator begin, ConstIterator end);
	NodePtr EmplaceFront(const T& str);
	NodePtr EmplaceBack(const T& str);
	NodePtr Emplace(const T& str, NodePtr position);
	NodePtr EraseFront() noexcept;
	NodePtr EraseBack() noexcept;
	NodePtr Erase(NodePtr position) noexcept;
	Iterator MakeIterator(NodePtr ptr) const noexcept;
	ConstIterator MakeConstIterator(NodePtr ptr) const noexcept;

	size_t m_size{};
	Node* m_last{};
	std::unique_ptr<Node> m_first;
};

template <typename T>
MyList<T>::Node::Node(const T& data, Node* prev, std::unique_ptr<Node>&& next)
	: m_data(data)
	, m_prev(prev)
	, m_next(std::move(next))
{
}

template <typename T>
MyList<T>::MyList(const MyList& other)
{
	ConstructRange(other.begin(), other.end());
}

template <typename T>
MyList<T>::MyList(MyList&& other) noexcept
{
	Swap(other);
}

template <typename T>
MyList<T>::MyList(ConstIterator begin, ConstIterator end)
{
	ConstructRange(begin, end);
}

template <typename T>
MyList<T>::~MyList() noexcept
{
	Clear();
}

template <typename T>
class StringListConstIterator
{
	friend class StringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = MyList::ValueType;
	using pointer = const value_type*;
	using reference = const value_type&;
	using Container = MyList;
	using NodePtr = Container::NodePtr;

	StringListConstIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	StringListConstIterator& operator++() noexcept;
	StringListConstIterator operator++(int) noexcept;
	StringListConstIterator& operator--() noexcept;
	StringListConstIterator operator--(int) noexcept;

	friend bool operator==(const StringListConstIterator& left, const StringListConstIterator& right) noexcept;
	friend bool operator!=(const StringListConstIterator& left, const StringListConstIterator& right) noexcept;

protected:
	StringListConstIterator(NodePtr ptr, const Container* container) noexcept;

	NodePtr m_ptr;
	const Container* m_container;
};

template <typename T>
class StringListIterator : public StringListConstIterator
{
	friend class StringList;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = MyList::ValueType;
	using pointer = value_type*;
	using reference = value_type&;
	using Container = MyList;
	using NodePtr = Container::NodePtr;
	using MyBase = StringListConstIterator;

	StringListIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	StringListIterator& operator++() noexcept;
	StringListIterator operator++(int) noexcept;
	StringListIterator& operator--() noexcept;
	StringListIterator operator--(int) noexcept;

private:
	StringListIterator(NodePtr ptr, const Container* container) noexcept;
};