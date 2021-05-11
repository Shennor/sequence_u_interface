#pragma once
#include <stdexcept>
#include "i_enumerator.h"
#include "i_collection.h"

template <class T> struct Node
{
	T data_ = {};
	struct Node<T>* next_ = nullptr;
};

template <typename T>
class LinkedListEnumerator : public IEnumerator<T>
{
private:
	Node<T>* p_begin = nullptr;
	Node<T>* p_current = nullptr;
	Node<T>* p_end = nullptr;
public:
	LinkedListEnumerator(Node<T>* const b, Node<T>* const e);

	bool MoveNext() override;
	T GetCurrent() override;
	void Reset() override;
};


template <class T> class LinkedList : public IEnumerable<T>, public ICollection<T>
{
private:
	Node<T>* head_ = nullptr;
	size_t length_ = 0;
public:
	// Constructors
	
	LinkedList(const T* items, size_t count);
	LinkedList();
	LinkedList(const LinkedList<T>& list);

	LinkedList<T>& operator=(const LinkedList<T>& other);

	// Decomposition
	
	T GetFirst() const;
	T GetLast() const;
	T Get(size_t index) const override;
	void Set(size_t index, T value);
	size_t GetCount() const override;
	
	LinkedList<T> GetSubList(size_t start_index, size_t end_index) const;
	void Append(T item);
	void Prepend(T item);
	void InsertAt(T item, size_t index);
	
	LinkedList<T> Concat(LinkedList<T>& list);

	// Iterator

	IEnumerator<T>* GetEnumerator() override;

	// Destructor

	~LinkedList();
};

// Realization

template <class T>
void copy_nodes(
	Node<T>* source, Node<T>* destination, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		destination->data_ = source->data_;
		destination->next_ = new Node<T>;
		destination = destination->next_;
		source = source->next_;
	}
}

template <typename T>
LinkedListEnumerator<T>::LinkedListEnumerator(Node<T>* const b, Node<T>* const e)
{
	p_begin = b;
	p_current = b;
	p_end = e;
}

template <typename T>
bool LinkedListEnumerator<T>::MoveNext()
{
	if (p_current->next_ != p_end && p_current->next_ != nullptr)
	{
		p_current = p_current->next_;
		return true;
	}
	return false;
}

template <typename T>
T LinkedListEnumerator<T>::GetCurrent()
{
	if(p_current->next_ == nullptr)
	{
		throw std::out_of_range("LinkedListEnumerator GetCurrent: this is the end");
	}
	return p_current->data_;
}

template <typename T>
void LinkedListEnumerator<T>::Reset()
{
	p_current = p_begin;
}

template <class T>
LinkedList<T>::LinkedList(const T* items, size_t count)
{
	head_ = new Node<T>;
	Node<T>* cur = head_;
	for (size_t i = 0; i < count; ++i)
	{
		cur->data_ = items[i];
		cur->next_ = new Node<T>;
		cur = cur->next_;
	}
	length_ = count;
}

template <class T>
LinkedList<T>::LinkedList()
{
	head_ = new Node<T>;
	length_ = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>&  list)
{
	head_ = new Node<T>;
	Node<T>* cur_this = head_;
	Node<T>* cur_other = list.head_;
	copy_nodes(cur_other, cur_this, list.length_);
	length_ = list.length_;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this == &other) return *this;
	copy_nodes(other.head_, head_, other.length_);
	this->length_ = other.length_;
	return *this;
}

template <class T>
T LinkedList<T>::Get(size_t index) const
{
	if (index >= length_)
	{
		throw std::out_of_range(
			"LinkedList Get: index out of range");
	}
	Node<T>* cur = head_;
	for (size_t i = 0; i < index; ++i)
	{
		cur = cur->next_;
	}
	return cur->data_;
}

template <class T>
void LinkedList<T>::Set(size_t index, T value)
{
	if(index >= length_)
	{
		throw std::out_of_range("LinkedList Set: index out of range");
	}
	Node<T>* cur = head_;
	for(size_t i = 0; i < index; ++i)
	{
		cur = cur->next_;
	}
	cur->data_ = value;
}

template <class T>
T LinkedList<T>::GetFirst() const
{
	if (length_ == 0)
	{
		throw std::out_of_range(
			"LinkedList GetFirst: list is empty");
	}
	return Get(0);
}

template <class T>
T LinkedList<T>::GetLast() const
{
	if (length_ == 0)
	{
		throw std::out_of_range(
			"LinkedList GetLast: list is empty");
	}
	return Get(length_ - 1);
}

template <class T>
LinkedList<T>
LinkedList<T>::GetSubList(size_t start_index, size_t end_index) const
{
	if (length_ == 0)
	{
		throw std::out_of_range(
			"LinkedList GetSubList: list is empty");
	}

	if (start_index >= length_)
	{
		throw std::out_of_range(
			"LinkedList GetSubList: start_index out of range");
	}

	if (end_index >= length_)
	{
		throw std::out_of_range(
			"LinkedList GetSubList: end_index out of range");
	}

	if (start_index > end_index)
	{
		throw std::out_of_range("LinkedList GetSubList: "
			"end_index is less than start_index");
	}

	Node<T>* h = head_;
	LinkedList<T> sub_list;
	for(size_t i = 0; i < start_index; ++i)
	{
		h = h->next_;
	}
	sub_list.head_ = new Node<T>;
	sub_list.length_ = end_index - start_index + 1;
	copy_nodes(h, sub_list.head_, 
		end_index - start_index + 1);
	return sub_list;
}

template <class T>
size_t LinkedList<T>::GetCount() const
{
	return length_;
}

template <class T>
void LinkedList<T>::InsertAt(T item, size_t index)
{
	if (index > length_)
	{
		throw std::out_of_range(
			"LinkedList InsertAt: index out of range");
	}
	
	Node<T>* cur1 = nullptr;
	Node<T>* cur2 = head_;
	for (size_t i = 0; i < index; ++i)
	{
		cur1 = cur2;
		cur2 = cur2->next_;
	}

	Node<T>* ncur = new Node<T>;
	ncur->data_ = item;
	ncur->next_ = cur2;

	if (cur1 != nullptr)
	{
		cur1->next_ = ncur;
	}
	else
	{
		head_ = ncur;
	}
	
	length_++;
}

template <class T>
void LinkedList<T>::Append(T item)
{
	InsertAt(item, length_);
}

template <class T>
void LinkedList<T>::Prepend(T item)
{
	InsertAt(item, 0);
}

template <class T>
LinkedList<T> LinkedList<T>::Concat(LinkedList<T>& list)
{
	LinkedList<T> res;
	res.head_ = new Node<T>;
	Node<T>* cur = res.head_;

	Node<T>* cur_this = head_;
	copy_nodes(cur_this, cur, length_);

	for(size_t i = 0; i < length_; ++i)
	{
		if(cur->next_ == nullptr)
		{
			cur->next_ = new Node<T>;
		}
		cur = cur->next_;
	}

	Node<T>* cur_other = list.head_;
	copy_nodes(cur_other, cur, list.length_);

	res.length_ = length_ + list.length_;
	return res;
}

template <class T>
IEnumerator<T>* LinkedList<T>::GetEnumerator()
{
	Node<T>* end = head_;
	for (size_t i = 0; i < length_; ++i)
	{
		end = end->next_;
	}
	IEnumerator<T>* res = new LinkedListEnumerator(head_, end);
	return res;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* prev = head_;
	for (size_t i = 0; i < length_; ++i)
	{
		Node<T>* cur = prev->next_;
		delete prev;
		prev = cur;
	}
	delete prev;
}
