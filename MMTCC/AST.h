#pragma once
// �����洢�����
// �����Tokenֻ��Ҫ�洢�������ͣ�Ҳ����ETokenType ������
#include "Tools.h"
#include "Token.h"
typedef struct OpAst
{
	AST pNode;
	Token token;
}OpAst;

// �����洢����
typedef struct NumAst
{
	AST pNode;
	int num;
}NumAst;

AST* init_opAstNode(ETokenType tokenType, NumAst* pLNum, NumAst* pRNum);
AST* inint_numAstNode(int num);

