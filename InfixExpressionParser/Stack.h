#pragma once
#include "Node.h"

template<typename item_type>
class Stack
{
private:
	Node<item_type>* top_of_stack;
	size_t num_items;
public:
	//Stack();
	//void push(const item_type& item);
	//item_type& top();
	//void pop();
	//bool empty() const;
	//size_t size();
	//virtual ~Stack();


	Stack()
	{
		top_of_stack = nullptr;
		num_items = 0;
	}

	void push(const item_type& item)
	{
		top_of_stack = new Node<item_type>(item, top_of_stack);
		++num_items;
	}

	item_type top()
	{
		return top_of_stack->data;
	}

	void pop()
	{
		if (!empty()) {
			Node<item_type>* temp = top_of_stack;
			top_of_stack = top_of_stack->next;
			delete temp;
			--num_items;
		}
	}

	bool empty() const
	{
		return num_items == 0;
	}

	size_t size()
	{
		return num_items;
	}

	~Stack()
	{
		// Delete stack
	}
};

