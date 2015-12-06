#pragma once

#include <string>
#include <cstdbool>
#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

typedef enum
{
    ENDFILE,ERROR,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
}TokenType;

typedef enum
{
	START, 
	INASSIGN, 
	INCOMMENT, 
	INNUM, 
	INID, 
	DONE 
}StateType;

class Token
{
public:
	TokenType m_tokentype;
	string m_strval;
};

class Scanner
{
public:
	Scanner::Scanner(const string& src_name, const string& des_name);
	~Scanner();
	void get_next_token();
	void unget();

	string get_token_type();
	string get_token_val() { return token.m_strval; }
	bool is_end() { return m_end_of_file; }
	int get_line_num() { return m_line_num; }

private:
	void get_next_line();

	int m_line_length = -1;
	int m_line_current_pos = 0;
	int m_line_num = -1;
	bool m_end_of_file = false;
	string m_line;

	string m_src_name;
	string m_des_name;
	Token token;
	ifstream m_src_file;
	ofstream m_des_file;
};


