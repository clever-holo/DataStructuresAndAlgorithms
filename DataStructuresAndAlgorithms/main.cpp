#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>

int main(int argc, char* argv[])
{
	std::cout << "hello world!" << std::endl;

	std::list<int> lst1;

	for(int i=0; i<5; i++)
		lst1.push_back(i+1);

	std::list<int>::iterator it1 = lst1.begin();

	std::list<int>::iterator it2 = it1;

	std::list<int> lst2(it1, it2);

	it2++;

	std::list<int> lst3(it1, it2);

	system("pause");
	return 0;
}
