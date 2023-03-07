#include "lex.h"
#include <stdio.h>
#include <stdlib.h>

char* g_pszUserBuf = NULL;
char* g_pPosition = NULL;

bool get_next_token(LPTOKEN pToken)
{
	char* sz = g_pPosition;
	g_pPosition++;
	pToken->value[0] = '\0';
	if (*sz >= '0' && *sz <= '9')
	{
		pToken->type = CINT;
		pToken->value[0] = *sz;
		return true;
	}
	else if (*sz == '+')
	{
		pToken->type = PLUS;
		pToken->value[0] = *sz;
		return true;
	}
	else if(*sz == '-')
	{
		pToken->type = MINUS;
		pToken->value[0] = '-';
		return true;
	}
	else
	{
		pToken->value[0] = '\0';
		return false;
	}
}

int expr()
{
	int val1 = 0, val2 = 0;
	Token token = { 0 };
	if (get_next_token(&token) && token.type == CINT)
	{
		val1 = atoi(token.value);
	}
	else
	{
		printf("首个字符必须是整数\n");
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
		val2 = atoi(token.value);
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