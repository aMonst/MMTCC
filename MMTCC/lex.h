#pragma once
#include "TokenType.h"
#include "Tools.h"
#include <stdbool.h>

extern char* g_pPosition;
extern char* g_pszUserBuf;

typedef struct Token
{
	ETokenType type;
	DyncString value;
}Token, *LPTOKEN;

char get_next_char();
bool get_next_token(LPTOKEN pToken);
void skip_whitespace();
void parser_number(LPDyncString dyncstr);
int get_factor(bool *pRet);
int expr(bool* pValid);
ETokenType get_oper(bool* pRet);

