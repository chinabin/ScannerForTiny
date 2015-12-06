// tiny.cpp : Defines the entry point for the console application.
//

#include "Lex.h"
#include "test.h"
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;


int main(int argc, char* argv[])
{
	/*Scanner sca("src.txt", "des.txt");
	while (!sca.is_end())
	{
		sca.get_next_token();
		cout << sca.get_token_type() << ":" << endl;
		cout << "\t" << sca.get_token_val() << endl;
	}*/
	test_scan_commnet();
	return 0;
}

