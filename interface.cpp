#include "interface.h"
#include <complex>
#include "math_vector.h"
#include <iostream>
#include <vector>
#include "test_dynamic_array.h"
#include "test_linked_list.h"
#include "test_sequence.h"
#include "test_math_vector.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

vector<MathVector<int>> int_base{};
std::vector<MathVector<float>> float_base{};
std::vector<MathVector<complex<int>>> complex_base{};

int get_value()
{
	cout << "Enter number >> ";
	int value;
	cin >> value;
	return value;
}

template <typename T>
void print_vector(MathVector<T> v)
{
	cout << "{ ";
	for(size_t i = 0; i < v.GetDim(); ++i)
	{
		cout << v.GetAxisProject(i) << ' ';
	}
	cout << "}\n";
}

void show_vectors()
{
	if(!int_base.empty())
	{
		cout << "Vectors in INTEGER space:\n";
	}
	for(size_t i = 0; i < int_base.size(); ++ i)
	{
		cout << i << " : ";
		print_vector(int_base[i]);
	}

	if (!float_base.empty())
	{
		cout << "Vectors in FLOAT space:\n";
	}
	for (size_t i = 0; i < float_base.size(); ++i)
	{
		cout << i << " : ";
		print_vector(float_base[i]);
	}

	if (!complex_base.empty())
	{
		cout << "Vectors in COMPLEX space:\n";
	}
	for (size_t i = 0; i < complex_base.size(); ++i)
	{
		cout << i << " : ";
		print_vector(complex_base[i]);
	}
}

void delete_vector()
{
	show_vectors();
	cout << "What kind of vector do you want to delete?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 1 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	if (type == 3)
	{
		count = complex_base.size();
	}
	cout << "Choose vector number\n";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	switch(type)
	{
	case 1:
		int_base.erase(int_base.begin() + num);
		break;
	case 2:
		float_base.erase(float_base.begin() + num);
		break;
	case 3:
		complex_base.erase(complex_base.begin() + num);
		break;
	}
}

void print_hello()
{
	cout << "Hello! Let's test our class MathVector!\n";
}

int menu()
{
	cout << "MENU\n";
	cout << "1 : Create new vector\n";
	cout << "2 : Show vectors\n";
	cout << "3 : Delete vector\n";
	cout << "4 : Operations\n";
	cout << "5 : Launch tests\n";
	cout << "6 : End program\n";
	int res = get_value();
	while(res < 1 || res > 6)
	{
		cout << "You've written the wrong number!\n";
		res = get_value();
	}
	return res;
}

int operations_menu()
{
	cout << "OPERATIONS\n";
	cout << "1 : Sum\n";
	cout << "2 : Multiply with constant\n";
	cout << "3 : Get norm\n";
	cout << "4 : Scalar Product\n";
	cout << "5 : Go back to the MENU\n";
	int res = get_value();
	while (res < 1 || res > 5)
	{
		cout << "You've written the wrong number!\n";
		res = get_value();
	}
	return res;
}

void create_int_vector_auto(size_t dim)
{
	int tmp = 0;
	MathVector<int> v(dim);
	for(size_t i = 0; i < dim; ++i)
	{
		tmp = rand() % 50;
		v.SetAxisProject(i, tmp);
	}
	print_vector(v);
	int_base.push_back(v);
}

void create_float_vector_auto(size_t dim)
{
	int tmp = 0;
	MathVector<float> v(dim);
	for (size_t i = 0; i < dim; ++i)
	{
		tmp = 250 - rand() % 501;
		float t = tmp / 10.0;
		v.SetAxisProject(i, t);
	}
	print_vector(v);
	float_base.push_back(v);
}

void create_complex_vector_auto(size_t dim)
{
	int tmp1 = 0;
	int tmp2 = 0;
	MathVector<complex<int>> v(dim);
	for (size_t i = 0; i < dim; ++i)
	{
		tmp1 = rand() % 50;
		tmp2 = rand() % 50;
		complex<int> t(tmp1, tmp2);
		v.SetAxisProject(i, t);
	}
	print_vector(v);
	complex_base.push_back(v);
}

