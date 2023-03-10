#include "DoubleList.h"
#include <iostream>

DoubleList::DoubleList() {
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}
DoubleList::~DoubleList() {
	clean();
}

bool DoubleList::isEmpty() {
	return (_head == nullptr && _tail == nullptr);
}
void DoubleList::clean() {
	while (!isEmpty()) {
		del();
	}
}
void DoubleList::print() {
	if (isEmpty()) {
		std::cout << "List is empty.\n";
	} 
	else {
		Node* temp = this->_head;
		while (temp != nullptr) {
			std::cout << temp->_key << " ";
			temp = temp->_next;
		}
		std::cout << "\n";
	}
}
bool DoubleList::insertNode(Node* newNode) {
	if (newNode == nullptr) {
		throw std::exception("failed to insert empty node.");
		return false;
	}
	if (isEmpty()) {
		_head = newNode;
		_tail = newNode;
		_size++;
		return true;
	}
	else {
		newNode->_next = this->_head;
		this->_head->_prev = newNode;
		this->_head = newNode;
		_size++;
		return true;
	}
	throw std::exception("fail to insert node.");
	return false;
}
bool DoubleList::insert(int key) {
	try {
		Node* newNode = new Node(key);
		if (!insertNode(newNode)) {
			return false;
		}
		return true;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
}
bool DoubleList::del() {
	try {
		if (isEmpty()) {
			throw std::exception("failed to delete empty list.");
			return true;
		}
		if (_tail == nullptr) {
			throw std::exception("failed to delete null tail.");
			return false;
		}
		else {
			Node* temp = this->_tail;
			if (temp->_prev != nullptr) {
				temp->_prev->_next = nullptr;
				this->_tail = temp->_prev;
			}
			else {
				_head = nullptr;
				_tail = nullptr;
			}
			delete temp;
			this->_size--;
			return true;
		}
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
	
}

void DoubleList::replaceByAverage() {
	if (isEmpty()) {
		std::cerr << "Can't replace, list is empty.";
		return;
	}
	if (_size % 2 != 0) {
		del();
	}
	Node* temp = this->_head;
	while (temp != nullptr) {
		temp->_key = (temp->_key + temp->_next->_key) / 2;
		temp->_next = temp->_next->_next;
		this->_size--;
		temp = temp->_next;
	}
}