#include "Stack.h"

template<typename item_type>
Stack<item_type>::Stack()
{
	top_of_stack = new Node<item_type>({}, nullptr);
	num_items = 0;
}

template<typename item_type>
void Stack<item_type>::push(const item_type& item)
{
	top_of_stack = new Node<item_type>(item, top_of_stack);
	++num_items;
}

template<typename item_type>
item_type& Stack<item_type>::top()
{
	return top_of_stack->data;
}

template<typename item_type>
void Stack<item_type>::pop()
{
	if (!empty()) {
		Node<item_type>* temp = top_of_stack;
		top_of_stack = top_of_stack->next;
		delete temp;
		--num_items;
	}
}

template<typename item_type>
bool Stack<item_type>::empty() const
{
	return top_of_stack == nullptr;
}

template<typename item_type>
size_t Stack<item_type>::size()
{
	return num_items;
}

template<typename item_type>
Stack<item_type>::~Stack()
{
	// Delete stack
}