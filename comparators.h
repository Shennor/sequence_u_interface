#pragma once

inline int int_more(int a, int b) {
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

inline int char_more(char a, char b)
{
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

inline int int_less(int a, int b) {
	if (a < b) return 1;
	if (a > b) return -1;
	return 0;
}

inline int char_less(char a, char b)
{
	if (a < b) return 1;
	if (a > b) return -1;
	return 0;
}