#pragma once
#include "linked_list.h"

template <class T> class Sequence;
template <class T> class ArraySequence;

template <class T> class LinkedListSequence : public Sequence<T>
{
private:
	LinkedList<T> sequence_;
public:

	//Constructors

	LinkedListSequence(T* items, int count);
	LinkedListSequence();
	LinkedListSequence(const LinkedListSequence<T>& sequence);
	LinkedListSequence(const Sequence<T>* sequence);
	LinkedListSequence(const LinkedList<T>& list);

	// Decomposition

	T GetFirst() const override;
	T GetLast() const override;
	T Get(size_t index) const override;
	T Set(size_t index, T item) override;
	LinkedListSequence<T>* GetSubsequence(
		size_t start_index, size_t end_index) const override;
	size_t GetCount() const override;

	// Operators

	void Append(T item) override;
	void Prepend(T item) override;
	void InsertAt(T item, size_t index) override;
	Sequence<T>* Concat(Sequence<T>* sequence) override;
	Sequence<T>* Concat(ArraySequence<T>* sequence) override;
	Sequence<T>* Concat(LinkedListSequence<T>* sequence) override;
	
};

template <class T>
LinkedListSequence<T>::LinkedListSequence(T* items, int count)
{
	sequence_ = LinkedList<T>(items, count);
}

template <class T>
LinkedListSequence<T>::LinkedListSequence()
{
	sequence_ = LinkedList<T>();
}

template <class T>
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T>& sequence)
{
	sequence_ = sequence.sequence_;
}

template <class T>
LinkedListSequence<T>::LinkedListSequence(const Sequence<T>* sequence)
{
	for (auto i = sequence->GetCount() - 1; i <= 0; --i)
	{
		sequence_.Prepend(sequence->Get(i));
	}
}

template <class T>
LinkedListSequence<T>::LinkedListSequence(const LinkedList<T>& list)
{
	sequence_ = list;
}

template <class T>
T LinkedListSequence<T>::GetFirst() const
{
	try
	{
		return sequence_.GetFirst();
	}
	catch (std::exception e)
	{
		throw std::out_of_range(
			"LinkedListSequence GetFirst: sequence is empty");
	}
}

template <class T>
T LinkedListSequence<T>::GetLast() const
{
	try
	{
		return sequence_.GetLast();
	}
	catch (std::exception e)
	{
		throw std::out_of_range(
			"LinkedListSequence GetLast: sequence is empty");
	}
}

template <class T>
T LinkedListSequence<T>::Get(size_t index) const
{
	try
	{
		sequence_.Get(index);
	}
	catch (std::exception e)
	{
		throw std::out_of_range(
			"LinkedListSequence Get: index out of range");
	}
	return sequence_.Get(index);
}

template <class T>
T LinkedListSequence<T>::Set(size_t index, T item)
{
	try
	{
		sequence_.Set(index, item);
		return sequence_.Get(index);
	}
	catch (std::exception e)
	{
		throw std::out_of_range(
			"ArraySequence Set: index out of range");
	}
}

template <class T>
LinkedListSequence<T>* LinkedListSequence<T>::GetSubsequence(size_t start_index, size_t end_index) const
{
	try
	{
		return new LinkedListSequence<T>(sequence_.GetSubList(start_index, end_index));
	}
	catch (std::exception e)
	{
		std::string mes =
			"LinkedListSequence GetSubsequence: " + std::string(e.what());
		throw std::out_of_range(mes);
	}
}

template <class T>
size_t LinkedListSequence<T>::GetCount() const
{
	return sequence_.GetCount();
}

template <class T>
void LinkedListSequence<T>::Append(T item)
{
	sequence_.Append(item);
}

template <class T>
void LinkedListSequence<T>::Prepend(T item)
{
	sequence_.Prepend(item);
}

template <class T>
void LinkedListSequence<T>::InsertAt(T item, size_t index)
{
	try
	{
		sequence_.InsertAt(item, index);
	}
	catch (std::exception e)
	{
		throw std::out_of_range(
			"LinkedListSequence InsertAt: index out of range");
	}
}

template <class T>
Sequence<T>* LinkedListSequence<T>::Concat(Sequence<T>* sequence)
{
	return sequence->Concat(this);
}

template <class T>
Sequence<T>* LinkedListSequence<T>::Concat(ArraySequence<T>* sequence)
{
	for (size_t i = sequence_.GetCount() - 1; i >= 0; --i)
	{
		sequence->Prepend(sequence->Get(i));
	}
	return sequence;
}

template <class T>
Sequence<T>* LinkedListSequence<T>::Concat(LinkedListSequence<T>* sequence)
{
	return new LinkedListSequence(sequence->sequence_.Concat(sequence_));
}
