/*
프로그램 내용 : 두 스택으로 구현된 큐
실습일 : 2023.04.17
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int Element;
typedef struct stack
{
	Element data[MAX_STACK_SIZE];
	int top;
} Stack;

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

void init_stack(Stack* s) { s->top = -1; }
int is_empty(Stack* s) { return s->top == -1; }
int is_full(Stack* s) { return s->top == MAX_STACK_SIZE; }
int size(Stack* s) { return s->top + 1; }

void push(Stack* s, Element e)
{
	if (is_full(s))
		error("스택 포화 에러");
	s->data[++s->top] = e;
}

Element pop(Stack* s)
{
	if (is_empty(s))
		error("스택 공백 에러");
	return s->data[s->top--];
}

Element peek(Stack* s)
{
	if (is_empty(s))
		error("스택 공백 에러");
	return s->data[s->top];
}

Element dequeue(Stack* s1, Stack* s2)
{
	if (is_empty(s2))
		if (is_empty(s1))
			error(" 큐 공백 에러");
	int sizeStack = size(s1);
	if (is_empty(s2)) 
	{
		for(int i=0;i<sizeStack;i++)
		{
			push(s2,pop(s1));
		}
	}
	return pop(s2);
}

void print_queue(Stack s1,Stack s2, char msg[])
{
	int i;
	int start = size(&s2);
	printf("%s[%2d]= ", msg, size(&s1)+size(&s2));
	for (i = start-1; i >= 0; i--)
		printf("%2d", s2.data[i]);
	for (i = 0; i < size(&s1); i++)
		printf("%2d", s1.data[i]);
	printf("\n");
}

void main()
{
	Stack s1;
	Stack s2;
	Element e;
	int i;
	init_stack(&s1);
	init_stack(&s2);
	for (i = 1; i < 10; i++)
		push(&s1,i);
	print_queue(s1, s2, "큐 enqueue 9회");
	printf("\tdequeue() --> %d\n", dequeue(&s1, &s2));
	printf("\tdequeue() --> %d\n", dequeue(&s1, &s2));
	printf("\tdequeue() --> %d\n", dequeue(&s1, &s2));
	print_queue(s1, s2, "큐 dequeue 3회");
}