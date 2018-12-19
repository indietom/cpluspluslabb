// DoubleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"

int _tmain(int argc, _TCHAR* argv[])
{
	List<char> l = List<char>();
	l.push_front('x');
	return 0;
}

