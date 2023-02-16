#include <iostream>
#include <fstream>
#include "DictionaryList.h"

template <typename T>
void readFromFail(DictionaryList<T>& dict);
template <typename T>
void searchingInDict(DictionaryList<T>& dict);
template <typename T>
void deletedDataFromDict(DictionaryList<T>& dict);
template <typename T>
void insertDataFromDict(DictionaryList<T>& dict);
template <typename T>
void findIntesectionDicts(DictionaryList<T>& dict1, DictionaryList<T>& dict2);

int main()
{
	std::cout << "Programm starts.";
	try {
		DictionaryList<std::string> test1;
		DictionaryList<std::string> test2;
		DictionaryList<std::string> test3;

		std::cout << "\n\n1. Filling out the dictionary.\n";
		readFromFail(test1);
		std::cout << "test1: ";
		test1.outAll();

		std::cout << "\n\n2. Dictionary search.\n";
		searchingInDict(test1);

		std::cout << "\n3. Insert data from dictionary.\n";
		insertDataFromDict(test1);
		std::cout << "test1: ";
		test1.outAll();
		
		std::cout << "\n\n4. Deleted data from dictionary.\n";
		deletedDataFromDict(test1);
		std::cout << "test1: ";
		test1.outAll();

		std::cout << "\n\n5. Interaction with another dictionary.\n";
		readFromFail(test2);
		std::cout << "test2: ";
		test2.outAll();
		
		std::cout << "\n\n6. Copy constructor.\n";
		test3 = test2;
		std::cout << "test3: ";
		test3.outAll();
		
		std::cout << "\n\n7. Merger of dictionaries.\n";
		test1.merge(test2);
		std::cout << "test1: "; 
		test1.outAll();
		std::cout << "\ntest2: ";
		test2.outAll();

		std::cout << "\n\n8. Deleted one dictionary from another.\n";
		test1.deleted(test3);
		std::cout << "test1: ";
		test1.outAll();
		std::cout << "\ntest3: ";
		test3.outAll();

		std::cout << "\n\n9. Find intersection of dictionaries.\n";
		findIntesectionDicts(test1, test3);

		std::cout << "\n\nProgramm has finished";
	}
	catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		exit(-1);
	}
	return 0;
}

template <typename T>
void readFromFail(DictionaryList<T>& dict) {
	std::ifstream in;
	std::string failName;
	std::cout << "Enter fail name: ";
	std::cin >> failName;
	in.open(failName);
	if (!in.is_open()) {
		throw std::exception("failed to open file");
	}
	else {
		T data;
		while (!in.eof()) {
			in >> data;
			if (!std::cin || std::cin.peek() != '\n')
			{
				throw std::exception("attempt to insert a key of the wrong type");
			}
			dict.insert(data);
		}
	}
	in.close();
}
template <typename T>
void searchingInDict(DictionaryList<T>& dict) {
	T data;
	std::cout << "Enter a data to check in the dictionary: ";
	std::cin >> data;
	if (!std::cin || std::cin.peek() != '\n')
	{
		throw std::exception("attempt to search for a key of the wrong type");
	}
	std::cout << (dict.search(data) ? "Data have found.\n" : "Data haven't found.\n");
}
template <typename T>
void deletedDataFromDict(DictionaryList<T>& dict) {
	T data;
	std::cout << "Enter the data you want to delete: ";
	std::cin >> data;
	if (!std::cin || std::cin.peek() != '\n')
	{
		throw std::exception("attempt to delete a key of the wrong type");
	}
	std::cout << (dict.deleted(data) ? "Data successfully deleted.\n" : "This data is not in the dictionary.\n");
}
template <typename T>
void insertDataFromDict(DictionaryList<T>& dict) {
	T data;
	std::cout << "Enter the data you want to insert: ";
	std::cin >> data;
	if (!std::cin || std::cin.peek() != '\n')
	{
		throw std::exception("attempt to insert a key of the wrong type");
	}
	std::cout << (dict.insert(data) ? "Data successfully inserted.\n" : "This data already in dictionary\n");
}
template <typename T>
void findIntesectionDicts(DictionaryList<T>& dict1, DictionaryList<T>& dict2)
{
	std::cout << "Intersection 1: ";
	getIntersection(dict1, dict2).outAll();
	std::cout << "\nLet's add some data in dict test3\n";
	insertDataFromDict(dict2);
	std::cout << "\ntest1: ";
	dict1.outAll();
	std::cout << "\ntest3: ";
	dict2.outAll();
	std::cout << "\nIntersection 2: ";
	getIntersection(dict1, dict2).outAll();
}