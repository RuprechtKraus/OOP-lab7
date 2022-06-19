#pragma once
#include <memory>

template <typename T>
class MyListIterator;

template <typename T>
class MyListConstIterator;

#pragma region MyList

template <typename T>
class MyList
{
	friend class MyListIterator<T>;
	friend class MyListConstIterator<T>;

	class Node
	{
	public:
		Node(const T& data, Node* prev, std::unique_ptr<Node>&& next);

		T m_data;
		Node* m_prev{};
		std::unique_ptr<Node> m_next;
	};

public:
	using Iterator = MyListIterator<T>;
	using ConstIterator = MyListConstIterator<T>;
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
MyList<T>::MyList(const MyList<T>& other)
{
	ConstructRange(other.begin(), other.end());
}

template <typename T>
MyList<T>::MyList(MyList<T>&& other) noexcept
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
MyList<T>& MyList<T>::operator=(const MyList<T>& other)
{
	if (&other != this)
	{
		Assign(other.begin(), other.end());
	}
	return *this;
}

template <typename T>
MyList<T>& MyList<T>::operator=(MyList<T>&& other) noexcept
{
	if (&other != this)
	{
		Swap(other);
		other.Clear();
	}
	return *this;
}

template <typename T>
void MyList<T>::ConstructRange(ConstIterator begin, ConstIterator end)
{
	_STL_ASSERT(begin.m_container == end.m_container, "List iterators incompatible");
	MyList<T> tmp;
	while (begin != end)
	{
		tmp.PushBack(*begin);
		begin++;
	}
	Swap(tmp);
}

template <typename T>
void MyList<T>::PushBack(const T& str)
{
	EmplaceBack(str);
}

template <typename T>
void MyList<T>::PushFront(const T& str)
{
	EmplaceFront(str);
}

template <typename T>
void MyList<T>::Clear() noexcept
{
	while (m_first)
	{
		m_first = std::move(m_first->m_next);
	}
	m_last = nullptr;

	m_size = 0;
}

template <typename T>
void MyList<T>::PopBack() noexcept
{
	_STL_ASSERT(m_size != 0, "PopBack called on empty list");
	EraseBack();
}

template <typename T>
void MyList<T>::PopFront() noexcept
{
	_STL_ASSERT(m_size != 0, "PopFront called on empty list");
	EraseFront();
}

template <typename T>
bool MyList<T>::IsEmpty() const noexcept
{
	return !m_first.get();
}

template <typename T>
void MyList<T>::Assign(ConstIterator begin, ConstIterator end)
{
	MyList<T> tmp(begin, end);
	Swap(tmp);
}

template <typename T>
void MyList<T>::Swap(MyList<T>& other) noexcept
{
	std::swap(m_first, other.m_first);
	std::swap(m_last, other.m_last);
	std::swap(m_size, other.m_size);
}

template <typename T>
MyList<T>::Iterator MyList<T>::Insert(ConstIterator position, const T& str)
{
	_STL_ASSERT(position.m_container == this, "List insert iterator outside range");
	if (position.m_ptr == m_first.get())
	{
		return MakeIterator(EmplaceFront(str));
	}
	else if (position.m_ptr == nullptr)
	{
		return MakeIterator(EmplaceBack(str));
	}
	else
	{
		return MakeIterator(Emplace(str, position.m_ptr));
	}
}

template <typename T>
MyList<T>::Iterator MyList<T>::Erase(ConstIterator position) noexcept
{
	_STL_ASSERT(position.m_container == this, "List erase iterator outside range");
	if (position.m_ptr == m_first.get())
	{
		return MakeIterator(EraseFront());
	}
	else if (position.m_ptr == m_last)
	{
		return MakeIterator(EraseBack());
	}
	else
	{
		return MakeIterator(Erase(position.m_ptr));
	}
}

template <typename T>
MyList<T>::NodePtr MyList<T>::EmplaceBack(const T& str)
{
	auto node{ std::make_unique<Node>(str, m_last, nullptr) };
	Node* newLast{ node.get() };

	if (m_last)
	{
		m_last->m_next = std::move(node);
	}
	else
	{
		m_first = std::move(node);
	}
	m_last = newLast;

	m_size++;
	return m_last;
}

template <typename T>
MyList<T>::NodePtr MyList<T>::EmplaceFront(const T& str)
{
	auto node{ std::make_unique<Node>(str, nullptr, std::move(m_first)) };
	Node* newFirst{ node.get() };

	m_first = std::move(node);
	if (m_last)
	{
		m_first->m_next->m_prev = newFirst;
	}
	else
	{
		m_last = newFirst;
	}

	m_size++;
	return m_first.get();
}

template <typename T>
MyList<T>::NodePtr MyList<T>::Emplace(const T& str, NodePtr position)
{
	auto node{ std::make_unique<Node>(str, position->m_prev, std::move(position->m_prev->m_next)) };
	Node* newNode{ node.get() };

	newNode->m_prev->m_next = std::move(node);
	newNode->m_next->m_prev = newNode;
	m_size++;

	return newNode;
}

template <typename T>
MyList<T>::NodePtr MyList<T>::EraseBack() noexcept
{
	m_last = m_last->m_prev;
	m_last->m_next = nullptr;
	m_size--;
	return nullptr;
}

template <typename T>
MyList<T>::NodePtr MyList<T>::EraseFront() noexcept
{
	m_first = std::move(m_first->m_next);
	m_first->m_prev = nullptr;
	m_size--;
	return m_first.get();
}

template <typename T>
MyList<T>::NodePtr MyList<T>::Erase(NodePtr position) noexcept
{
	Node* node{ position->m_next.get() };
	position->m_next->m_prev = position->m_prev;
	position->m_prev->m_next = std::move(position->m_next);
	m_size--;
	return node;
}

template <typename T>
T& MyList<T>::GetBack() noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

template <typename T>
const T& MyList<T>::GetBack() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetBackElement called on empty list");
	return m_last->m_data;
}

