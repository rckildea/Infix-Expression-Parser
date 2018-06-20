#pragma once

template<typename item_type>
struct Node
{
	item_type data; // Value stored in a node
	Node* next; // Pointer that points to the next node in the list

	Node();
	Node(const item_type& data_item, Node* next_ptr = nullptr);
	virtual ~Node();
};
