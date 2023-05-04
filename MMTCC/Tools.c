#include "Tools.h"
#include <malloc.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
/*----------------------------��̬����Ĳ�������-------------------------------*/
void dyncstring_init(LPDyncString str, int size)
{
	if (NULL == str)
		return;

	if (size == 0)
		str->capacity = DEFAULT_BUFFER_SIZE;
	else
		str->capacity = size;
	str->nLength = 0;
	str->pszBuf = (char*)malloc(sizeof(char) * str->capacity);
	if (NULL == str->pszBuf)
	{
		error("�����ڴ�ʧ��\n");
	}

	memset(str->pszBuf, 0x00, sizeof(char) * str->capacity);
}

void dyncstring_free(LPDyncString str)
{
	if (NULL == str)
		return;

	str->capacity = 0;
	str->nLength = 0;
	if (str->pszBuf == NULL)
	{
		return;
	}

	free(str->pszBuf);
	str->pszBuf = NULL;
}

void dyncstring_resize(LPDyncString str, int newSize)
{
	int size = str->capacity;
	for (; size < newSize; size = size * 2);
	char* pszStr = (char*)realloc(str->pszBuf, size);
	str->capacity = size;
	str->pszBuf = pszStr;
}

void dyncstring_catch(LPDyncString str, char c)
{
	if (str->capacity == str->nLength + 1)
	{
		dyncstring_resize(str, str->capacity + 1);
	}

	str->pszBuf[str->nLength] = c;
	str->nLength++;
}

void dyncstring_reset(LPDyncString str)
{
	dyncstring_free(str);
	dyncstring_init(str, DEFAULT_BUFFER_SIZE);
}
/*----------------------------End ��̬����Ĳ�������-------------------------------*/

void error(char* lpszFmt, ...)
{
	char szBuf[1024] = "";
	va_list arg;
	va_start(arg, lpszFmt);
	vsnprintf(szBuf, 1024, lpszFmt, arg);
	va_end(arg);

	printf(szBuf);
	exit(-1);
}

bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

extern void insert_lNode(AST* pRoot, AST* pNode)
{
	if (pRoot != NULL)
	{
		pRoot->l_node = pNode;
	}
}

extern void insert_rNode(AST* pRoot, AST* pNode)
{
	if (pRoot != NULL)
	{
		pRoot->r_node = pNode;
	}
}

extern AST* get_lNode(AST* pRoot)
{
	if (pRoot != NULL)
	{
		return pRoot->l_node;
	}

	return NULL;
}

extern AST* get_rNode(AST* pRoot)
{
	if (pRoot != NULL)
	{
		return pRoot->r_node;
	}

	return NULL;
}

extern free_ast(AST* pRoot)
{
	if (pRoot != NULL)
	{
		free_ast(pRoot->l_node);
		free_ast(pRoot->r_node);
		free(pRoot);
		pRoot = NULL;
	}
}
