#include "test_sequence.h"
#include "sequence.h"
#include <cassert>

namespace tests::sequence
{

namespace linked_list_sequence
{
	
void test_constructors()
{
	const Sequence<int>* s1 = new LinkedListSequence<int>();
	assert(s1->GetCount() == 0);

	double a[3] = { 1.2, 4.5, 1.3 };
	const Sequence<double>* s2 = new LinkedListSequence<double>(a, 3);
	assert(s2->GetCount() == 3);
	assert(abs(s2->GetFirst() - 1.2) < 0.00001);
	assert(abs(s2->Get(1) - 4.5) < 0.00001);
	assert(abs(s2->GetLast() - 1.3) < 0.00001);

	const Sequence<double>* s3 = new LinkedListSequence<double>(s2);
	assert(s2->GetCount() == 3);
	assert(abs(s2->GetFirst() - 1.2) < 0.00001);
	assert(abs(s2->Get(1) - 4.5) < 0.00001);
	assert(abs(s2->GetLast() - 1.3) < 0.00001);

	int b[5] = { 1,2,3,4,5 };
	Sequence<int>* s4 = new LinkedListSequence<int>(b, 5);
	Sequence<int>* s5 = s4->Copy(0, 3);
	assert(s5->GetCount() == 4);
	assert(s5->Get(0) == 1);
	assert(s5->Get(1) == 2);
	assert(s5->Get(2) == 3);
	assert(s5->Get(3) == 4);
	Sequence<int>* s6 = s4->Copy(0, 0);
	assert(s6->GetCount() == 0);
	
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete s6;
}

void test_get_set_subsequence()
{
	Sequence<int>* s1 = new LinkedListSequence<int>{};
	bool err = false;
	try
	{
		s1->GetFirst();
	}
	catch (std::exception& e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetFirst: sequence is empty") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->GetLast();
	}
	catch (std::exception& e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetLast: sequence is empty") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->Get(5);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence Get: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->InsertAt(4, 4);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence InsertAt: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->GetSubsequence(0,0);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetSubsequence: LinkedList GetSubList: list is empty") == 0);
	}
	assert(err);

	assert(s1->GetCount() == 0);			
	s1->Append(1);
	assert(s1->GetCount() == 1);
	assert(s1->GetFirst() == s1->GetLast());
	assert(s1->GetFirst() == 1);
	s1->Append(2);
	assert(s1->GetCount() == 2);
	assert(s1->Get(0) == 1);
	assert(s1->Get(1) == 2);
	s1->Prepend(3);
	assert(s1->GetCount() == 3);
	assert(s1->GetFirst() == 3);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->GetLast() == 2);
	
	err = false;
	try
	{
		s1->Get(3);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence Get: index out of range") == 0);
	}
	assert(err);

	s1->InsertAt(4, 3);
	assert(s1->GetCount() == 4);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->Get(3) == 4);

	s1->InsertAt(5, 3);
	assert(s1->GetCount() == 5);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->Get(3) == 5);
	assert(s1->Get(4) == 4);

	err = false;
	try
	{
		s1->InsertAt(6, 6);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence InsertAt: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(5, 4);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetSubsequence: LinkedList GetSubList: start_index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(1, 5);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetSubsequence: LinkedList GetSubList: end_index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(3, 0);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"LinkedListSequence GetSubsequence: LinkedList GetSubList: end_index is less than start_index") == 0);
	}
	assert(err);
	
	Sequence<int>* s2 = s1->GetSubsequence(0, 2);
	assert(s2->GetCount() == 3);
	assert(s2->Get(0) == 3);
	assert(s2->Get(1) == 1);
	assert(s2->Get(2) == 2);

	s2 = s1->GetSubsequence(3, 4);
	assert(s2->GetCount() == 2);
	assert(s2->Get(0) == 5);
	assert(s2->Get(1) == 4);

	s2 = s1->GetSubsequence(1, 3);
	assert(s2->GetCount() == 3);
	assert(s2->Get(0) == 1);
	assert(s2->Get(1) == 2);
	assert(s2->Get(2) == 5);
}

void test_concat()
{
	char a[] = "MECHANICAL";
	Sequence<char>* s1 = new LinkedListSequence<char>(a, 2);
	char b[] = "PHYSICS";
	Sequence<char>* s2 = new LinkedListSequence<char>(b, 2);
	char c[] = "INTELLIGENCE";
	Sequence<char>* s3 = new LinkedListSequence<char>(c, 1);

	assert(s1->GetCount() == 2);
	s1 = s1->Concat(s2);
	assert(s1->GetCount() == 4);
	s1 = s1->Concat(s3);
	assert(s1->GetCount() == 5);

	assert(s1->Get(0) == 'M');
	assert(s1->Get(1) == 'E');
	assert(s1->Get(2) == 'P');
	assert(s1->Get(3) == 'H');
	assert(s1->Get(4) == 'I');
}

void test_all()
{
	test_constructors();
	test_get_set_subsequence();
	test_concat();
}
}

