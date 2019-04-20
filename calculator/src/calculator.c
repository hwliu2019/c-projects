/*
 * calculator.c
 *
 *  Created on: 2019��4��6��
 *      Author: Liuhw
 *
 * �沨�����ʽ��ֵ�㷨
 * 1.ѭ��ɨ���﷨��Ԫ����Ŀ��
 * 2.���ɨ�����Ŀ�ǲ�����������ѹ���������ջ����ɨ����һ����Ŀ��
 * 3.���ɨ�����Ŀ��һ����Ԫ����������ջ�Ķ�������������ִ�и����㡣
 * 4.���ɨ�����Ŀ��һ��һԪ����������ջ����ϲ�����ִ�и����㡣
 * 5.������������ѹ���ջ��
 * 6.�ظ�����2-5����ջ�м�Ϊ���ֵ��
 * (1+2*4)*(3+8/2) ->1,2,4,3,8,2,*,+,*,+,/
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "SaStack.h"

#define  _DEBUG

/**���ȼ��жϺ���
 * op:�����������
 */
int GetPriority (const int operator)
{
	switch(operator)
	{
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default :
		return -1;
	}
}

/* ��������������ջ�����ݲ��������㣬Ȼ���ٴ���ջ */
int Compute(SaStack *pDataStack,const char operator)
{
#ifdef _DEBUG
	printf("Compute��%c\n",operator);
	PrintSaStack(pDataStack);
#endif
	double result,n1,n2;

	//���λ����ֵջ��ջ��������
	PopSaStack(pDataStack,&n1);
	PopSaStack(pDataStack,&n2);
	//����
	switch(operator) {
	case '+':
		result = n2 + n1;
		break;
	case '-':
		result = n2 - n1;
		break;
	case '*':
		result = n2 * n1;
		break;
	case '/':
		if(n1==0){
			printf("ERROR����0�쳣��������ֹ��%.1f%c%.1f=%.1f\n",n2,(char)operator,n1,result);
			return -1;//��0���
		}
		result = n2 / n1;
		break;
	}
#ifdef _DEBUG
	printf(" Compute��%.1f%c%.1f=%.1f\n",n2,(char)operator,n1,result);
#endif

	//��������ٴ���ջ
	PushSaStack(pDataStack,result);

	return 0;
}

/* ֻ�в������Ż����ú��� */
int DealOperator(SaStack *pDataStack,SaStack *pOperatorStack,double operator)
{
#ifdef _DEBUG
	printf(" DealOperator��%c\n",(char)operator);
#endif
	double preOperator;//ǰһ��������

	//���pOperatorStack������ջ�ǿ�ջ���߲�����Ϊ��(��
	if (IsEmptySaStack(pOperatorStack) || operator == '(') {
		//����ʽ�׸�������������ʽ'('��ջ

		PushSaStack(pOperatorStack, operator);
		return 0;
	}
	//��ջ������������ǰ������
	PeekSaStack(pOperatorStack,&preOperator);
	//����ǰ������ջ��ջ���������봫��Ĳ������������ȼ��Ƚ�
	if (GetPriority(operator) > GetPriority(preOperator))
	{
		//������������ڵ�ǰջ�����򽫴����������ջ�ȴ���������
		PushSaStack(pOperatorStack,operator);
		return 0;
	}

	int res;
	//�������Ĳ��������ȼ�С�ڵ�ǰջ�������������ݵ�ǰջ�����������м���
	while (GetPriority(operator) <= GetPriority(preOperator))
	{
		//����ǰջ���Ĳ�����ȡ������ֵջ�ж��˵�������ֵ���м���
		PopSaStack(pOperatorStack,&preOperator);

		if((res=Compute(pDataStack,preOperator))<0){
			return res;
		}
		//����������֮�������ջΪ����break;
		if (IsEmptySaStack(pOperatorStack))
		{
			break;
		}
		//�ٴ�ȡջ���������봫��������Ƚ�
		PeekSaStack(pOperatorStack,&preOperator);
	}
	//����������ȼ�����֮���ٽ��´���Ĳ�������ջ
	PushSaStack(pOperatorStack,operator);

	return 0;
}

/*�����⵽��������')',��ִ�иú���������Ϊ��ֵջ�Ͳ�����ջ*/
int DealBracket(SaStack *pDataStack,SaStack *pOperatorStack)
{

	double preOperator;
	//��õ�ǰ�Ĳ�����ջ��ջ��������
	PeekSaStack(pOperatorStack,&preOperator);
	//ֱ���ҵ�Ԥ����Ե������š���Ϊ��ȷ����ʽ����������һ������Ե�
	int res=0;
	while (preOperator != '(')
	{
#ifdef _DEBUG
	printf(" DealBracket��%c\n",(char)preOperator);
#endif
		//��ǰ��������ջȻ����ֵ��ջ�������м���,�����������ȼ����
		//���Ҫ֧�ֵ�Ŀ������ɸ��������ж�Ҫ��ջ������ֵ
		PopSaStack(pOperatorStack,&preOperator);
		//Compute(pDataStack,preOperator);
		if((res=Compute(pDataStack,preOperator))<0){
			return res;//�������ʱֱ�ӷ���
		}
		//Ȼ���ٴ�ȡ����ǰ������ջջ�����������������֡�(��
		PeekSaStack(pOperatorStack,&preOperator);
	}
	//��󽫳��ֵ������ų�ջ����
	PopSaStack(pOperatorStack,&preOperator);
	return 0;
}

