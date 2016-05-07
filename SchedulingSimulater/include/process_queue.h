#include<stdio.h>
#include<stdlib.h>
#include"process.h"
// 큐
typedef struct Queue
{
  Process *head, *tail;  
}Queue;

Process* copy_Process(Process* src);
Process* pop(Queue* target);
// 프로세스를 타겟 큐에 삽입.실패시 NULL 리턴
void push(Queue* target, Process* new);
// 큐 생성, 실패시 NULL 리턴
Queue* new_Queue();
// 새 프로세스 생성, 실패 시 NULL 리턴
Process* new_Process(char name, int arrival_time, int service_time, int order);

