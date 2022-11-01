#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "BETree.h"

int main(int argc, char* argv[])
{

	BETreeAnalysor* pAnalysor = new BETreeAnalysor();

	pAnalysor->SetParam("x", 10);
	pAnalysor->SetParam("y", 20);

	pAnalysor->InitExp("2 * x + y");
	float val = pAnalysor->Value();

	pAnalysor->SetParam("x", 33);
	pAnalysor->SetParam("y", 20);
	float val2 = pAnalysor->Value();

 	system("pause");
	return 0;
}
