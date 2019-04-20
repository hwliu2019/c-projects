/*
 * SaStack.c
 * ����ʵ�ֵ�ջ
 *  Created on: 2019��4��3��
 *      Author: Liuhw
 */

#include <stdio.h>
#include <stdlib.h>
#include "SaStack.h"

/* ����ջ */
SaStack *CreateSaStack()
{
	SaStack *pStack;
	pStack = (SaStack *)malloc(sizeof(*pStack));
	pStack->iSize = 0;
	return pStack;
}

/* ��ջ */
int PushSaStack(SaStack *pStack,const double data)
{
	//�����ջ����ջ�ռ�
	if (pStack->iSize>=MAXSIZE)
	{
		return -1;
	}

	//ѹջ
	pStack->datas[pStack->iSize] = data;
	pStack->iSize++;
	return 0;
}

/*
 * ��ջ
 * pStack:ջָ��
 * pData:ָ���ջ������ָ��
 */
int PopSaStack(SaStack *pStack,double *pData)
{
	//���ջ��Ϊ��
	if (IsEmptySaStack(pStack))
	{
		return -1;
	}

	//���ô�����������ջ��Ԫ��
	*pData = pStack->datas[--(pStack->iSize)];
	return 0;
}

/*
 * ���ջ��ֵ
 * pStack:ջָ��
 * pData:ָ��ջ��������ָ��
 */
int PeekSaStack(const SaStack *pStack,double *pData)
{
	if (IsEmptySaStack(pStack))
	{
		return -1;
	}

	*pData = pStack->datas[pStack->iSize - 1];
	return 0;
}

/*
 * �ж�ջ�Ƿ�Ϊ��
 * Ϊ��ʱ����1�����򷵻�0
 */
int IsEmptySaStack(const SaStack *pStack)
{
	//printf("pStack->iSize:%d \n ",pStack->iSize);
	return (pStack->iSize == 0);
}

/* ��ӡ���ջ��Ԫ�� */
void PrintSaStack(const SaStack *pStack)
{
	int i;
	if (IsEmptySaStack(pStack))
	{
		return ;
	}
	printf("SaStack[");
	for (i = 0 ; i < pStack->iSize; i++)
	{
		printf("%.0f, ",pStack->datas[i]);
	}
	printf("]\n");
}

