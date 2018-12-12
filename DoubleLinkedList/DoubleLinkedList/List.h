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

		void setPrev(Node<T> * prev)
		{
			this->prev = prev;
		}

		void setNext(Node<T> * next)
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

		Link<T> * getLink()
		{
			return link;
		}

		void print()
		{
			cout << "(n: " << list->getNext() << " | p: " << link->getPrev() << " | v: " << value << ")" << endl;
		}
	private:
		T value;

		Link<T> * link;
	};

	template<class T>
	class ListIter
	{
	public:
		using iterator_category = bidirectional_iterator_tag;

		ListIter();
		~ListIter();

		ListIter(Node<T> * p)
		{
			link = p->getLink();
		}

		ListIter(const ListIter& other)
		{

		}

		ListIter& operator=(const ListIter& other)
		{
			
		}

		Node<T> * next()
		{
			return link->next();
		}

		T & operator*()
		{

		}

		T* operator->()
		{

		}

		ListIter& operator++()
		{
			*link = link->getNext()->getLink();
		}

		ListIter& operator--()
		{
			*link = link->getPrev()->getLink();
		}

		ListIter operator++(int)
		{
			ListIter<T> tmp = *this;
			*link = link->getNext()->getLink();
			return tmp;
		}

		ListIter operator--(int)
		{
			ListIter<T> tmp = *this;
			*link = link->getPrev()->getLink();
			return tmp;
		}

		friend bool operator==(const ListIter& lhs, const ListIter& rhs)
		{

		}

		friend bool operator!=(const ListIter& lhs, const ListIter& rhs)
		{

		}

		Link<T> * getLink()
		{
			return link;
		}
	private:
		Link<T> * link;
	};
	using iterator = ListIter < T >;
public:
	List();
	~List();

	size_t size() const noexcept
	{
		size_t tmp = 0;

		iterator iter = iterator(head.getNext());
		while (iter->next() != nullptr)
		{
			iter++;
			tmp++;
		}

		return tmp;
	}

	iterator begin() const
	{
		return iterator(head.getNext());
	}

	iterator end() const
	{
		iterator iter = iterator(head.getNext());
		while (iter->next() != nullptr)
		{
			iter++;
		}

		return iter;
	}

	void pop_back()
	{

	}

	void pop_front()
	{

	}

	void push_back(const T& value)
	{
		Node<T> * n = (Node<T>*)malloc(sizeof(Node<T>));
		n->setValue(value);

		n->getLink()->setNext(nullptr);

		iterator iter = iterator(head.getNext());
		while (iter->next() != nullptr)
			iter++;

		iter.next()->getLink()->setNext(n);
		n->getLink()->setPrev(iter.getLink()->getPrev());
	}

	void push_front(const T& value)
	{
		Node<T> * n = (Node<T>*)malloc(sizeof(Node<T>));
		n->setValue(value);
		
		n->getLink()->setNext(*head);
		n->getLink()->setPrev(nullptr);

		head.setPrev(n);

		head = *n;
	}

	iterator insert(const iterator& pos, const T& value)	{	}
	iterator erase(const iterator& pos)
	{

	}
private:
	Link<T> head;
};


#endif