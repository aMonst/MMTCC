#include "interpreter.h"
#include <stdio.h>

int expr()
{
	bool bRet = false;
	int result = get_term(&bRet);
	int bEOF = false;
	do
	{
		ETokenType oper = get_oper(&bRet);
		switch (oper)
		{
			case PLUS:
			{
				int num = get_term(&bRet);
				if(bRet)
					result += num;
			}
			break;
		case MINUS:
			{
				int num = get_term(&bRet);
				if(bRet)
					result -= num;
			}
			break;
		case END_OF_FILE:
			printf("%d\n", result);
			bEOF = true;
			break;
		default:
			bRet = false;
			break;
		}
	} while (bRet && !bEOF);
	if (!bRet)
	{
		printf("Syntax Error!\n");
	}

	return 0;
}

int get_term(bool* pValid)
{
	int result = get_factor(pValid);
	int bEOF = false;
	do
	{
		ETokenType oper = get_oper(pValid);
		switch (oper)
		{
		case DIV:
			{
				int num = get_factor(pValid);
				if (*pValid)
					result *= num;
			}
			break;
		case MUL:
			{
				int num = get_factor(pValid);
				if (*pValid)
					result /= num;
			}
			break;
		case PLUS:
		case MINUS:
			{
				g_pPosition--;
				bEOF = true;
			}
			break;
		case END_OF_FILE:
			{
				g_pPosition--;
				bEOF = true;
			}
		}
	} while (pValid && !bEOF);
	
	return result;
}
