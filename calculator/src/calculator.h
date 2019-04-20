/*
 * calculator.h
 *
 *  Created on: 2019Äê3ÔÂ26ÈÕ
 *      Author: Liuhw
 */

#include "SaStack.h"

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

int GetPriority (const int operator);

int Compute(SaStack *pDataStack,  char operator);

int DealOperator(SaStack *pDataStack,SaStack *pOperatorStack,double operator);

int DealBracket(SaStack *pDataStack,SaStack *pOperatorStack);

void ShowHelpMessage();

int GetInput(char in[]);

int CheckExpressionsChar(char ch);

double deconstruct(char in[],int start, int end);

double calculating(double number1,double number2,char op);

#endif /* CALCULATOR_H_ */
