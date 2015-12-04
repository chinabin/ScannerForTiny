// tiny.cpp : Defines the entry point for the console application.
//

#include "test.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	Scanner sca("src.txt", "des.txt");
	while (!sca.is_end())
	{
		sca.get_next_token();
		cout << sca.get_token_type() << ":" << endl;
		cout << "\t" << sca.get_token_val() << endl;
	}
	return 0;
}

