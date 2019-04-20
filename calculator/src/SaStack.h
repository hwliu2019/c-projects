/*
 * SaStack.h
 *
 */

#ifndef SASTACK_H_
#define SASTACK_H_

#define MAXSIZE 100

/**ջ�ṹ��*/
typedef struct {
	double datas[MAXSIZE];
	/**��ջ���������ݸ���*/
	int iSize;
}SaStack;

SaStack *CreateSaStack(); //����ջ
int PushSaStack(SaStack *, const double ); //��ջ
int PopSaStack(SaStack *, double *); //��ջ
int PeekSaStack(const SaStack *, double *); //�鿴ջ��ֵ
int IsEmptySaStack(const SaStack *); //�ж�ջ�Ƿ�Ϊ��
void PrintSaStack(const SaStack *); //��ӡջ���ݣ����ڵ���

#endif

