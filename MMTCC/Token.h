#pragma once
#include "Tools.h"
#include <stdbool.h>

typedef enum e_TokenType
{
	CINT = 0, //整数
	PLUS, //加法
	MINUS, //减法
	DIV, //乘法
	MUL, //除法
	LPAREN, //左括号
	RPAREN, //右括号
	END_OF_FILE // 字符串末尾结束符号
}ETokenType;

typedef struct Token
{
	ETokenType type;
	DyncString value;
}Token, * LPTOKEN;

extern Token g_currentToken;
extern int g_nPosition;
extern char g_currentChar;

void advance();
bool get_next_token();
void skip_whitespace();
void parser_number(LPDyncString dyncstr);
