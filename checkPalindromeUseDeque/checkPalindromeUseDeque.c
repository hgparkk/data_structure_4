/*
프로그램 내용 : 덱을 이용한 회문 검사
실습일 : 2023.04.18
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;
Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char* str)
{
	printf("%s\n", str);
	exit(1);
}

void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
	if (is_full())
		error(" 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

Element dequeue()
{
	if (is_empty())
		error(" 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

Element peek()
{
	if (is_empty())
		error(" 큐 공백 에러");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}

void print_queue(char msg[])
{
	int i, maxi = rear;
	if (front >= rear) maxi += MAX_QUEUE_SIZE;
	printf("%s[%2d]=", msg, size());
	for (i = front + 1;i <= maxi;i++)
		printf("%2d", data[i % MAX_QUEUE_SIZE]);
	printf("\n");
}

void init_deque() { init_queue(); }
void add_rear(Element val) { enqueue(val); }
Element delete_front() { return dequeue(); }
Element get_front() { return peek(); }

void add_front(Element val)
{
	if (is_full())
		error(" 덱 포화 에러");
	data[front] = val;
	front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Element delete_rear()
{
	int prev = rear;
	if (is_empty())
		error(" 덱 공백 에러");
	rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return data[prev];
}

Element get_rear()
{
	if (is_empty())
		error(" 덱 공백 에러");
	return data[rear];
}

void print_deque(char msg[]) { print_queue(msg); }

void check_palindrome(char expr[])
{
	char c;
	char renew[80];
	char reverse[80];
	int i = 0;
	init_deque();
	while (expr[i] != '\0')
	{
		c = expr[i++];
		if ((c >= 'A') && (c <= 'Z'))
		{
			c = c - 'A' + 'a';
			add_rear(c);
		}
		else if (c == '.' || c == ',' || c == '!' || c == '?' || c == ' ' || c == '\'')
		{

		}
		else
		{
			add_rear(c);
		}
	}

	i = 0;

	while (rear >= front+2)
	{
		renew[i] = delete_front();
		reverse[i++] = delete_rear();
	}
	renew[i] = '\0';
	reverse[i] = '\0';

	if (strcmp(renew, reverse) == 0)
		printf("이 문자열은 회문입니다.");
	else
		printf("이 문자열은 회문이 아닙니다.");
}

void main()
{
	char expr[80];
	printf("문자열을 입력하세요 >>");
	scanf("%[^\n]", &expr);
	check_palindrome(expr);
}