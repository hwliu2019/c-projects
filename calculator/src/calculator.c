/*
 * calculator.c
 *
 *  Created on: 2019年4月6日
 *      Author: Liuhw
 *
 * 逆波兰表达式求值算法
 * 1.循环扫描语法单元的项目。
 * 2.如果扫描的项目是操作数，则将其压入操作数堆栈，并扫描下一个项目。
 * 3.如果扫描的项目是一个二元运算符，则对栈的顶上两个操作数执行该运算。
 * 4.如果扫描的项目是一个一元运算符，则对栈的最顶上操作数执行该运算。
 * 5.将运算结果重新压入堆栈。
 * 6.重复步骤2-5，堆栈中即为结果值。
 * (1+2*4)*(3+8/2) ->1,2,4,3,8,2,*,+,*,+,/
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "SaStack.h"

#define  _DEBUG

/**优先级判断函数
 * op:运算符或括号
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

/* 将两个操作数出栈、根据操作符计算，然后再次入栈 */
int Compute(SaStack *pDataStack,const char operator)
{
#ifdef _DEBUG
	printf("Compute：%c\n",operator);
	PrintSaStack(pDataStack);
#endif
	double result,n1,n2;

	//依次获得数值栈的栈顶两个数
	PopSaStack(pDataStack,&n1);
	PopSaStack(pDataStack,&n2);
	//计算
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
			printf("ERROR，除0异常，计算中止！%.1f%c%.1f=%.1f\n",n2,(char)operator,n1,result);
			return -1;//除0溢出
		}
		result = n2 / n1;
		break;
	}
#ifdef _DEBUG
	printf(" Compute：%.1f%c%.1f=%.1f\n",n2,(char)operator,n1,result);
#endif

	//计算完成再次入栈
	PushSaStack(pDataStack,result);

	return 0;
}

/* 只有操作符才会进入该函数 */
int DealOperator(SaStack *pDataStack,SaStack *pOperatorStack,double operator)
{
#ifdef _DEBUG
	printf(" DealOperator：%c\n",(char)operator);
#endif
	double preOperator;//前一个操作符

	//如果pOperatorStack操作符栈是空栈或者操作符为‘(’
	if (IsEmptySaStack(pOperatorStack) || operator == '(') {
		//将算式首个操作符或子算式'('入栈

		PushSaStack(pOperatorStack, operator);
		return 0;
	}
	//将栈顶操作符存入前操作符
	PeekSaStack(pOperatorStack,&preOperator);
	//将当前操作符栈的栈顶操作符与传入的操作符进行优先级比较
	if (GetPriority(operator) > GetPriority(preOperator))
	{
		//传入操作符大于当前栈顶，则将传入操作符入栈等待后续计算
		PushSaStack(pOperatorStack,operator);
		return 0;
	}

	int res;
	//如果传入的操作符优先级小于当前栈顶操作符，根据当前栈顶操作符进行计算
	while (GetPriority(operator) <= GetPriority(preOperator))
	{
		//将当前栈顶的操作符取出与数值栈中顶端的两个数值进行计算
		PopSaStack(pOperatorStack,&preOperator);

		if((res=Compute(pDataStack,preOperator))<0){
			return res;
		}
		//如果计算完毕之后操作符栈为空则break;
		if (IsEmptySaStack(pOperatorStack))
		{
			break;
		}
		//再次取栈顶操作符与传入操作符比较
		PeekSaStack(pOperatorStack,&preOperator);
	}
	//进行完毕优先级计算之后，再将新传入的操作符入栈
	PushSaStack(pOperatorStack,operator);

	return 0;
}

/*如果检测到操作符是')',则执行该函数，参数为数值栈和操作符栈*/
int DealBracket(SaStack *pDataStack,SaStack *pOperatorStack)
{

	double preOperator;
	//获得当前的操作符栈的栈顶操作符
	PeekSaStack(pOperatorStack,&preOperator);
	//直到找到预期配对的左括号。因为正确的算式中左右括号一定是配对的
	int res=0;
	while (preOperator != '(')
	{
#ifdef _DEBUG
	printf(" DealBracket：%c\n",(char)preOperator);
#endif
		//当前操作符出栈然后将数值出栈两个进行计算,在括号内优先级最高
		//如果要支持单目运算符可根据类型判断要出栈几个数值
		PopSaStack(pOperatorStack,&preOperator);
		//Compute(pDataStack,preOperator);
		if((res=Compute(pDataStack,preOperator))<0){
			return res;//计算出错时直接返回
		}
		//然后再次取出当前操作符栈栈顶操作符，至到出现‘(’
		PeekSaStack(pOperatorStack,&preOperator);
	}
	//最后将出现的左扩号出栈丢弃
	PopSaStack(pOperatorStack,&preOperator);
	return 0;
}

