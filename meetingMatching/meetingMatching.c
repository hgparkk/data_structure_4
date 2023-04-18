/*
프로그램 내용 : 큐를 이용한 미팅주선 프로그램
실습일 : 2023.04.18
실습자 : 박현규
학번 : 202111678
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 100

typedef struct Student
{
	char name[80];
	char gender[2];
}Element;

typedef struct CircularQueue {
	Element data[MAX_QUEUE_SIZE];
	int front;
	int rear;
}Queue;

void error(char* str)
{
	printf("%s\n", str);
	exit(1);
}

void init_queue(Queue* q) { q->front = q->rear = 0; }
int is_empty(Queue* q) { return q->front == q->rear; }
int is_full(Queue* q) { return q->front == (q->rear + 1) % MAX_QUEUE_SIZE; }
int size(Queue* q) { return(q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Queue* q,Element val)
{
	if (is_full(q))
		error(" 큐 포화 에러");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = val;
}

Element dequeue(Queue* q)
{
	if (is_empty(q))
		error(" 큐 공백 에러");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

Element peek(Queue* q)
{
	if (is_empty(q))
		error(" 큐 공백 에러");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void print_queue(Queue* q, char msg[])
{
	int i, maxi = q->rear;
	if (q->front >= q->rear) maxi += MAX_QUEUE_SIZE;
	printf("%s[%2d]=", msg, size(q));
	for (i = q->front + 1;i <= maxi;i++)
		printf("%s, %s", q->data[i % MAX_QUEUE_SIZE].name, q->data[i%MAX_QUEUE_SIZE].gender);
	printf("\n");
}

void main()
{
	Element e;
	char name[80];
	char gender[2];
	Queue mq;
	Queue fq;
	init_queue(&mq);
	init_queue(&fq);
	while(1)
	{
		printf("고객의 이름은?(종료는 -1) >>");
		scanf("%s", &name);
		if (strcmp(name, "-1") == 0)
		{
			printf("미팅 주선 프로그램을 종료합니다.");
			break;
		}
		else
		{
			printf("성별을 입력(남자는 m, 여자는 f) >>");
			scanf(" %s", &gender);
			if (strcmp("m", gender) == 0)
			{
				strcpy(e.name,name);
				strcpy(e.gender,gender);
				if (is_empty(&fq))
				{
					printf("아직 대상자가 없습니다.\n");
					enqueue(&mq,e);
				}
				else
				{
					Element matchf = dequeue(&fq);
					printf("커플 탄생 : %s과 %s\n", e.name, matchf.name);
				}
			}
			else if (strcmp("f", gender) == 0)
			{
				strcpy(e.name, name);
				strcpy(e.gender, gender);
				if (is_empty(&mq))
				{
					printf("아직 대상자가 없습니다.\n");
					enqueue(&fq, e);
				}
				else
				{
					Element matchm = dequeue(&mq);
					printf("커플 탄생 : %s과 %s\n", matchm.name, e.name);
				}
			}
			else
			{
				printf("잘못된 입력 입니다.\n");
			}
		}
	}
}