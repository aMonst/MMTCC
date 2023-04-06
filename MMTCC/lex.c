#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* g_pszUserBuf;

int get_factor(bool *pRet)
{
	int value = 0;
	if (g_currentToken.type == CINT)
	{
		value = atoi(g_currentToken.value.pszBuf);
		*pRet = eat(&g_currentToken, CINT);
	}
	else
	{
		if (g_currentToken.type == LPAREN)
		{
			bool bValid = true;
			bValid = eat(&g_currentToken, LPAREN);
			value = expr(&bValid);
			bValid = eat(&g_currentToken, RPAREN);
			*pRet = bValid;
		}
	}

	return value;
}


bool eat(LPTOKEN pToken, ETokenType eType)
{
	if (pToken->type == eType)
	{
		get_next_token();
		return true;
	}

	return false;
}
