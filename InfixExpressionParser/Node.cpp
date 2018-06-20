#include "Node.h"

template<typename item_type>
Node<item_type>::Node()
{
	this->data = {};
	this->next = nullptr;
}

template<typename item_type>
Node<item_type>::Node(const item_type& data_item, Node* next_ptr)
{
	this->data = data_item;
	this->next = next_ptr;
}

template<typename item_type>
Node<item_type>::~Node()
{
	// Delete Node
}