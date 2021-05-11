#pragma once
#include "dynamic_array.h"

template <class T> class Sequence;
template <class T> class LinkedListSequence;

template <class T> class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T> sequence_;
public:
	//Constructors
	
	ArraySequence(T* items, int count);
	ArraySequence();
	ArraySequence(size_t size);
	ArraySequence(const ArraySequence<T>& sequence);
	ArraySequence(const Sequence<T>* sequence);
	ArraySequence(const DynamicArray<T>& array);

	// Decomposition

	T GetFirst() const override;
	T GetLast() const override;
	T Get(size_t index) const override;
	T Set(size_t index, T item) override;
	ArraySequence<T>* GetSubsequence(
		size_t start_index, size_t end_index) const override;
	size_t GetCount() const override;

	// Operators

	void Append(T item) override;
	void Prepend(T item) override;
	void InsertAt(T item, size_t index) override;
	Sequence<T>* Concat(Sequence<T>* sequence) override;
	Sequence<T>* Concat(ArraySequence<T>* sequence);
	Sequence<T>* Concat(LinkedListSequence<T>* sequence);
};

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count)
{
	sequence_ = DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence()
{
	sequence_ = DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(size_t size)
{
	sequence_ = DynamicArray<T>(size);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& sequence)
{
	sequence_ = DynamicArray<T>(sequence.sequence_);
}

template <class T>
ArraySequence<T>::ArraySequence(const Sequence<T>* sequence)
{
	sequence_.Resize(sequence->GetCount());
	for (size_t i = 0; i < sequence->GetCount(); ++i)
	{
		sequence_.Set(i, sequence->Get(i)); //TODO:		
	}
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& array)
{
	sequence_ = array;
}

template <class T>
T ArraySequence<T>::GetFirst() const
{
	if (sequence_.GetCount() == 0)
	{
		throw std::out_of_range("ArraySequence GetFirst: sequence is empty");
	}
	return sequence_.Get(0);
}

template <class T>
T ArraySequence<T>::GetLast() const
{
	if (sequence_.GetCount() == 0)
	{
		throw std::out_of_range("ArraySequence GetLast: sequence is empty");
	}
	return sequence_.Get(sequence_.GetCount() - 1);
}

template <class T>
T ArraySequence<T>::Get(size_t index) const
{
	try
	{
		return sequence_.Get(index);
	}
	catch (std::exception& e)
	{
		throw std::out_of_range(
			"ArraySequence Get: index out of range");
	}
}

template <class T>
T ArraySequence<T>::Set(size_t index, T item)
{
	try
	{
		sequence_.Set(index, item);
		return sequence_.Get(index);
	}
	catch (std::exception& e)
	{
		throw std::out_of_range(
			"ArraySequence Set: index out of range");
	}
}

template <class T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(size_t start_index, size_t end_index) const
{
	if (sequence_.GetCount() == 0)
	{
		throw std::out_of_range(
			"ArraySequence GetSubsequence: sequence is empty");
	}

	if (start_index >= sequence_.GetCount())
	{
		throw std::out_of_range(
			"ArraySequence GetSubsequence: start_index out of range");
	}

	if (end_index >= sequence_.GetCount())
	{
		throw std::out_of_range(
			"ArraySequence GetSubsequence: end_index out of range");
	}

	if (start_index > end_index)
	{
		throw std::out_of_range("ArraySequence GetSubsequence: "
			"end_index is less than start_index");
	}

	auto tmp = sequence_.Slice(start_index, end_index);
	return new ArraySequence<T>(*tmp);
}

template <class T>
size_t ArraySequence<T>::GetCount() const
{
	return sequence_.GetCount();
}

template <class T>
void ArraySequence<T>::Append(T item)
{
	InsertAt(item, sequence_.GetCount());
}

template <class T>
void ArraySequence<T>::Prepend(T item)
{
	InsertAt(item, 0);
}

template <class T>
void ArraySequence<T>::InsertAt(T item, size_t index)
{
	if (index > sequence_.GetCount())
	{
		throw std::out_of_range(
			"ArraySequence InsertAt: index out of range");
	}
	sequence_.Resize(sequence_.GetCount() + 1);
	for (size_t i = sequence_.GetCount() - 1; i > index; --i)
	{
		sequence_.Set(i, sequence_.Get(i - 1));
	}
	sequence_.Set(index, item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* sequence)
{
	return sequence->Concat(this);
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(ArraySequence<T>* sequence)
{
	for (size_t i = 0; i < sequence_.GetCount(); ++i)
	{
		sequence->Append(sequence_.Get(i));
	}
	return sequence;
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(LinkedListSequence<T>* sequence)
{
	for (size_t i = 0; i < sequence_.GetCount(); ++i)
	{
		sequence->Append(sequence_.Get(i));
	}
	return sequence;
}