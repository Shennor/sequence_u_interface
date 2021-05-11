#include "test_linked_list.h"
#include <cassert>
#include "linked_list.h"
#include <exception>
#include <string>

namespace tests::linked_list
{

void test_constructors()
{
	const char* a = "Mother";
	LinkedList<char> first(a, 4);
	assert(first.GetCount() == 4);
	assert(first.Get(0) == 'M');
	assert(first.Get(1) == 'o');
	assert(first.Get(2) == 't');
	assert(first.Get(3) == 'h');

	LinkedList<int> empty{};
	assert(empty.GetCount() == 0);

	LinkedList<char> clone(first);
	assert(clone.GetCount() == 4);
	assert(clone.Get(0) == 'M');
	assert(clone.Get(1) == 'o');
	assert(clone.Get(2) == 't');
	assert(clone.Get(3) == 'h');
}

void test_get_elements()
{
	LinkedList<std::string> empty{};
	bool ex = false;
	try
	{
		empty.Get(3);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList Get: index out of range") == 0);
	}
	assert(ex);

	ex = false;
	try
	{
		empty.GetFirst();
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetFirst: list is empty") == 0);
	}
	assert(ex);

	ex = false;
	try
	{
		empty.GetLast();
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetLast: "
			"list is empty") == 0);
	}
	assert(ex);

	const char* a = "Mother";
	LinkedList<char> first(a, 6);
	assert(first.GetCount() == 6);
	assert(first.GetFirst() == 'M');
	assert(first.Get(2) == 't');
	assert(first.GetLast() == 'r');
	ex = false;
	try
	{
		first.Get(6);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList Get: "
			"index out of range") == 0);
	}
	assert(ex);
}

void test_get_sublist()
{
	LinkedList<std::string> empty{};
	bool ex = false;
	try
	{
		empty.GetSubList(5, 1);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetSubList: "
			"list is empty") == 0);
	}
	assert(ex);

	const char* a = "Mother";
	LinkedList<char> first(a, 6);
	ex = false;
	try
	{
		first.GetSubList(6, 1);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetSubList: "
			"start_index out of range") == 0);
	}
	assert(ex);

	ex = false;
	try
	{
		first.GetSubList(3, 6);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetSubList: "
			"end_index out of range") == 0);
	}
	assert(ex);

	ex = false;
	try
	{
		first.GetSubList(3, 1);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList GetSubList: "
			"end_index is less than start_index") == 0);
	}
	assert(ex);

	LinkedList<char> sublist{ first.GetSubList(0, 2) };
	assert(sublist.GetCount() == 3);
	assert(sublist.Get(0) == 'M');
	assert(sublist.Get(1) == 'o');
	assert(sublist.Get(2) == 't');

	sublist = first.GetSubList(4, 5);
	assert(sublist.GetCount() == 2);
	assert(sublist.Get(0) == 'e');
	assert(sublist.Get(1) == 'r');

	sublist = first.GetSubList(2, 4);
	assert(sublist.GetCount() == 3);
	assert(sublist.Get(0) == 't');
	assert(sublist.Get(1) == 'h');
	assert(sublist.Get(2) == 'e');
}

void test_set()
{
	LinkedList<int> v{};
	bool ex = false;
	try
	{
		v.InsertAt(5, 4);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "LinkedList InsertAt: index out of range") == 0);
	}
	assert(ex);
	assert(v.GetCount() == 0);
	v.InsertAt(1, 0);
	assert(v.GetCount() == 1);
	assert(v.GetFirst() == 1);
	v.Prepend(2);
	assert(v.GetCount() == 2);
	assert(v.GetFirst() == 2);
	assert(v.GetLast() == 1);
	v.Append(3);
	assert(v.GetCount() == 3);
	assert(v.Get(0) == 2);
	assert(v.Get(1) == 1);
	assert(v.Get(2) == 3);
}

void test_concat()
{
	LinkedList<char> s1{ "MECHANICAL", 2 };
	LinkedList<char> s2{ "PHYSICS", 2 };
	LinkedList<char> s3{ "INTELLIGENCE", 1 };

	assert(s1.GetCount() == 2);
	s1 = s1.Concat(s2);
	assert(s1.GetCount() == 4);
	s1 = s1.Concat(s3);
	assert(s1.GetCount() == 5);

	assert(s1.Get(0) == 'M');
	assert(s1.Get(1) == 'E');
	assert(s1.Get(2) == 'P');
	assert(s1.Get(3) == 'H');
	assert(s1.Get(4) == 'I');
}

void test_enumerator()
{
	const char* a = "Mother";
	LinkedList<char> first(a, 4);
	IEnumerator<char>* i = first.GetEnumerator();
	assert(i->GetCurrent() == 'M');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 'o');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 't');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 'h');
	assert(i->MoveNext() == false);

	LinkedList<int> second{};
	IEnumerator<int>* j = second.GetEnumerator();
	bool error = false;
	try
	{
		j->GetCurrent();
	}
	catch(std::exception& e)
	{
		error = true;
	}
	assert(error);
	assert(j->MoveNext() == false);
}

void test_collection()
{
	int a[4] = { 1, 3, 5, 8 };
	ICollection<int>* v = new LinkedList<int>(a, 4);
	assert(v->GetCount() == 4);
	assert(v->Get(0) == 1);
	assert(v->Get(1) == 3);
	assert(v->Get(2) == 5);
	assert(v->Get(3) == 8);
}
	
void test_all()
{
	test_constructors();
	test_get_elements();
	test_get_sublist();
	test_set();
	test_concat();
	test_enumerator();
	test_collection();
}

}