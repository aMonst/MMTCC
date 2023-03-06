#pragma once
#include "TokenType.h"
#include <stdbool.h>

extern char* g_pPosition;
extern char* g_pszUserBuf;

typedef struct Token
{
	ETokenType type;
	char value[2];
}Token, *LPTOKEN;

bool get_next_token(LPTOKEN pToken);

int expr();
