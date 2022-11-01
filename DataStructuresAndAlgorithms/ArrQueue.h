#pragma once

template<class T, int size = 100>
class ArrQueue
{



private:
	int first;
	int last;
	T storage[size];
};