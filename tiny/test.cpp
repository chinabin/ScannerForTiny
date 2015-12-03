#include "test.h"
#include <cctype>		// for isalpha()
#include <cstdbool>

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
	StateType state = START;
	string line;
	
	while (std::getline(m_src_file, line))
	{
		int length = line.length();
		int current_pos = 0;
		bool save = true;
		switch (state)
		{
		case START:
			if (std::isdigit(line[current_pos]))
				state = INNUM;
			else if(std::isalpha(line[current_pos]))
				state = INID;
			else if (line[current_pos] == ':')
				state = INASSIGN;
			else if (std::isspace(line[current_pos]))
				save = false;
			else if (line[current_pos] == '{')
			{
				state = INCOMMENT;
				save = false;
			}
			else
			{
				state = DONE;
				switch (line[current_pos])
				{
				case '=':
					token.m_tokentype = EQ;
					break;
				case '<':
					token.m_tokentype = LT;
					break;
				case '+':
					token.m_tokentype = PLUS;
					break;
				case '-':
					token.m_tokentype = MINUS;
					break;
				case '*':
					token.m_tokentype = TIMES;
					break;
				case '/':
					token.m_tokentype = OVER;
					break;
				case '(':
					token.m_tokentype = LPAREN;
					break;
				case ')':
					token.m_tokentype = RPAREN;
					break;
				case ';':
					token.m_tokentype = SEMI;
					break;
				default:
					token.m_tokentype = ERROR;
					break;
				}
			}
			break;
		case INASSIGN:
			state = DONE;
			if (line[current_pos] == '=')
				token.m_tokentype = ASSIGN;
			else
			{
				save = false;
				token.m_tokentype = ERROR;
				unget = true;
			}
			break;
		case INCOMMENT:
			save = false;
			if (line[current_pos] == '}')
				state = START;
			break;
		case INNUM:
			if (!isdigit(line[current_pos]))
			{
				unget = true;
				save = false;
				state = DONE;
				token.m_tokentype = NUM;
			}
			break;
		case INID:
			if (!isalpha(line[current_pos]))
			{
				unget = true;
				save = false;
				state = DONE;
				token.m_tokentype = ID;
			}
			break;
		case DONE:
		default:
			cout << "this is a bug!" << endl;
			state = DONE;
			token.m_tokentype = ERROR;
			break;
		}
		current_pos++;
	}
}
