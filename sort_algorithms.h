#pragma once
#include "sequence.h"

template <class T>
class SequenceSorter
{
public:
	static Sequence<T>* merge_sort(Sequence<T>* sequence, int (*cmp)(T, T),
		size_t begin, size_t end);
	static Sequence<T>* binary_insertion(Sequence<T>* sequence, int (*cmp)(T, T),
		size_t begin, size_t end);
	//static Sequence<T>* merge_sort(Sequence<T>* sequence, int (*cmp)(T, T));
	//static Sequence<T>* binary_insertion(Sequence<T>* sequence, int (*cmp)(T, T));
};

template <class T>
Sequence<T>* merge(Sequence<T>* sequence, int(*cmp)(T, T), size_t begin, size_t middle, size_t end)
{
	Sequence<T>* seq_copy = sequence->Copy(begin, end);
	
	size_t insert_i = begin;
	size_t first_i = 0;
	size_t second_i = middle - begin + 1;
	while (first_i <= middle - begin && second_i <= end - begin)
	{
		T f = seq_copy->Get(first_i);
		T s = seq_copy->Get(second_i);
		if (cmp(f, s) < 0)
		{
			sequence->Set(insert_i++, f);
			first_i++;
		}
		else
		{
			sequence->Set(insert_i++, s);
			second_i++;
		}
	}
	while (first_i <= middle - begin)
	{
		sequence->Set(insert_i++, seq_copy->Get(first_i++));
	}
	while (second_i <= end - begin)
	{
		sequence->Set(insert_i++, seq_copy->Get(second_i++));
	}
	delete seq_copy;
	return sequence;
}

template <class T>
Sequence<T>* SequenceSorter<T>::merge_sort(Sequence<T>* sequence, int(* cmp)(T, T), size_t begin, size_t end)
{
	if (end - begin < 1) return sequence;
	if (end >= sequence->GetCount())
	{
		throw std::out_of_range(
			"SequenceSorter merge_sort: end out of range");
	}
	if (begin > end)
	{
		throw std::out_of_range(
			"SequenceSorter merge_sort: begin is bigger then end");
	}
	size_t middle = (begin + end) / 2;
	merge_sort(sequence, cmp, begin, middle);
	merge_sort(sequence, cmp, middle + 1, end);
	return merge(sequence, cmp, begin, middle, end);
}

template<class T>
size_t binary_search(Sequence<T>* sequence, 
	int (*cmp)(T, T), T element, size_t begin, size_t end)
{
	if (end <= begin) return
		(cmp(element, sequence->Get(begin)) >= 0) ? (begin + 1) : begin;
	size_t middle = begin + (end - begin) / 2;
	if (cmp(element, sequence->Get(middle)) == 0) return middle + 1;
	if (cmp(element, sequence->Get(middle)) > 0)
		return binary_search(sequence, cmp, element, middle + 1, end);
	return binary_search(sequence, cmp, element, begin, middle);
}

template <class T>
Sequence<T>* SequenceSorter<T>::binary_insertion(Sequence<T>* sequence, int(* cmp)(T, T),
	size_t begin, size_t end)
{
	if (end - begin < 1) return sequence;
	if (end >= sequence->GetCount())
	{
		throw std::out_of_range(
			"SequenceSorter binary_insertion: end out of range");
	}
	if (begin > end)
	{
		throw std::out_of_range(
			"SequenceSorter binary_insertion: begin is bigger than end");
	}
	for(size_t index = begin + 1; index <= end; ++index)
	{
		T element = sequence->Get(index);
		sequence->DeleteAt(index);
		sequence->InsertAt(element, 
			binary_search(sequence, cmp, element, begin, index - 1));
	}
	return sequence;
}
