#pragma once
#include <stdexcept>
#include "i_enumerator.h"
#include "i_collection.h"


template <typename T>
class ArrayEnumerator : public IEnumerator<T>
{
private:
	T* p_begin = nullptr;
	T* p_current = nullptr;
	T* p_end = nullptr;
public:
	
	ArrayEnumerator(T* begin, T* end);
	
	bool MoveNext() override;
	T GetCurrent() override;
	void Reset() override;
};

template <class T> class DynamicArray : public IEnumerable<T>, public ICollection<T>
{
private:
	size_t size_ = 0;
	size_t capacity_ = 0;
	float growth_factor_ = 2;
	T* p_data_ = nullptr;
public:
	// Constructors

	DynamicArray() = default;
	DynamicArray(T* items, size_t count);
	DynamicArray(size_t size);
	DynamicArray(const DynamicArray<T>& dynamic_array);

	// Decomposition

	T Get(size_t index) const;
	size_t GetCount() const;
	void Set(size_t index, T value);
	
	// Operators

	DynamicArray<T>& operator=(const DynamicArray<T>& other);

	// Operations

	void Resize(size_t new_size);
	DynamicArray<T>* Slice(size_t start_index, size_t end_index) const;

	// Iterator

	IEnumerator<T>* GetEnumerator() override;

	// Destructor

	~DynamicArray();
};

// Realization

template <typename T>
ArrayEnumerator<T>::ArrayEnumerator(T* begin, T* end)
{
	p_begin = begin;
	p_current = begin;
	p_end = end;
}

template <typename T>
bool ArrayEnumerator<T>::MoveNext()
{
	if (p_current + 1 != p_end && p_current != p_end)
	{
		++p_current;
		return true;
	}
	return false;
}

template <typename T>
T ArrayEnumerator<T>::GetCurrent()
{
	if(p_current == nullptr)
	{
		throw std::out_of_range("ArrayEnumerator GetCurrent: out of range");
	}
	return *p_current;
}

template <typename T>
void ArrayEnumerator<T>::Reset()
{
	p_current = p_begin;
}


template <class T>
DynamicArray<T>::DynamicArray(T* items, size_t count)
{
	capacity_ = count;
	size_ = count;
	p_data_ = new T[capacity_]();
	for (size_t i = 0; i < count; ++i)
	{
		p_data_[i] = items[i];
	}
}

template <class T>
DynamicArray<T>::DynamicArray(size_t size)
{
	capacity_ = size;
	size_ = size;
	p_data_ = new T[capacity_]();
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamic_array)
{
	capacity_ = dynamic_array.capacity_;
	size_ = dynamic_array.size_;
	p_data_ = new T[capacity_]();
	for (size_t i = 0; i < size_; ++i)
	{
		p_data_[i] = dynamic_array.p_data_[i];
	}
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	size_ = other.size_;
	capacity_ = size_;
	p_data_ = new T[size_];
	for(int i = 0; i < size_; ++i)
	{
		p_data_[i] = other.p_data_[i];
	}
	return *this;
}

template <class T>
T DynamicArray<T>::Get(size_t index) const
{
	if (index >= size_)
	{
		throw std::out_of_range("DynamicArray Get: index out of range");
	}
	return p_data_[index];
}

template <class T>
size_t DynamicArray<T>::GetCount() const
{
	return size_;
}

template <class T>
void DynamicArray<T>::Set(size_t index, T value)
{
	if (index >= size_)
	{
		throw std::out_of_range("DynamicArray Set: index out of range");
	}
	p_data_[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(size_t new_size)
{
	if (new_size > capacity_)
	{
		// TODO
		if (capacity_ == 0)
		{
			capacity_ = 10;
		}
		while (new_size > capacity_)
		{
			capacity_ = (int)(capacity_ * growth_factor_);
		}
		T* old_p_data = p_data_;
		p_data_ = new T[capacity_]();
		for (size_t i = 0; i < size_; ++i)
		{
			p_data_[i] = old_p_data[i];
		}
		delete[] old_p_data;
	}
	if(new_size < size_)
	{
		for (size_t i = new_size; i < size_; ++i)
		{
			p_data_[i] = T{};
		}
	}
	size_ = new_size;
}

template <class T>
DynamicArray<T>* DynamicArray<T>::Slice(size_t start_index, size_t end_index) const
{
	if (size_ == 0)
	{
		throw std::out_of_range(
			"DynamicArray Slice: list is empty");
	}

	if (start_index >= size_)
	{
		throw std::out_of_range(
			"DynamicArray Slice: start_index out of range");
	}

	if (end_index >= size_)
	{
		throw std::out_of_range(
			"DynamicArray Slice: end_index out of range");
	}

	if (start_index > end_index)
	{
		throw std::out_of_range("DynamicArray Slice: "
			"end_index is less than start_index");
	}
	DynamicArray<T>* res = new DynamicArray(&p_data_[start_index], end_index - start_index + 1);
	return res;
}

template <class T>
IEnumerator<T>* DynamicArray<T>::GetEnumerator()
{
	return new ArrayEnumerator<T>(p_data_, p_data_ + size_);
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete[] p_data_;
}