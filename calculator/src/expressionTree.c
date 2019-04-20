/*
 * expressionTree.c
 *
 * 根据一个合法的表达式字符串生成表达式树
 *
 * 表达式树数据结构：所有叶子节点都是数值；所有非叶子节点都是运算符；用树的层级结构代表运算符优先级；
 * 用广度优先遍历逐级计算结果后，根节点上即为整个表达式的结果。
 *
 * 表达式(1+2*4)*(3+8/2)的树结构表示为：
 *
 *       *
 *   +       +
 * 1   *    3  /
 *   2  4    8  2
 *
 *  Created on: 2019年4月6日
 *      Author: Liuhw
 *
 */


//TODO:待完成,现阶段用栈实现了逆波兰式表达式的计算
