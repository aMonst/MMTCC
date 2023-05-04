#pragma once
#include <stdbool.h>
#define DEFAULT_BUFFER_SIZE 16

// ��̬�ַ����ṹ�����ڱ������ⳤ�ȵ��ַ���
typedef struct DyncString
{
	int nLength; // �ַ�����
	int capacity; //ʵ�ʷ���Ŀռ��С
	char* pszBuf; //�����ַ����Ļ���
}DyncString, *LPDyncString;

// ��̬�ַ�����ʼ��
// str: ����ʼ�����ַ���
// size: ��ʼ���ַ�������Ĵ�С�������0����Ĭ�ϴ�С����ռ�
void dyncstring_init(LPDyncString str, int size);
// ��̬�ַ����ռ��ͷ�
void dyncstring_free(LPDyncString str);
//�ط��䶯̬�ַ�����С
void dyncstring_resize(LPDyncString str, int newSize);
//����̬�ַ���������ַ�
void dyncstring_catch(LPDyncString str, char c);
// ���ö�̬����
void dyncstring_reset(LPDyncString str);


bool is_digit(char c);
bool is_space(char c);

void error(char* lpszFmt, ...);

// ��������﷨���Ĳ���
typedef struct AST
{
	struct AST* l_node;
	struct AST* r_node;
}AST;

extern free_ast(AST* pRoot);

#ifndef CONTAINING_RECORD
#define CONTAINING_RECORD(address, type, field) ((type *)( \
                                                  (char*)(address) - \
                                                  (char*)(&((type *)0)->field)))
#endif
