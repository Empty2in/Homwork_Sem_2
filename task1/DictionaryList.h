#pragma once
#include <iostream>

template<typename T>
class DictionaryList {
private:
	template<typename T>
	struct Node {
		T _key;
		Node<T>* _next;
		Node(T key = T(), Node<T>* next = nullptr) {
			this->_key = key;
			this->_next = next;
		}
	};
	
	Node<T>* _head;
	int _size;

	void copy(const DictionaryList<T>& obj);
	void deleted(Node<T>* del);
	void insert(Node<T>* in);

public:

	DictionaryList();
	~DictionaryList();
	DictionaryList(const DictionaryList<T>& scr);
	DictionaryList(DictionaryList<T>&& scr) noexcept;

	DictionaryList<T>& operator=(const DictionaryList<T>& scr);
	DictionaryList<T>& operator=(DictionaryList<T>&& scr) noexcept;

	int getSize() const;
	T getHead() const;
	bool is_empty();
	void clear();
	void outAll();
	void pop_front();
	void swap(DictionaryList<T>& other) noexcept;

	bool search(const T& key);
	bool insert(const T& key);
	bool deleted(T key);

	bool merge(DictionaryList<T>& other);
	bool deleted(const DictionaryList<T>& other);

	friend DictionaryList<T> getIntersection(DictionaryList<T>& one, DictionaryList<T>& two)
	{
		DictionaryList<T>Inter;
		Node<T>* temp = one._head;
		while (temp != nullptr)
		{
			if (two.search(temp->_key))
			{
				Inter.insert(temp->_key);
			}
			temp = temp->_next;
		}
		return Inter;
	}
};

template<typename T>
DictionaryList<T>::DictionaryList() {
	this->_head = nullptr;
	this->_size = 0;
}
template<typename T>
DictionaryList<T>::~DictionaryList() {
	clear();
}
template<typename T>
DictionaryList<T>::DictionaryList(DictionaryList<T>&& scr) noexcept {
	_head = scr._head;
	_size = scr._size;
	scr._head = nullptr;
	scr._size = 0;
}
template<typename T>
DictionaryList<T>::DictionaryList(const DictionaryList<T>& scr) {
	if (scr._head == nullptr) {
		this->_head = nullptr;
		this->_size = 0;
	}
	this->_head = new Node<T>(scr._head->_key);
	Node<T>* ptrScr = scr._head->_next;
	Node<T>* destScr = this->_head;
	while (ptrScr != nullptr) {
		destScr->_next = new Node<T>(ptrScr->_key);
		destScr = destScr->_next;
		ptrScr = ptrScr->_next;
	}
	this->_size = scr._size;
}

template<typename T>
DictionaryList<T>& DictionaryList<T>::operator=(const DictionaryList<T>& scr) {
	if (this == &scr) {
		return *this;
	}
	copy(scr);
	return *this;
}
template<typename T>
DictionaryList<T>& DictionaryList<T>::operator=(DictionaryList<T>&& scr) noexcept {
	if (this != &scr) {
		swap(scr);
	}
	return *this;
}

template<typename T>
inline void DictionaryList<T>::swap(DictionaryList<T>& other) noexcept {
	std::swap(_head, other._head);
	std::swap(_size, other._size);
}
template<typename T>
inline int DictionaryList<T>::getSize() const { 
	return _size; 
}
template<typename T>
inline T DictionaryList<T>::getHead() const {
	return _head;
}
template<typename T>
inline bool DictionaryList<T>::is_empty() { 
	return this->_head == nullptr; 
}
template<typename T>
inline void DictionaryList<T>::clear() {
	while (_size) {
		pop_front();
	}
}
template<typename T>
void DictionaryList<T>::pop_front() {
	if (!is_empty()) {
		Node<T>* temp = this->_head;
		_head = _head->_next;
		delete temp;
		this->_size--;
	}
	else {
		throw std::exception("Deleting an empty area of memory");
	}
}
template<typename T>
void DictionaryList<T>::outAll() {
	Node<T>* temp = this->_head;
	while (temp != nullptr) {
		std::cout << temp->_key << " ";
		temp = temp->_next;
	}
}

template<typename T>
bool DictionaryList<T>::search(const T& key) {
	Node<T>* temp = this->_head;
	while (temp != nullptr) {
		if (key == temp->_key) {
			return true;
		}
		temp = temp->_next;
	}
	return false;
}
template<typename T>
bool DictionaryList<T>::insert(const T& key) {
	if (this->is_empty() || key < _head->_key) {
		_head = new Node<T>(key, _head);
		_size++;
		return true;
	}
	else {
		Node<T>* prev = this->_head;
		while (prev != nullptr) {
			if (key == prev->_key) {
				return false;
			}
			else if ((prev->_key < key) && (prev->_next == nullptr) || (prev->_next->_key > key)) {
				Node<T>* newNode = new Node<T>(key, prev->_next);
				insert(newNode);
				return true;
			}
			prev = prev->_next;
		}
	}
	throw std::exception("Failed to insert element into list");
	return false;
}
template<typename T>
bool DictionaryList<T>::deleted(T key)
{
	if (is_empty()) {
		return false;
	}
	else if (key == this->_head->_key) {
		pop_front();
		return true;
	}
	else {
		Node<T>* temp = this->_head;
		while (temp != nullptr) {
			if (temp->_key == key) {
				this->deleted(temp);
				return true;
			}
			temp = temp->_next;
		}
		return true;
	}
	throw std::exception("Failed to remove key from the list");
	return false;
}

template<typename T>
bool DictionaryList<T>::merge(DictionaryList<T>& other) {
	if (other.is_empty()) {
		return true;
	}
	else {
		Node<T>* temp = other._head;
		while (temp != nullptr) {
			insert(temp->_key);
			temp = temp->_next;
		}
		other.clear();
		return true;
	}
	throw std::exception("Failed to merge dictionaries");
	return false;
	
}
template<typename T>
bool DictionaryList<T>::deleted(const DictionaryList<T>& other) {
	if (other._head == nullptr) {
		return true;
	}
	else {
		Node<T>* temp = other._head;
		while (temp != nullptr) {
			deleted(temp->_key);
			temp = temp->_next;
		}
		return true;
	}
	throw std::exception("Failed to remove one list from another");
	return false;
}

template<typename T>
void DictionaryList<T>::copy(const DictionaryList<T>&obj) {
	clear();
	Node<T>* temp = obj._head;
	for (int i = 0; i < obj._size; ++i) {
		insert(temp->_key);
		temp = temp->_next;
	}
	_size = obj._size;
}

template<typename T>
void DictionaryList<T>::deleted(Node<T>* del) {
	Node<T>* temp = _head;
	while (temp->_next != del) {
		temp = temp->_next;
	}
	temp->_next = del->_next;
	delete del;
	_size--;
}
template<typename T>
void DictionaryList<T>::insert(Node<T>* in) {
	if (is_empty()) {
		_head = new Node<T>(in->_key, in->_next);
	}
	else {
		Node<T>* temp = _head;
		while (temp->_next != in->_next) {
			temp = temp->_next;
		}
		temp->_next = in;
	}
	_size++;
}