#ifndef LIST
#define LIST

#include<iterator>
#include<iostream>

using namespace std;

template<class T>
class List
{
	template<class T>
	class Node;

	template<class T>
	class Link
	{
		friend class List<T>;
	public:
		Link();
		~Link();

		Node<T> * getNext()
		{
			return next;
		}

		Node<T> * getPrev()
		{
			return prev;
		}

		void setPrev(Node<T> prev)
		{
			this->prev = prev;
		}

		void setNext(Node<T> next)
		{
			this->next = next;
		}

	private:
		Node<T> * next;
		Node<T> * prev;
	};

	template<class T>
	class Node
	{
		friend class List<T>;
	public:
		Node();
		~Node();

		Node(T value)
		{
			this->value = T;
		}

		void setValue(T value)
		{
			this->value = value;
		}

		T getValue()
		{
			return value;
		}

		Link<T> getLink()
		{
			return link;
		}

		void print()
		{
			cout << "(n: " << list.getNext() << " | p: " << link.getPrev() << " | v: " << value << ")" << endl;
		}
	private:
		T value;

		Link<T> link;
	};

	template<class T>
	class ListIter
	{
	public:
		using iterator_category = bidirectional_iterator_tag;

		ListIter();
		~ListIter();

		ListIter(Node<T>* p)
		{
			
		}

		ListIter(const ListIter& other)
		{

		}

		ListIter& operator=(const ListIter& other)
		{
			
		}

		T & operator*()
		{

		}

		T* operator->()
		{

		}

		ListIter& operator++()
		{

		}

		ListIter& operator--()
		{

		}

		ListIter operator++(int)
		{

		}

		ListIter operator--(int)
		{

		}

		friend bool operator==(const ListIter& lhs, const ListIter& rhs)
		{

		}

		friend bool operator!=(const ListIter& lhs, const ListIter& rhs)		{

		}
	private:
		Link<T> * link;
	};
	using iterator = ListIter < T >;
public:
	List();
	~List();
private:
	Link<T> head;
};


#endif