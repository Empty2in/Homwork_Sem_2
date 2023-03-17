#include <iostream>
#include <fstream>
#include "StackArray.h"
#include "QueueArray.h"

bool checkBalanceBrackets(const std::string& text, const int maxDeep);
void printQueue(QueueArray<char>& queue, const size_t& maxSize);
void printStack(StackArray<char>& stack, const size_t& maxSize);
void checkSteck(std::fstream& stream, size_t maxSteckSize);
void checkQueue(std::istream& stream, size_t maxSize);
void openFail(std::fstream& stream, std::string fileName);

int main() {
	
	std::fstream in;
	std::string fileName;

	try {

		std::cout << "\nTest of check Steck\n";
		openFail(in, fileName);
		while (!in.eof()) {
			size_t maxSteckSize;
			in >> maxSteckSize;
			if (!in) {
				throw std::exception("incorrect maxDeep.");
			}
			in.ignore();
			checkSteck(in, maxSteckSize);
		}
		in.close();

		std::cout << "\nTest of check Brackets\n";
		openFail(in, fileName);
		while (!in.eof()) {
			std::string text;
			int maxDeep;
			in >> maxDeep;
			if (!in) {
				throw std::exception("incorrect maxDeep.");
			}
			in.ignore();
			std::getline(in, text);
			std::cout << text << (checkBalanceBrackets(text, maxDeep) ? "\tYES\n" : "\tNO\n");
		}
		in.close();

		std::cout << "\nTest of Queue\n";

		openFail(in, fileName);

		while (!in.eof()) {
			size_t maxSize;
			in >> maxSize;
			if (!in) {
				throw std::exception("incorrect maxSize.");
			}
			in.ignore();
			checkQueue(in, maxSize);
		}
		in.close();
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
}

void openFail(std::fstream& stream, std::string fileName) {
	std::cout << "Enter fail name: ";
	std::cin >> fileName;
	stream.open(fileName);
	if (!stream.is_open()) {
		throw std::exception("failed to open file.");
	}
	if (stream.peek() == EOF) {
		throw std::exception("fail is empty.");
	}
}

bool checkBalanceBrackets(const std::string& text, const int maxDeep) {
	StackArray<char> skobki(maxDeep);
	for (char simb : text) {
		switch (simb) {
		case '(': skobki.push(')'); break;
		case '[': skobki.push(']'); break;
		case '{': skobki.push('}'); break;
		case ')':
		case ']':
		case '}':
			if (skobki.isEmpty() || skobki.top() != simb) {
				return false;
			}
			skobki.pop();
			break;
		default:
			break;
		}
	}
	return skobki.isEmpty();
}

void checkQueue(std::istream& stream, size_t maxSize) {
	QueueArray<char> queue(maxSize);
	std::string text;
	std::getline(stream, text, '\n');
	for (char simb : text) {
		if (simb != ' ') {
			queue.enQueue(simb);
		}
	}
	printQueue(queue, maxSize);

	std::cout << (queue.isEmpty() ? "\tQueue is empty\n" : "\tQueue isn't empty\n");
	std::cout << (queue.isFull() ? "\tQueue is full\n" : "\tQueue isn't full\n");

	std::cout << "check deQueue\n";
	queue.deQueue();
	printQueue(queue, maxSize);

	std::cout << "check enQueue.\n";
	queue.enQueue('7');
	printQueue(queue, maxSize);
	std::cout << "\n";
}

void checkSteck(std::fstream& stream, size_t maxSteckSize) {
	StackArray<char> stack(maxSteckSize);
	std::string text;
	std::getline(stream, text, '\n');
	for (char simb : text) {
		if (simb != ' ') {
			stack.push(simb);
		}
	}
	printStack(stack, maxSteckSize);
	std::cout << (stack.isEmpty() ? "\tStack is empty\n" : "\tStack isn't empty\n");
	std::cout << (stack.isFull() ? "\tStack is full\n" : "\tStack isn't full\n");

	std::cout << "check pop()\n";
	stack.pop();
	printStack(stack, maxSteckSize);

	std::cout << "check push()\n";
	stack.push('8');
	printStack(stack, maxSteckSize);
	std::cout << "\n";
}

void printQueue(QueueArray<char> &queue, const size_t &maxSize) {
	queue.Print();
	std::cout << "\tfirst: " << queue.first() << "\n";
	std::cout << "\tlast: " << queue.last() << "\n";
	std::cout << "\tcount: " << queue.count() << "\n";
	std::cout << "\tsize: " << maxSize << "\n";
}

void printStack(StackArray<char> &stack, const size_t& maxSize) {
	stack.Print();
	std::cout << "\ttop: " << stack.top() << '\n';
	std::cout << "\tmax size: " << maxSize << '\n';
}