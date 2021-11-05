//#include "interface.h"

#include <iostream>
#include "u_interface_sort.h"
#include "test_sequence.h"
#include "test_sort.h"

int main()
{
	tests::sequence::array_sequence::test_constructors();
	tests::sequence::linked_list_sequence::test_constructors();
	tests::sort::test_all();
	u_interface_sort::sort_interface();
}


// tester (generate tests, run)