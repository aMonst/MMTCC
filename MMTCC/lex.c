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
	else if(is_space(c))
	{
		skip_whitespace();
		return get_next_token(pToken);
	}
	else
	{
		switch (c) {
		case '+':
			pToken->type = PLUS;
			break;
		case '-':
			pToken->type = MINUS;
			break;
		case '*':
			pToken->type = DIV;
			break;
		case '/':
			pToken->type = MUL;
			break;
		case '(':
			pToken->type = LPAREN;
			break;
		case ')':
			pToken->type = RPAREN;
			break;
		case '\0':
			pToken->type = END_OF_FILE;
			break;
		default:
			return false;
		}
	}

	return true;
}

int get_factor(bool *pRet)
{
	Token token = { 0 };
	dyncstring_init(&token.value, DEFAULT_BUFFER_SIZE);
	int value = 0;
	if (get_next_token(&token))
	{
		if (token.type == CINT)
		{
			value = atoi(token.value.pszBuf);
			if (pRet)
				*pRet = true;
		}
		else
		{
			if (token.type == LPAREN)
			{
				bool bValid = true;
				value = expr(&bValid);
				if (!bValid)
					*pRet = false;

				if (get_next_token(&token) && token.type == RPAREN)
					*pRet = true;
				else
					*pRet = false;
			}
		}
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
	if (get_next_token(&token) && (token.type == PLUS || token.type == MINUS || token.type == DIV || token.type == MUL || token.type == LPAREN || token.type == RPAREN))
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
