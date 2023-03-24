#include <stdio.h>
#include "interpreter.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>

#define MAX_INPUT_BUFFER 4096
void reset()
{
	memset(g_pszUserBuf, 0x00, MAX_INPUT_BUFFER * sizeof(char));
	gets_s(g_pszUserBuf, MAX_INPUT_BUFFER * sizeof(char));
	g_pPosition = g_pszUserBuf;
}

int main()
{
	g_pszUserBuf = (char*)malloc(MAX_INPUT_BUFFER * sizeof(char));
	while (1)
	{
		printf(">>>");
		reset();
		if (strcmp(g_pszUserBuf, "exit") == 0)
		{
			break;
		}
		bool bValid = false;
		int result = expr(&bValid);
		if (bValid)
		{
			printf("%s=%d\n", g_pszUserBuf, result);
		}
		else
		{
			printf(">>>Syntax Error!\n");
		}

	}

	free(g_pszUserBuf);
	return 0;
}
