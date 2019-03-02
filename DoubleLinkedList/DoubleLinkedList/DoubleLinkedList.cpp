// DoubleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	List<char> l = List<char>();
	l.push_front('x');
	l.print();
	cin.get();
	return 0;
}