template <typename T>
T& MyList<T>::GetFront() noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

template <typename T>
const T& MyList<T>::GetFront() const noexcept
{
	_STL_ASSERT(m_size != 0, "GetFrontElement called on empty list");
	return m_first->m_data;
}

template <typename T>
size_t MyList<T>::GetSize() const noexcept
{
	return m_size;
}

template <typename T>
MyList<T>::Iterator MyList<T>::MakeIterator(NodePtr ptr) const noexcept
{
	return Iterator(ptr, this);
}

template <typename T>
MyList<T>::ConstIterator MyList<T>::MakeConstIterator(NodePtr ptr) const noexcept
{
	return ConstIterator(ptr, this);
}

template <typename T>
MyList<T>::Iterator MyList<T>::begin() noexcept
{
	return Iterator(m_first.get(), this);
}

template <typename T>
MyList<T>::Iterator MyList<T>::end() noexcept
{
	return Iterator(nullptr, this);
}

template <typename T>
MyList<T>::ConstIterator MyList<T>::begin() const noexcept
{
	return ConstIterator(m_first.get(), this);
}

template <typename T>
MyList<T>::ConstIterator MyList<T>::end() const noexcept
{
	return ConstIterator(nullptr, this);
}

template <typename T>
MyList<T>::ConstIterator MyList<T>::cbegin() const noexcept
{
	return begin();
}

template <typename T>
MyList<T>::ConstIterator MyList<T>::cend() const noexcept
{
	return end();
}

template <typename T>
MyList<T>::ReverseIterator MyList<T>::rbegin() noexcept
{
	return ReverseIterator(end());
}

template <typename T>
MyList<T>::ReverseIterator MyList<T>::rend() noexcept
{
	return ReverseIterator(begin());
}

template <typename T>
MyList<T>::ConstReverseIterator MyList<T>::rbegin() const noexcept
{
	return ConstReverseIterator(end());
}

template <typename T>
MyList<T>::ConstReverseIterator MyList<T>::rend() const noexcept
{
	return ConstReverseIterator(begin());
}

template <typename T>
MyList<T>::ConstReverseIterator MyList<T>::crbegin() const noexcept
{
	return rbegin();
}

template <typename T>
MyList<T>::ConstReverseIterator MyList<T>::crend() const noexcept
{
	return rend();
}

#pragma endregion MyList

#pragma region MyListConstIterator

template <typename T>
class MyListConstIterator
{
	friend class MyList<T>;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = MyList<T>::ValueType;
	using pointer = const value_type*;
	using reference = const value_type&;
	using Container = MyList<T>;
	using NodePtr = Container::NodePtr;

	MyListConstIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	MyListConstIterator<T>& operator++() noexcept;
	MyListConstIterator<T> operator++(int) noexcept;
	MyListConstIterator<T>& operator--() noexcept;
	MyListConstIterator<T> operator--(int) noexcept;

	template <typename T>
	friend bool operator==(const MyListConstIterator<T>& left, const MyListConstIterator<T>& right) noexcept;

	template <typename T>
	friend bool operator!=(const MyListConstIterator<T>& left, const MyListConstIterator<T>& right) noexcept;
	 
protected:
	MyListConstIterator(NodePtr ptr, const Container* container) noexcept;

