#pragma once
class DoubleList
{
private:
	class Node {
	public:
		Node* _prev;
		Node* _next;
		int _key;
		Node(int key = 0, Node* prev = nullptr, Node* next = nullptr) {
			_key = key;
			_prev = prev;
			_next = next;
		}
	};

	Node* _head;
	Node* _tail;
	size_t _size;

	bool insertNode(Node* newNode);
	bool del();

public:
	DoubleList();
	~DoubleList();

	DoubleList(const DoubleList &other) = delete;
	DoubleList(DoubleList&& other) = delete;
	DoubleList&& operator=(const DoubleList& other) = delete;
	DoubleList&& operator=(DoubleList& other) = delete;

	void clean();
	void print();
	bool isEmpty();
	bool insert(int key);
	void replaceByAverage();
};

