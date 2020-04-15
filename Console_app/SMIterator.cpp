#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	first();
}

void SMIterator::first(){
	if (map.lsize > 0) {
		current_node = map.head;
	} 
	else {
		current_node = NULL;
	}
}

void SMIterator::next(){
	if (!valid()) {
		throw exception();
	}
	current_node = current_node->next;
}

//Change the iterator to be able to remove the current element.Add the following operation in the MapIterator class :
//removes and returns the current pair from the iterator
//after the operation the current pair from the Iterator is the next element from the Map, or, if the removed element was the last one, the iterator is invalid
//throws exception if the iterator is invalid

//Complexity : Theta(1)
TElem SMIterator::remove() {

	Node* node_to_remove = get_the_node();
	if (current_node == NULL) {
		throw exception();
	}
	else if (current_node->next == NULL) {
		current_node = current_node->next;
		return node_to_remove->info;
	}
	else {
		current_node = current_node->next;
		current_node->prev = NULL;
		delete current_node->prev;
		return node_to_remove->info;
	}
}

//might need it, not sure yet
Node* SMIterator::get_the_node() {
	return this->current_node;
}

bool SMIterator::valid() const{
	if (current_node != NULL) {
		return true;
	}
	return false;
}

TElem SMIterator::getCurrent() const{
	if (current_node == NULL)
		throw exception();
	return this->current_node->info;
}


