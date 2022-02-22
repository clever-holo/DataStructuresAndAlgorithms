#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "DLList.h"

int main(int argc, char* argv[])
{
	DLList<int> dl;

	dl.push_back(1);
	dl.push_back(2);
	dl.push_back(3);
	dl.push_back(4);


	dl.pop_back();
	std::cout << dl << std::endl;

	dl.pop_front();
	std::cout << dl << std::endl;

	dl.pop_front();
	std::cout << dl << std::endl;

	dl.pop_back();
	std::cout << dl << std::endl;

	dl.pop_front();
	std::cout << dl << std::endl;

	system("pause");
	return 0;
}
