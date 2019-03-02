#pragma once

#include<iterator>
#include<iostream>

using namespace std;

template<class T>
class List {
	template <class T>
	class Node;

	/*
	* LINK CLASS
	*/
	template <class T>
	class Link {
		friend class List<T>;
		Link* next, * prev;
	public:
		Node<T>* Next() { return static_cast<Node<T>*>(next); }
		Node<T>* Prev() { return static_cast<Node<T>*>(next); }
	};

	/*
	* NODE CLASS
	*/
	template<class T>
	class Node :Link<T> {
		friend class List<T>;
		T data;
	public:
		Node(const T& data)
		{
			this->data = data;
		}
	};

	/*
	* LIST ITER CLASS
	*/
	template<class T>
	class ListIter {
		Link<T>* ptr;
	};

public:
private:
	Link<T> _head;
};