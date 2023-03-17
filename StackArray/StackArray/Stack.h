#pragma once
#include <string>
template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	virtual void push(const T& e) = 0;
	virtual T pop() = 0;
	virtual bool isEmpty() = 0;

	virtual bool isFull() = 0;
	virtual const T& top() = 0;

};