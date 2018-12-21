#pragma once

#include <iostream>
#include <cstdio>
#include <iterator>
#include <vector>
#include <algorithm>  

#define DEBUG 1

using namespace std;

template<class T> class VectorItt;

template<class T> class Vector
{
public:
	using iterator = VectorItt<T>;

	Vector()
	{
		items = nullptr;
		capacity = 0;
		size = 0;
	}

	~Vector()
	{
		delete items;
	}

	Vector(const Vector& other)
	{
		capacity = other.getCapacity();
		size = other.getSize();

		reserve(capacity);

		for (int i = 0; i < other.getSize(); i++)
		{
			items[i] = other.data()[i];
		}
	}

	Vector(Vector&& other)
	{
		items = other.data();
		size = other.size;
		capacity = other.getCapacity();
		other.setData(nullptr);
	}

	Vector(const vector<T>& other)
	{
		capacity = other.capacity();
		size = other.size();

		reserve(capacity);

		for (int i = 0; i < other.getSize(); i++)
		{
			items[i] = other.at(i);
		}
	}
	
	Vector(const char* other)
	{
		int length = strlen(other);

		if (items != nullptr && length < capacity && length == size)
		{
			int index = 0;
			for (iterator i = begin(); i != end(); i++)
			{
				char tmp = other[index++];
				*i.data() = tmp;
			}
		}
		else
		{
			items = (T*)malloc(length+1);

			capacity = length+1;
			size = length;

			int index = 0;
			for (iterator i = begin(); i != end(); i++)
			{
				char tmp = other[index++];
				*i.data() = tmp;
			}
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (other.getSize() == size)
		{
			for (int i = 0; i < other.getSize(); i++)
			{
				items[i] = other.data()[i];
			}
		}
		else
		{
			capacity = other.getCapacity();
			size = other.getSize();

			reserve(capacity);

			for (int i = 0; i < other.getSize(); i++)
			{
				items[i] = other.data()[i];
			}
		}
		return *this;
	}

	Vector& operator=(Vector&& other)
	{
		items = other.data();
		size = other.getSize();
		capacity = other.getCapacity();
		other.setData(nullptr);

		return *this;
	}

	T& operator[](size_t i)
	{
		return items[i];
	}

	T& at(size_t i)
	{
		if (i >= size || i < 0) throw std::out_of_range("out of range");
		return items[i];
	}

	const T& operator[](size_t i) const
	{
		return items[i];
	}

	const T& at(size_t i) const
	{
		if (i >= capacity) throw std::exception("out of bounds");
		return items[i];
	}

	T* data() noexcept
	{
		return items;
	}

	void setData(T* t)
	{
		items = t;
	}

	const T* data() const noexcept
	{
		return items;
	}

	size_t getSize() const noexcept
	{
		return size;
	}

	size_t getCapacity() const noexcept
	{
		return capacity;
	}
	
	void print()
	{
		for (iterator i = begin(); i != end(); i++)
		{
			cout << *i;
		}
		//for (int i = 0; i < size; i++)
		//	cout << items[i];
		cout << endl << "( s: " << size << " | c: " << capacity << ")" << endl;
		if (size >= capacity) cout << "[SIZE IS OVER CAPACISTY]" << endl;
	}

	void reserve(size_t n)
	{
		capacity = n;
		if (items == nullptr)
		{
			items = (T*)malloc(capacity);
			return;
		}

		T * tmp = (T*)malloc(capacity);

		for (int i = 0; i < size; i++)
			tmp[i] = items[i];

		items = (T*)malloc(capacity);

		for (int i = 0; i < size; i++)
			items[i] = tmp[i];

		delete tmp;
	}

	void shrink_to_fit()
	{
		reserve(size);
	}

	void push_back(T t)
	{
		if (size >= capacity)
		{
			if (capacity == 0) capacity = 4;
			else capacity *= 2;

			reserve(capacity);
		}
		items[size++] = t;
	}

	void resize(size_t n)
	{
		if (n > capacity)
		{
			reserve(n);
			for (int i = size; i < capacity; i++)
				items[i] = 0;
		}
		else if (n <= size)
		{
			for (int i = size; i < capacity; i++)
				items[i] = 0;
		}
		size = n;
	}

	iterator begin() const
	{
		return iterator(items);
	}

	iterator end() const
	{
		return iterator(items + size);
	}

	bool comp1(T t0, T t1)
	{
		return t0 < t1;
	}

	bool comp2(const T & t0, const T & t1)
	{
		return t0 > t1;
	}

	bool comp3(T t0, T t1)
	{
		return t0 >= t1;
	}

	friend bool operator<(const Vector& lhs, const Vector& other)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());
	}

	friend bool operator>(const Vector& lhs, const Vector& other)
	{
		return std::lexicographical_compare(other.begin(), other.end(), lhs.begin(), lhs.end());
	}

	friend bool operator<=(const Vector& lhs, const Vector& other)
	{
		return !(other < lhs);
	}

	friend bool operator>=(const Vector& lhs, const Vector& other)
	{
		return !(other > lhs);
	}

	friend bool operator==(const Vector& lhs, const Vector& other)
	{
		if (lhs.getSize() != other.getSize()) return false;
		for (int i = 0; i < lhs.getSize(); i++)
		{
			if (lhs.data()[i] != other.data()[i]) return false;
		}
		
		return true;
	}

	friend bool operator!=(const Vector& lhs, const Vector& other)
	{
		return !(lhs == other);
	}

	friend std::ostream& operator<<(std::ostream& cout, const Vector& other) 
	{
		for (size_t i = 0; i < other.getSize(); ++i)
			cout << other[i];
		return cout;
	}
