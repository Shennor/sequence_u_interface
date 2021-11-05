#include "test_dynamic_array.h"
#include "dynamic_array.h"
#include <cassert>
#include <string>
#include <exception>

namespace tests::dynamic_array
{

void test_constructors()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	DynamicArray<int> first(a, 5);
	assert(first.GetCount() == 5);
	assert(first.Get(0) == 1);
	assert(first.Get(1) == 2);
	assert(first.Get(2) == 3);
	assert(first.Get(3) == 4);
	assert(first.Get(4) == 5);

	char c[3] = { 'a', 'd', 's' };
	DynamicArray<char> other(c, 2);
	assert(other.GetCount() == 2);
	assert(other.Get(0) == 'a');
	assert(other.Get(1) == 'd');

	double b[2] = { 3.34, 5.345 };
	double eps = 0.000000001;
	DynamicArray<double> another(b, 2);
	assert(another.GetCount() == 2);
	assert(another.Get(0) - 3.34 < eps);
	assert(another.Get(1) - 5.345 < eps);

	DynamicArray<std::string> second(3);
	assert(second.GetCount() == 3);

	DynamicArray<int> same(2);
	assert(same.Get(0) == 0);
	assert(same.Get(1) == 0);

	DynamicArray<int> third(first);
	assert(third.GetCount() == 5);
	assert(third.Get(0) == 1);
	assert(third.Get(1) == 2);
	assert(third.Get(2) == 3);
	assert(third.Get(3) == 4);
	assert(third.Get(4) == 5);
}

void test_set_get()
{
	DynamicArray<int> v(3);
	v.Set(0, 4);
	v.Set(1, 234);
	v.Set(2, 5);
	assert(v.Get(0) == 4);
	assert(v.Get(1) == 234);
	assert(v.Get(2) == 5);

	bool ex = false;
	try
	{
		v.Set(3, 6);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "DynamicArray Set: index out of range") == 0);
	}
	assert(ex);

	ex = false;
	try
	{
		v.Get(3);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "DynamicArray Get: index out of range") == 0);
	}
	assert(ex);
}

void test_resize()
{
	DynamicArray<int> v(3);
	v.Set(0, 567);
	v.Set(1, 4502);
	v.Set(2, 1840);
	assert(v.GetCount() == 3);

	v.Resize(4);
	assert(v.GetCount() == 4);
	assert(v.Get(0) == 567);
	assert(v.Get(1) == 4502);
	assert(v.Get(2) == 1840);
	assert(v.Get(3) == 0);

	v.Resize(2);
	assert(v.GetCount() == 2);
	assert(v.Get(0) == 567);
	assert(v.Get(1) == 4502);

	v.Resize(4);
	assert(v.GetCount() == 4);
	assert(v.Get(0) == 567);
	assert(v.Get(1) == 4502);
	assert(v.Get(2) == 0);
	assert(v.Get(3) == 0);
}

void test_delete_at()
{
	DynamicArray<int> v(3);
	v.Set(0, 1);
	v.Set(1, 2);
	v.Set(2, 3);
	v.Set(3, 4);
	v.Set(4, 5);
	bool ex = false;
	try
	{
		v.DeleteAt(6);
	}
	catch (std::exception e)
	{
		ex = true;
		assert(strcmp(e.what(), "DynamicArray DeleteAt: index out of range") == 0);
	}
	assert(ex);
	v.DeleteAt(2);
	assert(v.GetCount() == 4);
	assert(v.Get(0) == 1);
	assert(v.Get(1) == 2);
	assert(v.Get(2) == 4);
	assert(v.Get(3) == 5);
	v.DeleteAt(0);
	assert(v.GetCount() == 3);
	assert(v.Get(0) == 2);
	assert(v.Get(1) == 4);
	assert(v.Get(2) == 5);
	v.DeleteAt(2);
	assert(v.GetCount() == 2);
	assert(v.Get(0) == 2);
	assert(v.Get(1) == 4);
}
	
void test_enumerator()
{
	char a[7] = "Mother";
	DynamicArray<char> first(a, 4);
	IEnumerator<char>* i = first.GetEnumerator();
	assert(i->GetCurrent() == 'M');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 'o');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 't');
	assert(i->MoveNext());
	assert(i->GetCurrent() == 'h');
	assert(i->MoveNext() == false);

	DynamicArray<int> second{};
	IEnumerator<int>* j = second.GetEnumerator();
	bool error = false;
	try
	{
		j->GetCurrent();
	}
	catch (std::exception& e)
	{
		error = true;
	}
	assert(error);
	assert(j->MoveNext() == false);
}

void test_collection()
{
	int a[4] = { 1, 3, 5, 8 };
	ICollection<int>* v = new DynamicArray<int>(a, 4);
	assert(v->GetCount() == 4);
	assert(v->Get(0) == 1);
	assert(v->Get(1) == 3);
	assert(v->Get(2) == 5);
	assert(v->Get(3) == 8);
}
	
void test_all()
{
	test_constructors();
	test_set_get();
	test_resize();
	test_enumerator();
	test_collection();
}

}