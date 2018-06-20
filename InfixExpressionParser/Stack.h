#pragma once
#include "Node.h"

template<typename item_type>
class Stack
{
private:
	Node<item_type>* top_of_stack;
	size_t num_items;
public:
	Stack();
	void push(const item_type& item);
	item_type& top();
	void pop();
	bool empty() const;
	size_t size();
	virtual ~Stack();
};

