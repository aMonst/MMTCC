#pragma once
// 用来存储运算符
// 这里的Token只需要存储它的类型，也就是ETokenType 的数据
#include "Tools.h"
#include "Token.h"
typedef struct OpAst
{
	AST pNode;
	Token token;
}OpAst;

// 用来存储数字
typedef struct NumAst
{
	AST pNode;
	int num;
}NumAst;

AST* init_opAstNode(ETokenType tokenType, NumAst* pLNum, NumAst* pRNum);
AST* inint_numAstNode(int num);

