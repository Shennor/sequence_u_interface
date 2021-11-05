#include "u_interface_sort.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include "comparators.h"
#include "test_sort.h"
#include "sort_algorithms.h"
#include "u_interface_utils.h"
using namespace std;

namespace u_interface_sort
{

	Sequence<int>* random_sequence(size_t num_elements, bool is_linked_list)
	{
		Sequence<int>* res;
		if (is_linked_list)
			res = new LinkedListSequence<int>{};
		else
			res = new ArraySequence<int>{};
		for (size_t i = 0; i < num_elements; ++i)
		{
			res->Append(rand() - RAND_MAX / 2);
		}
		return res;
	}

	Sequence<int>* input_sequence(size_t num_elements, bool is_linked_list)
	{
		Sequence<int>* res;
		if (is_linked_list)
			res = new LinkedListSequence<int>{};
		else
			res = new ArraySequence<int>{};
		for (size_t i = 0; i < num_elements; ++i)
		{
			int tmp;
			cin >> tmp;
			res->Append(tmp);
		}
		return res;
	}

	template <class T>
	void print_sequence(Sequence<T>* seq)
	{
		for (int i = 0; i < seq->GetCount(); ++i)
		{
			cout << seq->Get(i);
			cout << " ";
		}
		cout << endl;
	}

	// in ms
	unsigned long long sort_time_test(size_t num_elements, bool is_linked_list, 
		Sequence<int>* (*sort)(Sequence<int>* sequence, int (*cmp)(int, int), size_t begin, size_t end))
	{
		Sequence<int>* seq = random_sequence(num_elements, is_linked_list);
		auto start = std::chrono::high_resolution_clock::now();
		sort(seq, int_more, 0, seq->GetCount() - 1);
		auto finish = std::chrono::high_resolution_clock::now();
		auto result = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
		delete seq;
		return result / 1000000;
	}

	int menu()
	{
		cout << "MENU\n";
		cout << "1 : Launch automatic tests\n";
		cout << "2 : Test by hand\n";
		cout << "3 : Time tests\n";
		cout << "4 : End program\n";
		int res = get_value();
		while (res < 1 || res > 4)
		{
			cout << "You've written the wrong number!\n";
			res = get_value();
		}
		return res;
	}

	void test_by_hand()
	{
		cout << "Choose sequence type:\n";
		cout << "0 : ArraySequence\n";
		cout << "1 : LinkedListSequence\nEnter >> ";
		bool is_linked_list;
		cin >> is_linked_list;
		cout << "Enter number of elements:\n";
		size_t num_elements;
		cin >> num_elements;
		cout << "Elements from:\n";
		cout << "1 : Random int value\n";
		cout << "2 : Input\n";
		int res = get_value();
		while (res < 1 || res > 2)
		{
			cout << "You've written the wrong number!\n";
			res = get_value();
		}
		Sequence<int>* seq;
		if (res == 1)
		{
			seq = random_sequence(num_elements, is_linked_list);
		}
		else
		{
			seq = input_sequence(num_elements, is_linked_list);
		}
		print_sequence(seq);
		cout << "Which type of sort:\n";
		cout << "1 : Merge sort\n";
		cout << "2 : Binary insertion\n";
		res = get_value();
		while (res < 1 || res > 2)
		{
			cout << "You've written the wrong number!\n";
			res = get_value();
		}
		if (res == 1)
		{
			SequenceSorter<int>::merge_sort(seq, int_more, 0, seq->GetCount() - 1);
		}
		else
		{
			SequenceSorter<int>::binary_insertion(seq, int_more, 0, seq->GetCount() - 1);
		}
		print_sequence(seq);
		delete seq;
	}

	void sort_interface()
	{
		srand(time(NULL));
		cout << "Welcome to Sort Tester User Interface.\n";
		int menu_res = menu();
		while (menu_res != 4)
		{
			switch (menu_res)
			{
			case 1:
				tests::sort::test_all();
				cout << "Tests are OK\n";
				break;
			case 2:
				test_by_hand();
				break;
			default:
				cout << "Enter number of elements to test:\n";
				size_t num;
				cin >> num;
				unsigned long long lls_merge = sort_time_test(num, true, SequenceSorter<int>::merge_sort);
				unsigned long long as_merge = sort_time_test(num, false, SequenceSorter<int>::merge_sort);
				unsigned long long lls_b_insert = sort_time_test(num, true, SequenceSorter<int>::binary_insertion);
				unsigned long long as_b_insert = sort_time_test(num, false, SequenceSorter<int>::binary_insertion);
				cout << setw(20) << "" << setw(13) << "merge sort" << setw(23) << "binary insertion sort\n";
				cout << setw(20) << "Linked List Sequence" << setw(13) << lls_merge << setw(23) << lls_b_insert << endl;
				cout << setw(20) << "Array Sequence" << setw(13) << lls_merge << setw(23) << lls_b_insert << endl;
				break;
			}
			cout << endl;
			menu_res = menu();
			cout << endl;
		}
	}
}