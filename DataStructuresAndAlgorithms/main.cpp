#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "DLList.h"

int main(int argc, char* argv[])
{
	DLList<int> dl;
	dl.insertBack(1);
	std::cout << dl << std::endl;

	dl.insertFront(2);
	std::cout << dl << std::endl;

	dl.insertBack(3);
	std::cout << dl << std::endl;

	dl.insertBack(4);
	std::cout << dl << std::endl;

	dl.deleteVal(4);
	std::cout << dl << std::endl;

	dl.deleteVal(3);
	std::cout << dl << std::endl;

	dl.deleteVal(2);
	std::cout << dl << std::endl;

	dl.deleteVal(1);
	std::cout << dl << std::endl;

	system("pause");
	return 0;
}
