#include "test.h"
#include <cctype>		// for isalpha

using std::cout;
using std::endl;

Scanner::Scanner(const string& src_name, const string& des_name)
{
	m_src_file.open(src_name);
	m_des_file.open(des_name);

	m_src_name = src_name;
	m_des_name = des_name;
}

Scanner::~Scanner()
{
	m_src_file.close();
	m_des_file.close();
}

void Scanner::get_next_token(void)
{
	const int max_size_read = 255;
	string line;
	
	while (std::getline(m_src_file, line))
	{
		int length = line.length();
		int current_pos = 0;
		if (std::isalpha('a'))
			;
	}
}
