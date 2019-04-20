/*
 * SaStack.c
 * 数组实现的栈
 *  Created on: 2019年4月3日
 *      Author: Liuhw
 */

#include <stdio.h>
#include <stdlib.h>
#include "SaStack.h"

/* 创建栈 */
SaStack *CreateSaStack()
{
	SaStack *pStack;
	pStack = (SaStack *)malloc(sizeof(*pStack));
	pStack->iSize = 0;
	return pStack;
}

/* 入栈 */
int PushSaStack(SaStack *pStack,const double data)
{
	//如果入栈超出栈空间
	if (pStack->iSize>=MAXSIZE)
	{
		return -1;
	}

	//压栈
	pStack->datas[pStack->iSize] = data;
	pStack->iSize++;
	return 0;
}

/*
 * 出栈
 * pStack:栈指针
 * pData:指向出栈的数据指针
 */
int PopSaStack(SaStack *pStack,double *pData)
{
	//如果栈内为空
	if (IsEmptySaStack(pStack))
	{
		return -1;
	}

	//利用传出参数传出栈顶元素
	*pData = pStack->datas[--(pStack->iSize)];
	return 0;
}

/*
 * 获得栈顶值
 * pStack:栈指针
 * pData:指向栈顶的数据指针
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
 * 判断栈是否为空
 * 为空时返回1，否则返回0
 */
int IsEmptySaStack(const SaStack *pStack)
{
	//printf("pStack->iSize:%d \n ",pStack->iSize);
	return (pStack->iSize == 0);
}

/* 打印输出栈中元素 */
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

