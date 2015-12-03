// tiny.cpp : Defines the entry point for the console application.
//

#include "test.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	Scanner sca("src.txt", "des.txt");
	sca.get_next_token();
	return 0;
}