namespace array_sequence
{
	
void test_constructors()
{

	const Sequence<int>* s1 = new ArraySequence<int>();
	assert(s1->GetCount() == 0);

	double a[3] = { 1.2, 4.5, 1.3 };
	const Sequence<double>* s2 = new ArraySequence<double>(a, 3);
	assert(s2->GetCount() == 3);
	assert(abs(s2->GetFirst() - 1.2) < 0.00001);
	assert(abs(s2->Get(1) - 4.5) < 0.00001);
	assert(abs(s2->GetLast() - 1.3) < 0.00001);

	const Sequence<double>* s3 = new ArraySequence<double>(s2);
	assert(s2->GetCount() == 3);
	assert(abs(s2->GetFirst() - 1.2) < 0.00001);
	assert(abs(s2->Get(1) - 4.5) < 0.00001);
	assert(abs(s2->GetLast() - 1.3) < 0.00001);

	int b[5] = { 1,2,3,4,5 };
	Sequence<int>* s4 = new ArraySequence<int>(b, 5);
	Sequence<int>* s5 = s4->Copy(0, 3);
	assert(s5->GetCount() == 4);
	assert(s5->Get(0) == 1);
	assert(s5->Get(1) == 2);
	assert(s5->Get(2) == 3);
	assert(s5->Get(3) == 4);
	Sequence<int>* s6 = s4->Copy(0, 0);
	assert(s6->GetCount() == 0);

	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete s6;
}
	
void test_get_set_subsequence()
{
	Sequence<int>* s1 = new ArraySequence<int>{};
	bool err = false;
	try
	{
		s1->GetFirst();
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetFirst: sequence is empty") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->GetLast();
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetLast: sequence is empty") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->Get(5);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence Get: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->InsertAt(4, 4);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence InsertAt: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		s1->GetSubsequence(0, 0);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetSubsequence: sequence is empty") == 0);
	}
	assert(err);

	assert(s1->GetCount() == 0);
	s1->Append(1);
	assert(s1->GetCount() == 1);
	assert(s1->GetFirst() == s1->GetLast());
	assert(s1->GetFirst() == 1);
	s1->Append(2);
	assert(s1->GetCount() == 2);
	assert(s1->Get(0) == 1);
	assert(s1->Get(1) == 2);
	s1->Prepend(3);
	assert(s1->GetCount() == 3);
	assert(s1->GetFirst() == 3);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->GetLast() == 2);

	err = false;
	try
	{
		s1->Get(3);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence Get: index out of range") == 0);
	}
	assert(err);

	s1->InsertAt(4, 3);
	assert(s1->GetCount() == 4);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->Get(3) == 4);

	s1->InsertAt(5, 3);
	assert(s1->GetCount() == 5);
	assert(s1->Get(0) == 3);
	assert(s1->Get(1) == 1);
	assert(s1->Get(2) == 2);
	assert(s1->Get(3) == 5);
	assert(s1->Get(4) == 4);

	err = false;
	try
	{
		s1->InsertAt(6, 6);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence InsertAt: index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(5, 4);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetSubsequence: start_index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(1, 5);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetSubsequence: end_index out of range") == 0);
	}
	assert(err);

	err = false;
	try
	{
		Sequence<int>* s2 = s1->GetSubsequence(3, 0);
	}
	catch (std::exception e)
	{
		err = true;
		assert(strcmp(e.what(),
			"ArraySequence GetSubsequence: end_index is less than start_index") == 0);
	}
	assert(err);

	Sequence<int>* s2 = s1->GetSubsequence(0, 2);
	assert(s2->GetCount() == 3);
	assert(s2->Get(0) == 3);
	assert(s2->Get(1) == 1);
	assert(s2->Get(2) == 2);

	s2 = s1->GetSubsequence(3, 4);
	assert(s2->GetCount() == 2);
	assert(s2->Get(0) == 5);
	assert(s2->Get(1) == 4);

	s2 = s1->GetSubsequence(1, 3);
	assert(s2->GetCount() == 3);
	assert(s2->Get(0) == 1);
	assert(s2->Get(1) == 2);
	assert(s2->Get(2) == 5);
}
void test_concat()
{
	char a[] = "MECHANICAL";
	Sequence<char>* s1 = new ArraySequence<char>(a, 2);
	char b[] = "PHYSICS";
	Sequence<char>* s2 = new ArraySequence<char>(b, 2);
	char c[] = "INTELLIGENCE";
	Sequence<char>* s3 = new ArraySequence<char>(c, 1);

	assert(s1->GetCount() == 2);
	s1 = s1->Concat(s2);
	assert(s1->GetCount() == 4);
	s1 = s1->Concat(s3);
	assert(s1->GetCount() == 5);

	assert(s1->Get(0) == 'M');
	assert(s1->Get(1) == 'E');
	assert(s1->Get(2) == 'P');
	assert(s1->Get(3) == 'H');
	assert(s1->Get(4) == 'I');
}
	
void test_all()
{
	test_constructors();
	test_get_set_subsequence();
	test_concat();
}
	
}

}