void create_int_vector_input(size_t dim)
{
	int tmp = 0;
	MathVector<int> v(dim);
	cout << "Enter coordinates:\n";
	for (size_t i = 0; i < dim; ++i)
	{
		cin >> tmp;
		v.SetAxisProject(i, tmp);
	}
	print_vector(v);
	int_base.push_back(v);
}

void create_float_vector_input(size_t dim)
{
	float tmp = 0.0;
	MathVector<float> v(dim);
	cout << "Enter coordinates:\n";
	for (size_t i = 0; i < dim; ++i)
	{
		cin >> tmp;
		v.SetAxisProject(i, tmp);
	}
	print_vector(v);
	float_base.push_back(v);
}

void create_complex_vector_input(size_t dim)
{
	int tmp1 = 0;
	int tmp2 = 0;
	MathVector<complex<int>> v(dim);
	cout << "Enter coordinates:\n";
	for (size_t i = 0; i < dim; ++i)
	{
		cin >> tmp1;
		cin >> tmp2;
		complex<int> t(tmp1, tmp2);
		v.SetAxisProject(i, t);
	}
	print_vector(v);
	complex_base.push_back(v);
}

void create_vector()
{
	cout << "Type of space\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 0 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}

	cout << "What about dimension? ";
	int dim = get_value();
	while (type < 0)
	{
		cout << "Dimension must be >= 0!\n";
		type = get_value();
	}
	
	cout << "Make it from...\n";
	cout << "1 : input\n";
	cout << "2 : +-random algorithm\n";
	int source = get_value();
	while (source < 0 || source > 2)
	{
		cout << "You've written the wrong number!\n";
		source = get_value();
	}
	
	switch(type)
	{
	case 1:
		if (source == 1) create_int_vector_input(dim);
		else create_int_vector_auto(dim);
		break;
	case 2:
		if (source == 1) create_float_vector_input(dim);
		else create_float_vector_auto(dim);
		break;
	case 3:
		if (source == 1) create_complex_vector_input(dim);
		else create_complex_vector_auto(dim);
		break;
	}
}

void sum_vectors()
{
	show_vectors();
	cout << "What kind of vector do you want to sum?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 1 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	if (type == 3)
	{
		count = complex_base.size();
	}
	cout << "Choose first vector number. ";
	int num1 = get_value();
	while (num1 < 0 || num1 >= count)
	{
		cout << "You've written the wrong number!\n";
		num1 = get_value();
	}
	cout << "Choose second vector number. ";
	int num2 = get_value();
	while (num2 < 0 || num2 >= count)
	{
		cout << "You've written the wrong number!\n";
		num2 = get_value();
	}

	cout << "Save result as vector?\n";
	cout << "1 : yes\n";
	cout << "2 : no\n";
	int save = get_value();
	while (save < 1 || save > 2)
	{
		cout << "You've written the wrong number!\n";
		save = get_value();
	}
	
	MathVector<int> v1;
	MathVector<float> v2;
	MathVector<complex<int>> v3;
	switch (type)
	{
	case 1:
		v1 = int_base[num1].Sum(int_base[num2]);
		print_vector(v1);
		if (save == 1)
		{
			int_base.push_back(v1);
		}
		break;
	case 2:
		v2 = float_base[num1].Sum(float_base[num2]);
		print_vector(v2);
		if (save == 1)
		{
			float_base.push_back(v2);
		}
		break;
	case 3:
		v3 = complex_base[num1].Sum(complex_base[num2]);
		print_vector(v3);
		if (save == 1)
		{
			complex_base.push_back(v3);
		}
		break;
	}
}

void multiply_vectors()
{
	show_vectors();
	cout << "What kind of vector do you want to multiply?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 1 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	if (type == 3)
	{
		count = complex_base.size();
	}
	cout << "Choose vector number. ";
	int num1 = get_value();
	while (num1 < 0 || num1 >= count)
	{
		cout << "You've written the wrong number!\n";
		num1 = get_value();
	}
	cout << "Give int constant to multiply with. ";
	int c = get_value();

	cout << "Save result as vector?\n";
	cout << "1 : yes\n";
	cout << "2 : no\n";
	int save = get_value();
	while (save < 1 || save > 2)
	{
		cout << "You've written the wrong number!\n";
		save = get_value();
	}

	MathVector<int> v1;
	MathVector<float> v2;
	MathVector<complex<int>> v3;
	
	switch (type)
	{
	case 1:
		v1 = int_base[num1].Multiply(c);
		print_vector(v1);
		if (save == 1)
		{
			int_base.push_back(v1);
		}
		break;
	case 2:
		v2 = float_base[num1].Multiply(c);
		print_vector(v2);
		if (save == 1)
		{
			float_base.push_back(v2);
		}
		break;
	case 3:
		v3 = complex_base[num1].Multiply(c);
		print_vector(v3);
		if (save == 1)
		{
			complex_base.push_back(v3);
		}
		break;
	}
}

