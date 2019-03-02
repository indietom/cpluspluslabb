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
		Link()
		{

		}

		~Link()
		{

		}

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
	class Node : Link<T>
	{
		friend class List<T>;
	public:
		Node()
		{

		}

		~Node()
		{

		}

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
		
		void print()
		{
			cout << "(n: " << getNext() << " | p: " << getPrev() << " | v: " << value << ")" << endl;
		}
	private:
		T value;
	};

	template<class T>
	class ListIter
	{
	public:
		using iterator_category = bidirectional_iterator_tag;

		ListIter()
		{

		}

		~ListIter()
		{

		}

		ListIter(Node<T> * p)
		{
			link = p->getLink();
		}

		ListIter(const ListIter& other)
		{
			link = other.getLink();
		}

		ListIter& operator=(const ListIter& other)
		{
			link = other.getLink();
		}

		Node<T> * next()
		{
			return link->getNext();
		}

		T & operator*()
		{
			return *link;
		}

		T* operator->()
		{
			return link;
		}

		ListIter& operator++()
		{
			*link = link->getNext();
		}

		ListIter& operator--()
		{
			*link = link->getPrev();
		}

		ListIter operator++(int)
		{
			ListIter<T> tmp = *this;
			*link = link->getNext();
			return tmp;
		}

		ListIter operator--(int)
		{
			ListIter<T> tmp = *this;
			*link = link->getPrev();
			return tmp;
		}

		friend bool operator==(const ListIter& lhs, const ListIter& rhs)
		{
			return lhs.getLink() == rhs.getLink();
		}

		friend bool operator!=(const ListIter& lhs, const ListIter& rhs)
		{
			return !(lhs == rhs);
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
	List()
	{

	}

	~List()
	{

	}

	size_t size() //const noexcept
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
		iterator iter = iterator(head.getNext());
		while (iter->next() != nullptr)
			iter++;

		iter.getLink()->setNext(nullptr);
	}

	void pop_front()
	{
		head.setPrev(head.getPrev());
		head.setNext(nullptr);
	}

	void push_back(const T& value)
	{
		Node<T> * n = (Node<T>*)malloc(sizeof(Node<T>));
		n->setValue(value);

		n->setNext(nullptr);

		iterator iter = iterator(head.getNext());
		while (iter->next() != nullptr)
			iter++;

		iter.next()->getLink()->setNext(n);
		n->setPrev(iter.getLink()->getPrev());
	}

	void push_front(const T& value)
	{
		Node<T> * n = (Node<T>*)malloc(sizeof(Node<T>));
		n->setValue(value);
		
		n->setNext(head.getPrev());
		n->setPrev(nullptr);

		head.setPrev(n);

		head = *n;
	}

	iterator insert(const iterator& pos, const T& value)
	{

	}

	iterator erase(const iterator& pos)
	{

	}

	void print()
	{
		iterator iter = iterator(head.getNext());
		while (iter.next() != nullptr)
		{
			cout << (iter.next()) << endl;
			iter++;
		}
	}
private:
	Link<T> head;
};


#endif