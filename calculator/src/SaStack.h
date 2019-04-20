/*
 * SaStack.h
 *
 */

#ifndef SASTACK_H_
#define SASTACK_H_

#define MAXSIZE 100

/**栈结构体*/
typedef struct {
	double datas[MAXSIZE];
	/**堆栈内现有数据个数*/
	int iSize;
}SaStack;

SaStack *CreateSaStack(); //创建栈
int PushSaStack(SaStack *, const double ); //入栈
int PopSaStack(SaStack *, double *); //出栈
int PeekSaStack(const SaStack *, double *); //查看栈顶值
int IsEmptySaStack(const SaStack *); //判断栈是否为空
void PrintSaStack(const SaStack *); //打印栈内容，用于调试

#endif