void get_norm()
{
	show_vectors();
	cout << "What kind of vector you want to norm?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 1 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	if (type == 3)
	{
		count = complex_base.size();
	}
	cout << "Choose vector number. ";
	int num1 = get_value();
	while (num1 < 0 || num1 >= count)
	{
		cout << "You've written the wrong number!\n";
		num1 = get_value();
	}
	
	int n1;
	float n2;
	complex<int> n3;
	switch(type)
	{
	case 1:
		n1 = int_base[num1].Norm();
		cout << n1 << endl;
		break;
	case 2:
		n2 = float_base[num1].Norm();
		cout << n2 << endl;
		break;
	case 3:
		n3 = complex_base[num1].Norm();
		cout << n3 << endl;
		break;
	}
}

void product_vectors()
{
	show_vectors();
	cout << "What kind of vector do you want to product?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	cout << "3 : complex\n";
	int type = get_value();
	while (type < 1 || type > 3)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	if (type == 3)
	{
		count = complex_base.size();
	}
	cout << "Choose first vector number. ";
	int num1 = get_value();
	while (num1 < 0 || num1 >= count)
	{
		cout << "You've written the wrong number!\n";
		num1 = get_value();
	}
	cout << "Choose second vector number. ";
	int num2 = get_value();
	while (num2 < 0 || num2 >= count)
	{
		cout << "You've written the wrong number!\n";
		num2 = get_value();
	}

	int s1;
	float s2;
	complex<int> s3;
	switch (type)
	{
	case 1:
		s1 = int_base[num1].ScalarProduct(&int_base[num2]);
		cout << s1 << endl;
		break;
	case 2:
		s2 = float_base[num1].ScalarProduct(&float_base[num2]);
		cout << s2 << endl;
		break;
	case 3:
		s3 = complex_base[num1].ScalarProduct(&complex_base[num2]);
		cout << s3;
		break;
	}
}

void coroutine()
{
	srand(time(NULL));
	print_hello();
	cout << endl;
	int_base = vector<MathVector<int>>();
	float_base = vector<MathVector<float>>();
	complex_base = vector<MathVector<std::complex<int>>>();
	int menu_res = menu();
	while(menu_res != 6)
	{
		int op;
		switch (menu_res)
		{
		case 1: 
			create_vector();
			cout << endl;
			break;
		case 2:
			show_vectors();
			cout << endl;
			break;
		case 3:
			delete_vector();
			cout << endl;
			break;
		case 4:
			op = operations_menu();
			cout << endl;
			while(op != 5)
			{
				switch(op)
				{
				case 1:
					sum_vectors();
					cout << endl;
					break;
				case 2:
					multiply_vectors();
					cout << endl;
					break;
				case 3:
					get_norm();
					cout << endl;
					break;
				case 4:
					product_vectors();
					cout << endl;
					break;
				}
				op = operations_menu();
			}
			break;
		case 5:
			tests::dynamic_array::test_all();
			cout << "dynamic_array tests OK\n";
			tests::linked_list::test_all();
			cout << "linked_list tests OK\n";
			tests::sequence::linked_list_sequence::test_all();
			cout << "linked_list_sequence tests OK\n";
			tests::sequence::array_sequence::test_all();
			cout << "array_sequence tests OK\n";
			tests::math_vector::test_all();
			cout << "math_vector tests OK\n";
			break;
		}
		cout << endl;
		menu_res = menu();
		cout << endl;
		cout << "There are:\n";
		cout << int_base.size() << " int vectors\n";
		cout << float_base.size() << " float vectors\n";
		cout << complex_base.size() << " complex vectors\n";
		cout << endl;
	}
	
}
