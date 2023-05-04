#include "interpreter.h"
#include <stdio.h>
#include "AST.h"

/*
* expr::=term{(PLUS|MINUS)term}
* term::=factor{(DIV|MUL)factor}
* factor::=NUM|{(LPAREN)expr(RPAREN)}
*/
AST* expr(bool *pValid)
{
	*pValid = true;
	AST* pRoot = get_term(pValid);
	int bEOF = false;
	do
	{
		switch (g_currentToken.type)
		{
			case PLUS:
			{
				*pValid = eat(&g_currentToken, PLUS);
				AST* pNumNode = get_term(pValid);
				if (*pValid)
				{
					pRoot = init_opAstNode(PLUS, pRoot, pNumNode);
				}
			}
			break;
		case MINUS:
			{
				*pValid = eat(&g_currentToken, MINUS);
				AST* pNumNode = get_term(pValid);
				if (*pValid)
				{
					pRoot = init_opAstNode(MINUS, pRoot, pNumNode);
				}
			}
			break;
		}
	} while (g_currentToken.type == PLUS || g_currentToken.type == MINUS);

	return pRoot;
}

AST* get_term(bool* pValid)
{
	AST* pRoot = get_factor(pValid);
	int bEOF = false;
	do
	{
		switch (g_currentToken.type)
		{
		case DIV:
			{
				*pValid = eat(&g_currentToken, DIV);
				AST* pNumNode = get_factor(pValid);
				if (*pValid)
				{
					pRoot = init_opAstNode(DIV, pRoot, pNumNode);
				}
			}
			break;
		case MUL:
			{
				*pValid = eat(&g_currentToken, MUL);
				AST*pNumNode = get_factor(pValid);
				if (*pValid)
				{
					pRoot = init_opAstNode(MUL, pRoot, pNumNode);
				}
			}
			break;
		}
	} while (g_currentToken.type == DIV || g_currentToken.type == MUL);

	return pRoot;
}

AST* get_factor(bool* pRet)
{
	if (g_currentToken.type == CINT)
	{
		int value = atoi(g_currentToken.value.pszBuf);
		*pRet = eat(&g_currentToken, CINT);
		return inint_numAstNode(value);
	}
	else
	{
		if (g_currentToken.type == LPAREN)
		{
			bool bValid = true;
			bValid = eat(&g_currentToken, LPAREN);
			AST* pNode = expr(&bValid);
			bValid = eat(&g_currentToken, RPAREN);
			*pRet = bValid;
			return pNode;
		}
	}

	return NULL;
}

int calc(AST* pRoot, bool* pValid)
{
	if (pRoot == NULL || !(*pValid))
	{
		*pValid = false;
		return 0;
	}

	// 如果没有子树，则应该是数字类型，直接返回数字
	if (pRoot->l_node == NULL && pRoot->r_node == NULL)
	{
		NumAst* pNumNode = CONTAINING_RECORD(pRoot, NumAst, pNode);
		return pNumNode->num;
	}

	OpAst* pOpNode = CONTAINING_RECORD(pRoot, OpAst, pNode);
	switch (pOpNode->token.type)
	{
	case PLUS:
		return calc(pRoot->l_node, pValid) + calc(pRoot->r_node, pValid);
	case MINUS:
		return calc(pRoot->l_node, pValid) - calc(pRoot->r_node, pValid);
	case MUL:
		return calc(pRoot->l_node, pValid) / calc(pRoot->r_node, pValid);
	case DIV:
		return calc(pRoot->l_node, pValid) * calc(pRoot->r_node, pValid);
	default:
		*pValid = false;
		return 0;
	}
}

