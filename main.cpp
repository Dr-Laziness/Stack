#include <iostream>

#include "stack.h"

int main()
{
	std::cout << "----------- START -----------" << std::endl;

	Stack<char> obj_1;
	for(int i = 0; i < 5; i++)
	{
		obj_1.push(97 + i);
	}
	std::cout << "Stack 1: " << std::endl;
	obj_1.print();
	std::cout << "size: " << obj_1.size() << std::endl;

	Stack<char> obj_2{obj_1};
	for(unsigned long int i = 0; i < obj_1.size(); i++)
	{
		obj_2.push(105 + i);
	}

	std::cout << std::endl << "Stack 2:" << std::endl;
	obj_2.print();
	std::cout << "size: " << obj_2.size() << std::endl;

	obj_1 = obj_2;
	std::cout << std::endl << "Stack 1:" << std::endl;
	obj_1.print();
	for(unsigned long int i = 0; i < obj_1.size(); i++)
	{
		obj_2.push(110 + i);
	}
	std::cout << std::endl << "Stack 2:" << std::endl;
	obj_2.print();

	obj_1 = std::move(obj_2);
	std::cout << std::endl << "Stack 1:" << std::endl;
	obj_1.print();
	std::cout << "Stack 2:" << std::endl;
	obj_2.print();

	Stack<char>::Iterator it_1 = obj_1.begin();
	std::cout << "Iterator 1: " << *it_1 << std::endl;


	std::cout << "----------- END -----------" << std::endl;
	return 0;
}
