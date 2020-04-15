#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r):rel(r) {
	this->head = NULL;
	this->tail = NULL;
	this->lsize = 0;
}


//complexity: best case - theta(1)  worst - theta(n)  overall : O(n)
TValue SortedMap::add(TKey k, TValue v) {
	Node* current_node = this->head;

	while (current_node != NULL && current_node->info.first != k) {
		current_node = current_node->next;
	}
	//case when we have the value added already and we modify the second arg.
	if (current_node != NULL) {
		int val_old = current_node->info.second;
		current_node->info.second = v;
		return val_old;
	}
	//the case where we need to insert a value and we do that by the given rule
	else {
		Node* node_to_add = new Node();
		node_to_add->info.first = k;
		node_to_add->info.second = v;
		
		if (this->head == NULL) {
			this->head = node_to_add;
			this->tail = node_to_add;
			this->lsize++;
			return NULL_TVALUE;
		}

		//searching for the position by the rule
		Node* current_node = this->head;
		while (current_node != NULL) {
			if (this->rel(current_node->info.first, node_to_add->info.first) == false) {

				if (current_node->prev == NULL) {
					this->head = node_to_add;
					current_node->prev = node_to_add;
					node_to_add->next = current_node;
					node_to_add->prev = NULL;
					this->lsize++;
					return NULL_TVALUE;
				}
				else {
					node_to_add->next = current_node;
					node_to_add->prev = current_node->prev;
					current_node = current_node->prev;
					current_node->next = node_to_add;
					current_node = current_node->next;
					current_node = current_node->next;
					current_node->prev = node_to_add;
					this->lsize++;
					return NULL_TVALUE;

				}
			}
			else if (this->rel(current_node->info.first, node_to_add->info.first) == true && current_node->next == NULL) {
				this->tail = node_to_add;
				node_to_add->next = NULL;
				node_to_add->prev = current_node;
				current_node->next = node_to_add;
				this->lsize++;
				return NULL_TVALUE;
			}
			current_node = current_node->next;
				
		}

	}
 
}

//complexity: best case - theta(1)  worst - theta(n)
TValue SortedMap::search(TKey k) const {
	Node* current_node = this->head;
	while (current_node != NULL && current_node->info.first != k) {
		current_node = current_node->next;
	}
	if (current_node == NULL)
		return NULL_TVALUE;
	return current_node->info.second;

}

//complexity: theta(n)
TValue SortedMap::remove(TKey k) {
	Node* current_node = this->head;
	while (current_node != NULL && current_node->info.first != k) {
		current_node = current_node->next;
	}
	Node* to_remove = current_node;
	if (current_node != NULL) {
		if(current_node == this->head)
			if (current_node == this->tail) {
				this->head = NULL;
				this->tail = NULL;
			}
			else {
				this->head = this->head->next;
				this->head->prev = NULL;
			}
		else if (current_node == this->tail) {
			this->tail = this->tail->prev;
			this->tail->next = NULL;
		}
		else {
			current_node->next->prev = current_node->prev;
			current_node->prev->next = current_node->next;
		}
		this->lsize--;
		return to_remove->info.second;
	}
	return NULL_TVALUE;
}

//complexity: theta(1)
int SortedMap::size() const {
	return this->lsize;
}

//complexity: theta(1)
bool SortedMap::isEmpty() const {
	if (this->lsize == 0) {
		return true;
	}
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	Node* current_node = this->head;
	Node* next_node = this->head;
	//delete all the nodes till the last one
	while (current_node != NULL) {
		next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	}
	//delete the last node
	delete next_node;
}
