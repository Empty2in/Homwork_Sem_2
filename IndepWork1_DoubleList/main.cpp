#include <iostream>
#include <fstream>
#include "DoubleList.h"

int main() {
	
	std::cout << "Program start.\n\n";

	try {
		std::cout << "1. Create and test empty list.\n";
		DoubleList test;
		test.print();
		test.replaceByAverage();
		test.print();

		std::cout << "\n2. Insert elem to list from file.\n";
		std::fstream in;
		std::string fileName;
		std::cout << "Enter file name: ";
		std::cin >> fileName;
		in.open(fileName);
		if (!in.is_open()) {
			throw std::exception("Failed to open the fail.");
		}
		if (in.peek() == EOF) {
			throw std::exception("Fail is empty");
		}
		while (!in.eof()) {
			int data;
			in >> data;
			if (!in) {
				throw std::exception("Uncorrect data");
			}
			test.insert(data);
		}
		in.close();
		test.print();

		std::cout << "\n3. Test replaceByAverage.\n";
		test.replaceByAverage();
		test.print();

		std::cout << "\nProgram has finished.\n";
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

}

