#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

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