/**输出提示信息*/
void ShowHelpMessage()
{
	printf("********************************************************\n");
	printf(" 本计算器支持1亿以内,最长100个字符的 '+-*/' 混合算式计算  \n");
	printf(" 支持用括号()指定计算顺序 \n");
	printf(" 数值、 '+-*/' 、及括号以外的输入将被忽略 \n");
	printf(" 最后输入'='回车后查看计算结果          \n");
	printf("********************************************************\n");
	printf("请输入需计算的算式，例如: (1+2)*(3-8/4)=\n\n");
	fflush(stdout);  //刷新缓冲区
}

/**获取用户输入,直到用户输入'='，超过100个字符返回失败*/
int GetInput(char in[]) {

	ShowHelpMessage();

	int i = 0;
	char c;
	int cType;//字符类型
	int operationable=1;//可以是操作符
	while (1) {
		scanf("%c", &c);		//读入

		cType = CheckExpressionsChar(c);
		switch (cType) {
		case 0:    //掠过非法字符
			continue;
		case 1:		//number
			operationable=1;
			in[i++] = c;
			break;
		case 2:		//oprator
			if(operationable){
				in[i++] = c;
			}else{
				//掠过连续的操作符
			}
			operationable=0;
			break;
		case 3://括号
			operationable=1;
			in[i++] = c;
			break;
		case 4: //=号
			//抹去末尾的=号
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

/**检查是否合法字符,非法字符返回0，合法字符返回非0*/
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
 * 进行计算
 * str:指向表达式字符串的指针
 * pDataStack:
 */
int HandleInput(char *str,SaStack *pDataStack,SaStack *pOperatorStack)
{
#ifdef _DEBUG
	printf("开始处理算式：%s\n",str);
#endif
	int i=0;
	double value = 0;   //数字的值
	int isDigital = 0;
	double operator;
	int type;
	 /* 表达式字符串解析函数,然后将高优先级的符号/(*)进行计算重新入栈退出while大家的优先级都一样+-*/
	while (str[i] != '\0')
	{ //获取输入的数字
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
				//isDigital = 1说明value里面存储了数字，将其入栈
				//printf(" value入栈 %c:%.0f \n",str[i],value);
				PushSaStack (pDataStack, value);
				//num标志清零，value存放数字的变量清零
				isDigital = 0;
				value = 0;
			}
			if(str[i] == ')')
			{
				//如果是右括号，则
				DealBracket(pDataStack,pOperatorStack);
			}
			else//+-*/(等情况
			{
				DealOperator(pDataStack,pOperatorStack,str[i]);
			}
		}
		i++;
	}
	//如果isDigital = 1.说明value里面还有数值,将其入栈
	if (isDigital)
	{
		PushSaStack(pDataStack,value);
	}
#ifdef _DEBUG
	printf("算式入栈完毕：%s\n",str);
	PrintSaStack(pDataStack);
	PrintSaStack(pOperatorStack);
#endif

	//然后将符号与数字依次出栈计算。数字出栈计算完成之后回再次在compute中入栈
	while (!IsEmptySaStack(pOperatorStack))
	{
		PopSaStack(pOperatorStack,&operator);
#ifdef _DEBUG
		printf("计算：%c\n",(char)operator);
#endif
		Compute(pDataStack,operator);
	}

	return 0;
}


int main(void) {

    char in[101];

    GetInput(in);

   	SaStack *pDataStack,*pOperatorStack;      // 定义两个指向栈结构体的指针
   	pDataStack = CreateSaStack();  // 创建存放数值的栈
    pOperatorStack = CreateSaStack();  // 创建存放运算符的栈
    HandleInput(in,pDataStack,pOperatorStack);

    //取出数字栈最后剩下的数字，就是最后的答案
    double value = 0;   //值
    PopSaStack(pDataStack,&value);
    //打印结果
    printf("您输入的算式：%s",in);
    printf(" = %0.2f\n",value);

	return EXIT_SUCCESS;
}


