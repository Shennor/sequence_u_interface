#pragma once
#include "array_sequence.h"
#include "linked_list_sequence.h"

template <class T> class Sequence
{
public:
	// Decomposition
	
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(size_t index) const = 0;
	virtual T Set(size_t index, T item) = 0;

	virtual Sequence* GetSubsequence( 
		size_t start_index, size_t end_index) const= 0;
	
	virtual size_t GetCount() const = 0;

	// Operators

	virtual void Append(T item)= 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, size_t index) = 0;
	virtual void DeleteAt(size_t index) = 0;
	virtual void Swap(size_t first_index, size_t second_index) = 0;

	virtual Sequence<T>* Concat(Sequence <T>* sequence) = 0;
	virtual Sequence<T>* Concat(ArraySequence <T>* sequence) = 0;
	virtual Sequence<T>* Concat(LinkedListSequence <T>* sequence) = 0;
	
	virtual ~Sequence() = default;

	virtual Sequence<T>* Copy(size_t begin, size_t end) = 0;
};