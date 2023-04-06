#pragma once
#include "Tools.h"
#include <stdbool.h>

typedef enum e_TokenType
{
	CINT = 0, //����
	PLUS, //�ӷ�
	MINUS, //����
	DIV, //�˷�
	MUL, //����
	LPAREN, //������
	RPAREN, //������
	END_OF_FILE // �ַ���ĩβ��������
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
