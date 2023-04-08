#include "Token.h"
#include <memory.h>

Token g_currentToken = { 0 };
char* g_pszUserBuf = NULL;
int g_nPosition = -1;
char g_currentChar = '\0';

void advance()
{
	g_nPosition++;
	// 如果到达字符串尾部，索引不再增加
	if (g_nPosition >= strlen(g_pszUserBuf))
	{
		g_currentChar = '\0';
	}
	else
	{
		g_currentChar = g_pszUserBuf[g_nPosition];
	}
}

void skip_whitespace()
{
	while (is_space(g_currentChar))
	{
		advance();
	}
}

void parser_number(LPDyncString dyncstr)
{
	char c = g_currentChar;
	while(is_digit(c))
	{
		dyncstring_catch(dyncstr, c);
		advance();
		c = g_currentChar;
	}
}

bool get_next_token()
{
	dyncstring_reset(&g_currentToken.value);
	while (g_currentChar != '\0')
	{
		if (is_digit(g_currentChar))
		{
			g_currentToken.type = CINT;
			parser_number(&g_currentToken.value);
			return true;
		}
		else if (is_space(g_currentChar))
		{
			skip_whitespace();
		}
		else
		{
			switch (g_currentChar)
			{
				case '+':
					g_currentToken.type = PLUS;
					dyncstring_catch(&g_currentToken.value, '+');
					advance();
					break;
				case '-':
					g_currentToken.type = MINUS;
					dyncstring_catch(&g_currentToken.value, '-');
					advance();
					break;
				case '*':
					g_currentToken.type = DIV;
					dyncstring_catch(&g_currentToken.value, '*');
					advance();
					break;
				case '/':
					g_currentToken.type = MUL;
					dyncstring_catch(&g_currentToken.value, '/');
					advance();
					break;
				case '(':
					g_currentToken.type = LPAREN;
					dyncstring_catch(&g_currentToken.value, '(');
					advance();
					break;
				case ')':
					g_currentToken.type = RPAREN;
					dyncstring_catch(&g_currentToken.value, ')');
					advance();
					break;
				case '\0':
					g_currentToken.type = END_OF_FILE;
					break;
				default:
					return false;
			}

			return true;
		}
	}

	return true;
}