/**�����ʾ��Ϣ*/
void ShowHelpMessage()
{
	printf("********************************************************\n");
	printf(" ��������֧��1������,�100���ַ��� '+-*/' �����ʽ����  \n");
	printf(" ֧��������()ָ������˳�� \n");
	printf(" ��ֵ�� '+-*/' ����������������뽫������ \n");
	printf(" �������'='�س���鿴������          \n");
	printf("********************************************************\n");
	printf("��������������ʽ������: (1+2)*(3-8/4)=\n\n");
	fflush(stdout);  //ˢ�»�����
}

/**��ȡ�û�����,ֱ���û�����'='������100���ַ�����ʧ��*/
int GetInput(char in[]) {

	ShowHelpMessage();

	int i = 0;
	char c;
	int cType;//�ַ�����
	int operationable=1;//�����ǲ�����
	while (1) {
		scanf("%c", &c);		//����

		cType = CheckExpressionsChar(c);
		switch (cType) {
		case 0:    //�ӹ��Ƿ��ַ�
			continue;
		case 1:		//number
			operationable=1;
			in[i++] = c;
			break;
		case 2:		//oprator
			if(operationable){
				in[i++] = c;
			}else{
				//�ӹ������Ĳ�����
			}
			operationable=0;
			break;
		case 3://����
			operationable=1;
			in[i++] = c;
			break;
		case 4: //=��
			//Ĩȥĩβ��=��
			//i--;
			in[i] = '\0';
			return i;
		}

		if (i >= 100 ) {
			in[i] = '\0';
			break;//break while(1)
		}
	}

	return i;

}

/**����Ƿ�Ϸ��ַ�,�Ƿ��ַ�����0���Ϸ��ַ����ط�0*/
int CheckExpressionsChar(const char ch) {
	switch (ch) {
	case '=':
		return 4;
	case '(':
	case ')':
		return 3;
	case '+':
	case '-':
	case '*':
	case '/':
		return 2;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		return 1;
	}
	return 0;
}

/**
 * ���м���
 * str:ָ����ʽ�ַ�����ָ��
 * pDataStack:
 */
int HandleInput(char *str,SaStack *pDataStack,SaStack *pOperatorStack)
{
#ifdef _DEBUG
	printf("��ʼ������ʽ��%s\n",str);
#endif
	int i=0;
	double value = 0;   //���ֵ�ֵ
	int isDigital = 0;
	double operator;
	int type;
	 /* ���ʽ�ַ�����������,Ȼ�󽫸����ȼ��ķ���/(*)���м���������ջ�˳�while��ҵ����ȼ���һ��+-*/
	while (str[i] != '\0')
	{ //��ȡ���������
		type=CheckExpressionsChar(str[i]);

		if (str[i] >= '0' && str[i] <= '9')//num
		{
			value = value * 10 + (str[i] - '0');
			isDigital = 1;
		}
		else//operator
		{
			if (isDigital)
			{
				//isDigital = 1˵��value����洢�����֣�������ջ
				//printf(" value��ջ %c:%.0f \n",str[i],value);
				PushSaStack (pDataStack, value);
				//num��־���㣬value������ֵı�������
				isDigital = 0;
				value = 0;
			}
			if(str[i] == ')')
			{
				//����������ţ���
				DealBracket(pDataStack,pOperatorStack);
			}
			else//+-*/(�����
			{
				DealOperator(pDataStack,pOperatorStack,str[i]);
			}
		}
		i++;
	}
	//���isDigital = 1.˵��value���滹����ֵ,������ջ
	if (isDigital)
	{
		PushSaStack(pDataStack,value);
	}
#ifdef _DEBUG
	printf("��ʽ��ջ��ϣ�%s\n",str);
	PrintSaStack(pDataStack);
	PrintSaStack(pOperatorStack);
#endif

	//Ȼ�󽫷������������γ�ջ���㡣���ֳ�ջ�������֮����ٴ���compute����ջ
	while (!IsEmptySaStack(pOperatorStack))
	{
		PopSaStack(pOperatorStack,&operator);
#ifdef _DEBUG
		printf("���㣺%c\n",(char)operator);
#endif
		Compute(pDataStack,operator);
	}

	return 0;
}


int main(void) {

    char in[101];

    GetInput(in);

   	SaStack *pDataStack,*pOperatorStack;      // ��������ָ��ջ�ṹ���ָ��
   	pDataStack = CreateSaStack();  // ���������ֵ��ջ
    pOperatorStack = CreateSaStack();  // ��������������ջ
    HandleInput(in,pDataStack,pOperatorStack);

    //ȡ������ջ���ʣ�µ����֣��������Ĵ�
    double value = 0;   //ֵ
    PopSaStack(pDataStack,&value);
    //��ӡ���
    printf("���������ʽ��%s",in);
    printf(" = %0.2f\n",value);

	return EXIT_SUCCESS;
}


