#pragma once
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
