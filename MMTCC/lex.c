#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* g_pszUserBuf;



bool eat(LPTOKEN pToken, ETokenType eType)
{
	if (pToken->type == eType)
	{
		get_next_token();
		return true;
	}

	return false;
}
