#pragma once
#include "lex.h"


AST* expr(bool *pValid);
AST* get_term(bool* pValid);
AST* get_factor(bool *pRet);

int calc(AST* pRoot, bool* pValid); //计算AST 树具体的值
