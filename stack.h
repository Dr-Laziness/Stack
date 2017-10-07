#pragma once

#include <iostream>

template<typename T>
class Stack
{
private:
	struct Element
	{
		T		value;
		Element	*next;
	};

public:
	class Iterator
	{
	private:
		Element	*_ptr_element;

		friend class Stack;
		Iterator() : _ptr_element(nullptr) {}
		Iterator(Element *element) : _ptr_element(element) {}

	public:
		Iterator(const Iterator &it) : _ptr_element(it._ptr_element){}

		Iterator operator=(const Iterator &p_iterator)
		{
			_ptr_element = p_iterator._ptr_element;
			return *this;
		}

		bool operator==(const Iterator &it) const
		{
			return _ptr_element == it._ptr_element;
		}

		bool operator!=(const Iterator &it) const
		{
			return _ptr_element == it._ptr_element;
		}

		Iterator &operator++()
		{
			_ptr_element = _ptr_element->next;
			return *this;
		}

		Iterator &operator++(int)
		{
			_ptr_element = _ptr_element->next;
			return *this;
		}

		T &operator*() const
		{
			return _ptr_element->value;
		}
	};

private:
	unsigned long int	_size;
	Element				*_ptr_begin;
	Iterator			_begin;

	//+++
	Element *find_last_element()
	{
		Element *temp = _ptr_begin;
		while(temp->next != nullptr)
			temp = temp->next;
		return temp;
	}
	//+++
	void push_back(const T value)
	{
		Element *temp = new Element;
		temp -> value = value;
		temp -> next = nullptr;

		if(_ptr_begin == 0)
		{
			_ptr_begin = temp;
			_begin = Iterator(_ptr_begin);
		}
		else
		{
			Element *last_element = find_last_element();
			last_element->next = temp;
			last_element = temp;
		}
		_size++;
	}
	//+++
	void clean_stack()
	{
		while (!isEmpty())
		{
			Element *temp = _ptr_begin;
			_ptr_begin = _ptr_begin->next;
			delete temp;
		}
		_begin = Iterator(_ptr_begin);
		_size = 0;
	}

public:
	//+++
	Stack() :
		_ptr_begin(nullptr),
		_size(0),
		_begin(Iterator(_ptr_begin)) { }
	//+++
	Stack(const Stack &p_stack) :
		Stack()
	{
		Iterator temp = p_stack._begin;
		for(unsigned long int i = 0; i < p_stack.size(); i++)
		{
			push_back(*temp);
			temp++;
		}
	}

	Stack(Stack &&p_stack) :
		_ptr_begin(p_stack._ptr_begin),
		_size(p_stack._size),
		_begin(Iterator(_ptr_begin))
	{
		p_stack.clean_stack();
	}

	~Stack()
	{
		clean_stack();
		delete _ptr_begin;
	}

	//+++
	Stack operator=(const Stack &p_stack)
	{
		Iterator temp = p_stack._begin;
		clean_stack();
		for(unsigned long int i = 0; i < p_stack.size(); i++)
		{
			push_back(*temp);
			temp++;
		}
		return *this;
	}

	Stack operator=(Stack &&p_stack)
	{
		Element *temp_ptr_beginer = p_stack._ptr_begin;
		p_stack._ptr_begin = _ptr_begin;
		_ptr_begin = temp_ptr_beginer;

		unsigned long int temp_size = p_stack._size;
		p_stack._size = _size;
		_size = temp_size;

		_begin = Iterator(_ptr_begin);
		p_stack._begin = Iterator(p_stack._ptr_begin);

		return *this;
	}

	//+++
	bool isEmpty() const
	{
		return _ptr_begin == nullptr;
	}
	//+++
	unsigned long int size() const
	{
		return _size;
	}

	Iterator begin()
	{
		return _begin;
	}
	//+++
	void push(const T &value)
	{
		Element *temp = new Element;
		temp->value = value;
		temp->next = _ptr_begin;

		_ptr_begin = temp;
		_begin = Iterator(_ptr_begin);

		_size++;
	}
	//+++
	T pop()
	{
		if(isEmpty())
		{
			std::cout << "The stack is empty." << std::endl;
			exit(1);
		}
		T value = _ptr_begin->value;

		Element *temp = _ptr_begin;

		_ptr_begin = _ptr_begin->next;
		_begin = Iterator(_ptr_begin);
		_size--;

		delete temp;
		return value;
	}
	//+++
	void print()
	{
		Iterator temp = Iterator(_ptr_begin);
		for(unsigned long int i = 0; i < size(); i++)
		{
			std::cout << *temp << " ";
			temp++;
		}
		std::cout << std::endl;
	}
};
