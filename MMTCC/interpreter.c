#include "interpreter.h"
#include <stdio.h>


/*
* expr::=term{(PLUS|MINUS)term}
* term::=factor{(DIV|MUL)factor}
* factor::=NUM|{(LPAREN)expr(RPAREN)}
*/
int expr(bool *pValid)
{
	*pValid = true;
	int result = get_term(pValid);
	int bEOF = false;
	do
	{
		switch (g_currentToken.type)
		{
			case PLUS:
			{
				*pValid = eat(&g_currentToken, PLUS);
				int num = get_term(pValid);
				if(*pValid)
					result += num;
			}
			break;
		case MINUS:
			{
				*pValid = eat(&g_currentToken, MINUS);
				int num = get_term(pValid);
				if(*pValid)
					result -= num;
			}
			break;
		}
	} while (g_currentToken.type == PLUS || g_currentToken.type == MINUS);

	return result;
}

int get_term(bool* pValid)
{
	int result = get_factor(pValid);
	int bEOF = false;
	do
	{
		switch (g_currentToken.type)
		{
		case DIV:
			{
				*pValid = eat(&g_currentToken, DIV);
				int num = get_factor(pValid);
				if (*pValid)
					result *= num;
			}
			break;
		case MUL:
			{
				*pValid = eat(&g_currentToken, MUL);
				int num = get_factor(pValid);
				if (*pValid)
					result /= num;
			}
			break;
		}
	} while (g_currentToken.type == DIV || g_currentToken.type == MUL);
	
	return result;
}

int get_factor(bool* pRet)
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
