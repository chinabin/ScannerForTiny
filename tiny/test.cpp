#include "test.h"
#include <iostream>
#include <vector>
#include <iterator>

using std::vector;
using std::string;
using std::cout;
using std::endl;

/*
note: it use input character as the outer case test and the state as the inner case test.
*/
bool scan_c_comment(string r_str)
{
	int state = 1;
	int index = 0;
	char c = r_str[index];
	int length = r_str.length();
	while ( index != length )
	{
		c = r_str[index];
		switch ( c )
		{
		case '/':
			switch (state)
			{
			case 1:
				state = 2;
				break;
			case 4:
				state = 5;
				break;
			default:
				break;
			}
			break;
		case '*':
			switch (state)
			{
			case 2:
				state = 3;
				break;
			case 3:
				state = 4;
				break;
			case 4:
				break;
			default:
				break;
			}
			break;
		default:
			switch (state)
			{
			case 3:
				break;
			case 4:
				state = 3;
			default:
				break;
			}
			break;
		}
		++index;
		if (state == 5)
		{
			if (index == length)
			{
				std::cout << "good!" << std::endl;
				return true;
			}
			else
			{
				std::cout << "there is a nested comment, which not supported yet!" << std::endl;
				return false;
			}
		}
	}
	std::cout << "bad!" << std::endl;
	return false;
}

bool ex_scan_c_comment(string r_str)
{
	int error_state = -1;
	int nest = 0;
	int state = 1;
	int length = r_str.length();
	if (!length)
		return false;
	int index_str = 0;
	char c = r_str[index_str];
	bool unfinished = true;
	while (unfinished && (state != error_state))
	{
		switch (state)
		{
		case 1:
			switch (c)
			{
			case '/':
				state = 2;
				break;
			default:
				state = error_state;
				break;
			}
			break;
		case 2:
			switch (c)
			{
			case '*':
				state = 3;
				nest++;
				break;
			default:
				state = error_state;
				break;
			}
			break;
		case 3:
			switch (c)
			{
			case '/':
				state = 5;
				break;
			case '*':
				state = 4;
				break;
			default:		// others staty in state 3.
				break;
			}
			break;
		case 4:
			switch (c)
			{
			case '/':
				state = 7;
				nest--;
				break;
			case '*':
				break;
			default:
				state = 3;
				break;
			}
			break;
		case 5:
			switch (c)
			{
			case '*':
				state = 6;
				nest++;
				break; 
			default:
				state = 3;
				break;
			}
			break;
		case 6:
			switch (c)
			{
			case '*':
				state = 4;
				break;
			case '/':
				state = 5;
				break;
			default:
				break;
			}
			break;
		case 7:	
			if (length == index_str)
				unfinished = false;
			else if (!nest)
				state = error_state;
			else
			{
				state = 8;
				--index_str;    // should return back
			}
			break;
		case 8:
			switch (c)
			{
			case '*':
				state = 4;
				break;
			case '/':
				state = 9;
				break;
			default:
				break;
			}
			break;
		case 9:
			switch (c)
			{
			case '*':
				state = 3;
				nest++;
				break;
			default:
				state = 8;
				break;
			}
			break;
		default:
			std::cout << std::endl << "there is a error taken place." << std::endl;
			break;
		}
		c = r_str[++index_str];
		if (index_str == length)
		{
			unfinished = false;
			break;
		}
	}
	if ((state == 7) && (index_str == length) && !nest)
	{
		return true;
	}
	return false;
}

void test_scan_commnet()
{
	vector<string> vc_str{ "/*a/*haha*//*lala*/*/",
		"/*/*/*/*/*sdfs/*   */4545*/*/dfg*/fdg*/*/",
		"/*asdasda*/",
	};
	vector<bool> vb_rtn{ true, true, true
	};
	if (vc_str.size() != vb_rtn.size())
	{
		cout << "size not equal!" << endl;
		return;
	}
	int index = 0;
	for (auto str : vc_str)
	{
		if (vb_rtn[index] != ex_scan_c_comment(str))
		{
			cout << "item " << index << " get wrong: " << str << endl;
			cout << "should be: " << (vb_rtn[index] ? "true" : "false") << endl << endl;
		}
		index++;
	}
}