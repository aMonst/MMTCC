#include "AST.h"
#include <malloc.h>
#include <memory.h>

AST* init_opAstNode(ETokenType tokenType, NumAst* pLNum, NumAst* pRNum)
{
	OpAst* pNode = malloc(sizeof(OpAst));
	memset(pNode, 0x00, sizeof(OpAst));
	pNode->pNode.l_node = pLNum;
	pNode->pNode.r_node = pRNum;
	pNode->token.type = tokenType;
	return pNode;
}

AST* inint_numAstNode(int num)
{
	NumAst* pNode = malloc(sizeof(NumAst));
	memset(pNode, 0x00, sizeof(NumAst));
	pNode->num = num;
	return pNode;
}