private:
	T * items;

	size_t size;
	size_t capacity;
};

template<class T> class VectorItt {
public:
	/*using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	typedef typename ptrdiff_t difference_type;
	using pointer = const T*;
	using iterator = VectorItt<T>;*/
	using iterator = VectorItt<T>;
	typedef typename std::random_access_iterator_tag iterator_category;
	typedef typename T value_type;
	typedef typename ptrdiff_t  difference_type;
	typedef typename T* pointer;
	typedef typename T& reference;

	VectorItt(T* p)
	{
		current = p;
	}

	VectorItt()
	{
		current = nullptr;
	}

	VectorItt(const VectorItt& other)
	{
		current = other.data();
	}

	VectorItt& operator=(const VectorItt& other)
	{
		current = other.data();
		return *this;
	}

	VectorItt& operator++()
	{
		current++;
		return *this;
	}

	VectorItt& operator--()
	{
		current--;
		return *this;
	}

	VectorItt operator++(int)
	{
		iterator tmp = *this;
		++current;
		return tmp;
	}

	VectorItt operator--(int)
	{
		iterator tmp = *this;
		--current;
		return tmp;
	}

	VectorItt operator+(difference_type i) const
	{
		return VectorItt(current + i);
	}

	VectorItt operator-(difference_type i) const
	{
		return VectorItt(current - i);
	}

	difference_type operator-(const VectorItt& other) const
	{
		return current - other.data();
	}

	friend bool operator>=(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() >= rhs.data();
	}

	friend bool operator<=(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() <= rhs.data();
	}

	friend bool operator>(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() > rhs.data();
	}

	friend bool operator<(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() < rhs.data();
	}

	friend bool operator==(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() == rhs.data();
	}

	friend bool operator!=(const VectorItt& lhs, const VectorItt& rhs)
	{
		return lhs.data() != rhs.data();
	}

	T& operator*()
	{
		return *current;
	}

	T& operator[](size_t i)
	{
		return current[i];
	}

	T* operator->()
	{
		return *current;
	}

	T* data() const noexcept
	{
		return current;
	}
private:
	T* current;
};