	NodePtr m_ptr;
	const Container* m_container;
};

template <typename T>
MyListConstIterator<T>::MyListConstIterator() noexcept
	: m_ptr(nullptr)
	, m_container(nullptr)
{
}

template <typename T>
MyListConstIterator<T>::MyListConstIterator(NodePtr ptr, const Container* container) noexcept
	: m_ptr(ptr)
	, m_container(container)
{
}

template <typename T>
MyListConstIterator<T>::reference MyListConstIterator<T>::operator*() const noexcept
{
	_STL_ASSERT(m_container, "Cannot dereference value-initialized list iterator");
	_STL_ASSERT(m_ptr != nullptr, "Cannot dereference end list iterator");
	return m_ptr->m_data;
}

template <typename T>
MyListConstIterator<T>::pointer MyListConstIterator<T>::operator->() const noexcept
{
	return &(**this);
}

template <typename T>
MyListConstIterator<T>& MyListConstIterator<T>::operator++() noexcept
{
	_STL_ASSERT(m_container, "Cannot increment value-initialized list iterator");
	_STL_ASSERT(m_ptr != nullptr, "Cannot increment end list iterator");
	this->m_ptr = this->m_ptr->m_next.get();
	return *this;
}

template <typename T>
MyListConstIterator<T> MyListConstIterator<T>::operator++(int) noexcept
{
	MyListConstIterator tmp{ *this };
	++*this;
	return tmp;
}

template <typename T>
MyListConstIterator<T>& MyListConstIterator<T>::operator--() noexcept
{
	_STL_ASSERT(m_container, "Cannot decrement value-initialized list iterator");
	_STL_ASSERT(m_ptr != m_container->m_first.get(), "Cannot decrement begin list iterator");
	if (m_ptr == nullptr)
	{
		this->m_ptr = m_container->m_last;
	}
	else
	{
		this->m_ptr = this->m_ptr->m_prev;
	}
	return *this;
}

template <typename T>
MyListConstIterator<T> MyListConstIterator<T>::operator--(int) noexcept
{
	MyListConstIterator tmp{ *this };
	--*this;
	return tmp;
}

template <typename T>
bool operator==(const MyListConstIterator<T>& left, const MyListConstIterator<T>& right) noexcept
{
	_STL_ASSERT(left.m_container == right.m_container, "List iterators incompatible");
	return left.m_ptr == right.m_ptr;
}

template <typename T>
bool operator!=(const MyListConstIterator<T>& left, const MyListConstIterator<T>& right) noexcept
{
	return !(left == right);
}

#pragma endregion MyListConstIterator

#pragma region MyListIterator

template <typename T>
class MyListIterator : public MyListConstIterator<T>
{
	friend class MyList<T>;

public:
	using MyBase = MyListConstIterator<T>;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = MyList<T>::ValueType;
	using pointer = value_type*;
	using reference = value_type&;
	using Container = MyList<T>;
	using NodePtr = Container::NodePtr;

	MyListIterator() noexcept;

	reference operator*() const noexcept;
	pointer operator->() const noexcept;

	MyListIterator<T>& operator++() noexcept;
	MyListIterator<T> operator++(int) noexcept;
	MyListIterator<T>& operator--() noexcept;
	MyListIterator<T> operator--(int) noexcept;

private:
	MyListIterator(NodePtr ptr, const Container* container) noexcept;
};

template <typename T>
MyListIterator<T>::MyListIterator() noexcept
	: MyListConstIterator<T>(nullptr, nullptr)
{
}

template <typename T>
MyListIterator<T>::MyListIterator(NodePtr ptr, const Container* container) noexcept
	: MyListConstIterator<T>(ptr, container)
{
}

template <typename T>
MyListIterator<T>::reference MyListIterator<T>::operator*() const noexcept
{
	return const_cast<reference>(MyBase::operator*());
}

template <typename T>
MyListIterator<T>::pointer MyListIterator<T>::operator->() const noexcept
{
	return &(**this);
}

template <typename T>
MyListIterator<T>& MyListIterator<T>::operator++() noexcept
{
	MyBase::operator++();
	return *this;
}

template <typename T>
MyListIterator<T> MyListIterator<T>::operator++(int) noexcept
{
	MyListIterator tmp{ *this };
	MyBase::operator++();
	return tmp;
}

template <typename T>
MyListIterator<T>& MyListIterator<T>::operator--() noexcept
{
	MyBase::operator--();
	return *this;
}

template <typename T>
MyListIterator<T> MyListIterator<T>::operator--(int) noexcept
{
	MyListIterator tmp{ *this };
	MyBase::operator--();
	return tmp;
}

#pragma endregion MyListIterator