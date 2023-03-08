#include "Tools.h"
#include <malloc.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
/*----------------------------动态数组的操作函数-------------------------------*/
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
		error("分配内存失败\n");
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
		return;

	free(str->pszBuf);
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
/*----------------------------End 动态数组的操作函数-------------------------------*/

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
