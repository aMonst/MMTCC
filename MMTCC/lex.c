#include "lex.h"
#include <stdio.h>
#include <stdlib.h>

char* g_pszUserBuf = NULL;
char* g_pPosition = NULL;

char get_next_char()
{
	// 如果到达字符串尾部，索引不再增加
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

int expr()
{
	int val1 = 0, val2 = 0;
	Token token = { 0 };

	if (get_next_token(&token) && token.type == CINT)
	{
		val1 = atoi(token.value.pszBuf);
	}
	else
	{
		printf("首个操作数必须是整数\n");
		return -1;
	}

	int oper = 0;
	if (get_next_token(&token) && (token.type == PLUS || token.type == MINUS))
	{
		oper = token.type;
	}
	else
	{
		printf("第二个字符必须是操作符， 当前只支持+/-\n");
		return -1;
	}

	if (get_next_token(&token) && token.type == CINT)
	{
		val2 = atoi(token.value.pszBuf);
	}
	else
	{
		printf("操作符后需要跟一个整数\n");
		return -1;
	}


	switch (oper)
	{
	case PLUS:
		{
			printf("%d+%d=%d\n", val1, val2, val1 + val2);
		}
		break;
	case MINUS:
		{
			printf("%d-%d=%d\n", val1, val2, val1 - val2);
		}
		break;
	default:
		printf("未知的操作!\n");
		break;
	}
}

void skip_whitespace()
{
	char c = '\0';
	do
	{
		c = get_next_char();
	} while (is_space(c));

	// 遇到不是空白字符的，下次要取用它，这里需要重复取用上次取出的字符
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

	// 遇到不是数字的，下次要取用它，这里需要重复取用上次取出的字符
	g_pPosition--;
}
