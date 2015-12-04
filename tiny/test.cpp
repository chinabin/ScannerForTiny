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

void Scanner::unget()
{

}

void Scanner::get_next_line()
{
	bool end_of_file = false;
	if (m_line_current_pos >= m_line_length || m_line_length == -1)
	{
		if (std::getline(m_src_file, m_line))
		{
			m_line_num++;
			// cout << m_line_num << ": " << m_line << endl;
			m_line_length = m_line.length();
			m_line_current_pos = 0;
		}
		else
		{
			m_end_of_file = true;
		}
	}
}

void Scanner::get_next_token(void)
{
	const int max_size_read = 255;
	StateType state = START;
	token.m_strval.clear();		// must clear
	
	get_next_line();

	if (!m_end_of_file)
	{
		while (true)
		{
			bool save = true;
			bool unget = false;
			get_next_line();
			if (m_end_of_file)
				break;
			char c = m_line[m_line_current_pos];
			switch (state)
			{
				case START:
					if (std::isdigit(c))
						state = INNUM;
					else if (std::isalpha(c))
						state = INID;
					else if (c == ':')
						state = INASSIGN;
					else if (std::isspace(c))
						save = false;
					else if (c == '{')
					{
						state = INCOMMENT;
						save = false;
					}
					else
					{
						state = DONE;
						switch (c)
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
					if (c == '=')
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
					if (c == '}')
						state = START;
					break;
				case INNUM:
					if (!isdigit(c))
					{
						unget = true;
						save = false;
						state = DONE;
						token.m_tokentype = NUM;
					}
					break;
				case INID:
					if (!isalpha(c))
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
					cout << "line num is: " << m_line_num << " in " << m_line_current_pos << endl;
					cout << "string is: " << m_line << endl;
					state = DONE;
					token.m_tokentype = ERROR;
					break;
			}
			if (save)
				token.m_strval.push_back(m_line[m_line_current_pos]);
			if (unget)
				m_line_current_pos--;
			m_line_current_pos++;
			if (state == DONE)
				break;
		}
	}
}

string Scanner::get_token_type()
{
	TokenType t = token.m_tokentype;
	switch (t)
	{
		case IF: 
			return "IF";
			break;
		case THEN:
			return "THEN";
			break;
		case ELSE:
			return "ELSE";
			break;
		case END:
			return "END";
			break;
		case REPEAT:
			return "REPEAT";
			break;
		case UNTIL:
			return "UNTIL";
			break;
		case READ:
			return "READ";
			break;
		case WRITE:
			return "WRITE";
			break;
		case ID:
			return "ID";
			break;
		case NUM:
			return "NUM";
			break;
		case ASSIGN:
			return "ASSIGN";
			break;
		case EQ:
			return "EQ";
			break;
		case LT:
			return "LT";
			break;
		case PLUS:
			return "PLUS";
			break;
		case MINUS:
			return "MINUS";
			break;
		case TIMES:
			return "TIMES";
			break;
		case OVER:
			return "OVER";
			break;
		case LPAREN:
			return "LPAREN";
			break;
		case RPAREN:
			return "RPAREN";
			break;
		case SEMI:
			return "SEMI";
			break;
		case ENDFILE:
		case ERROR:
		default:
			break;
	}
	return "";
}
