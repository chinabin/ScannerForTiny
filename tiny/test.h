#pragma once

#include <string>
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
	void get_next_token();
	~Scanner();

private:
	string m_src_name;
	string m_des_name;
	string m_str;
	Token token;
	ifstream m_src_file;
	ofstream m_des_file;
};


