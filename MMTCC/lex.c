#include "lex.h"
#include <stdio.h>
#include <stdlib.h>

char* g_pszUserBuf = NULL;
char* g_pPosition = NULL;

char get_next_char()
{
	// ��������ַ���β����������������
	if (g_pPosition == '\0')
	{
		return '\0';
	}
	else
	{
		char c = *g_pPosition;
		g_pPosition++;
		return c;
	}
}

bool get_next_token(LPTOKEN pToken)
{
	char c = get_next_char();

	dyncstring_reset(&pToken->value);
	if (is_digit(c))
	{
		dyncstring_catch(&pToken->value, c);
		pToken->type = CINT;
		parser_number(&pToken->value);
	}
	else if (c == '+')
	{
		pToken->type = PLUS;
		dyncstring_catch(&pToken->value, '+');
	}
	else if (c == '-')
	{
		pToken->type = MINUS;
		dyncstring_catch(&pToken->value, '-');
	}
	else if (c == '*')
	{
		pToken->type = DIV;
		dyncstring_catch(&pToken->value, '*');
	}
	else if (c == '/')
	{
		pToken->type = MUL;
		dyncstring_catch(&pToken->value, '/');
	}
	else if(is_space(c))
	{
		skip_whitespace();
		return get_next_token(pToken);
	}
	else if ('\0' == c)
	{
		pToken->type = END_OF_FILE;
	}
	else
	{
		return false;
	}
	return true;
}

int get_factor(bool *pRet)
{
	Token token = { 0 };
	dyncstring_init(&token.value, DEFAULT_BUFFER_SIZE);
	int value = 0;
	if (get_next_token(&token) && token.type == CINT)
	{
		value = atoi(token.value.pszBuf);
		if (pRet)
			*pRet = true;
	}
	else
	{
		if (pRet)
			*pRet = false;
	}
	dyncstring_free(&token.value);

	return value;
}

ETokenType get_oper(bool* pRet)
{
	Token token = { 0 };
	dyncstring_init(&token.value, DEFAULT_BUFFER_SIZE);
	int oper = 0;
	if (get_next_token(&token) && (token.type == PLUS || token.type == MINUS || token.type == DIV || token.type == MUL))
	{
		oper = token.type;
		if (pRet)
			*pRet = true;
	}
	else if (token.type == END_OF_FILE)
	{
		oper = END_OF_FILE;
		if (pRet)
			*pRet = true;
	}
	else
	{
		oper = -1;
		if (pRet)
			*pRet = false;
	}

	dyncstring_free(&token.value);
	return oper;
}


void skip_whitespace()
{
	char c = '\0';
	do
	{
		c = get_next_char();
	} while (is_space(c));

	// �������ǿհ��ַ��ģ��´�Ҫȡ������������Ҫ�ظ�ȡ���ϴ�ȡ�����ַ�
	g_pPosition--;
}

void parser_number(LPDyncString dyncstr)
{
	char c = get_next_char();
	while(is_digit(c))
	{
		dyncstring_catch(dyncstr, c);
		c = get_next_char();
	}

	// �����������ֵģ��´�Ҫȡ������������Ҫ�ظ�ȡ���ϴ�ȡ�����ַ�
	g_pPosition--;
}
