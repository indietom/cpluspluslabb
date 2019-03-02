// Labb3meta.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

size_t AddFun(size_t x, size_t y) {
	if (x == 0)
		return y;
	else
		return AddFun(x - 1, y + 1);
}

template <size_t X, size_t Y>
struct Add {
	static const size_t value = Add<X - 1, Y + 1>::value;
};

template <> //typename std::enable_if<X>::type = 0
struct Add<X, Y> {
	static const size_t value = Y;
};

int main()
{
	cout << Add<19, 4>::value << endl;
    return 0;
}

