#pragma once
#include <stdbool.h>
#define DEFAULT_BUFFER_SIZE 16

// 动态字符串结构，用于保存任意长度的字符串
typedef struct DyncString
{
	int nLength; // 字符长度
	int capacity; //实际分配的空间大小
	char* pszBuf; //保存字符串的缓冲
}DyncString, *LPDyncString;

// 动态字符串初始化
// str: 被初始化的字符串
// size: 初始化字符串缓冲的大小，如果给0则按照默认大小分配空间
void dyncstring_init(LPDyncString str, int size);
// 动态字符串空间释放
void dyncstring_free(LPDyncString str);
//重分配动态字符串大小
void dyncstring_resize(LPDyncString str, int newSize);
//往动态字符串中添加字符
void dyncstring_catch(LPDyncString str, char c);
// 重置动态数组
void dyncstring_reset(LPDyncString str);


bool is_digit(char c);
bool is_space(char c);

void error(char* lpszFmt, ...);
