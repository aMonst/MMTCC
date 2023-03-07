#include <stdio.h>
#include "lex.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>

void reset()
{
	memset(g_pszUserBuf, 0x00, 16 * sizeof(char));
	scanf_s("%s", g_pszUserBuf);
	g_pPosition = g_pszUserBuf;
}

int main()
{
	g_pszUserBuf = (char*)malloc(16 * sizeof(char));
	while (1)
	{
		printf(">>>");
		reset();
		if (strcmp(g_pszUserBuf, "exit") == 0)
		{
			break;
		}
		expr();
	}
	return 0;
}
