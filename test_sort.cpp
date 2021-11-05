#include "test_sort.h"
#include <cassert>
#include "sequence.h"
#include "sort_algorithms.h"
#include "comparators.h"

// ms 10000

namespace tests::sort
{

void test_merge()
{
	int a[10] = { 15, 1, 2, 4, 6, 1, 20, -2, -109, 0 };
	Sequence<int>* seq1 = new LinkedListSequence<int>(a, 0);
	SequenceSorter<int>::merge_sort(seq1, int_less, 0, 0);
	assert(seq1->GetCount() == 0);
	bool error = false;
	try {
		SequenceSorter<int>::merge_sort(seq1, int_less, 0, 1);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(),
			"SequenceSorter merge_sort: end out of range") == 0);
	}
	assert(error);
	Sequence<int>* seq2 = new LinkedListSequence<int>(a, 10);
	SequenceSorter<int>::merge_sort(seq2, int_less, 0, 2);
	assert(seq2->GetCount() == 10);
	assert(seq2->Get(0) == 15);
	assert(seq2->Get(1) == 2);
	assert(seq2->Get(2) == 1);
	assert(seq2->Get(3) == 4);
	assert(seq2->Get(4) == 6);
	assert(seq2->Get(5) == 1);
	assert(seq2->Get(6) == 20);
	assert(seq2->Get(7) == -2);
	assert(seq2->Get(8) == -109);
	assert(seq2->Get(9) == 0);

	SequenceSorter<int>::merge_sort(seq2, int_less, 0, 9);
	assert(seq2->GetCount() == 10);
	assert(seq2->Get(0) == 20);
	assert(seq2->Get(1) == 15);
	assert(seq2->Get(2) == 6);
	assert(seq2->Get(3) == 4);
	assert(seq2->Get(4) == 2);
	assert(seq2->Get(5) == 1);
	assert(seq2->Get(6) == 1);
	assert(seq2->Get(7) == 0);
	assert(seq2->Get(8) == -2);
	assert(seq2->Get(9) == -109);

	error = false;
	try {
		SequenceSorter<int>::merge_sort(seq2, int_less, 6, 2);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(),
			"SequenceSorter merge_sort: begin is bigger then end") == 0);
	}
	assert(error);

	char b[5] = { 'b', 'c', 'e', 'd', 'a' };
	Sequence<char>* seq3 = new ArraySequence<char>(b, 5);
	SequenceSorter<char>::merge_sort(seq3, char_less, 0, 4);
	assert(seq3->GetCount() == 5);
	assert(seq3->Get(0) == 'e');
	assert(seq3->Get(1) == 'd');
	assert(seq3->Get(2) == 'c');
	assert(seq3->Get(3) == 'b');
	assert(seq3->Get(4) == 'a');

	delete seq1;
	delete seq2;
	delete seq3;
}

void test_binary_insertion()
{
	int a[10] = { 15, 1, 2, 4, 6, 1, 20, -2, -109, 0 };
	Sequence<int>* seq1 = new ArraySequence<int>(a, 0);
	SequenceSorter<int>::binary_insertion(seq1, int_less, 0, 0);
	assert(seq1->GetCount() == 0);
	bool error = false;
	try {
		SequenceSorter<int>::binary_insertion(seq1, int_less, 0, 1);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(),
			"SequenceSorter binary_insertion: end out of range") == 0);
	}
	assert(error);
	Sequence<int>* seq2 = new ArraySequence<int>(a, 10);
	SequenceSorter<int>::binary_insertion(seq2, int_less, 0, 2);
	assert(seq2->GetCount() == 10);
	assert(seq2->Get(0) == 15);
	assert(seq2->Get(1) == 2);
	assert(seq2->Get(2) == 1);
	assert(seq2->Get(3) == 4);
	assert(seq2->Get(4) == 6);
	assert(seq2->Get(5) == 1);
	assert(seq2->Get(6) == 20);
	assert(seq2->Get(7) == -2);
	assert(seq2->Get(8) == -109);
	assert(seq2->Get(9) == 0);

	SequenceSorter<int>::binary_insertion(seq2, int_less, 0, 9);
	assert(seq2->GetCount() == 10);
	assert(seq2->Get(0) == 20);
	assert(seq2->Get(1) == 15);
	assert(seq2->Get(2) == 6);
	assert(seq2->Get(3) == 4);
	assert(seq2->Get(4) == 2);
	assert(seq2->Get(5) == 1);
	assert(seq2->Get(6) == 1);
	assert(seq2->Get(7) == 0);
	assert(seq2->Get(8) == -2);
	assert(seq2->Get(9) == -109);

	error = false;
	try {
		SequenceSorter<int>::binary_insertion(seq2, int_less, 6, 2);
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(),
			"SequenceSorter binary_insertion: begin is bigger then end") == 0);
	}
	assert(error);

	char b[5] = { 'b', 'c', 'e', 'd', 'a' };
	Sequence<char>* seq3 = new LinkedListSequence<char>(b, 5);
	SequenceSorter<char>::binary_insertion(seq3, char_less, 0, 4);
	assert(seq3->GetCount() == 5);
	assert(seq3->Get(0) == 'e');
	assert(seq3->Get(1) == 'd');
	assert(seq3->Get(2) == 'c');
	assert(seq3->Get(3) == 'b');
	assert(seq3->Get(4) == 'a');

	delete seq1;
	delete seq2;
	delete seq3;
}

void test_all()
{
	test_merge(); 
	test_binary_insertion();
}
}
