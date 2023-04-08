#pragma once
#include "Token.h"
#include "Tools.h"
#include <stdbool.h>
#include <memory.h>

extern char* g_pszUserBuf;
bool eat(LPTOKEN pToken, ETokenType eType);
