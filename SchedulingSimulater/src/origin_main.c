#include"../include/process_queue.h"
/*
#include<stdio.h>
#include<stdlib.h>

// 프로세스
typedef struct Process Process;
struct Process
{
  char name;
  int arrival_time;
  int service_time;
  Process* next;
};
// 큐
typedef struct Queue
{
  Process *head, *tail;  
}Queue;
*/
typedef struct Scheduling_Policy
{
  char name[10];
  void(*scheduling)();
}Scheduling_Policy;

// 커서이동하여 출력
void setCursorMove(int XPos, int YPos)
{
   printf("\033[%d;%dH", YPos+1, XPos+1);
}
// 프로세스를 카피하여 복제된 프로세스 돌려줌, 실패시 NULL리턴
// 받은 프로세스 반드시 메모리 해제
/*
Process* copy_Process(Process* src)
{
  if(src == NULL)
    return NULL;

  Process* copy = NULL;
  copy = (Process*)malloc(sizeof(Process));

  if(copy == NULL)
    return NULL;
  
  copy->name = src->name;
  copy->arrival_time = src->arrival_time;
  copy->service_time = src->service_time;
  copy->next = NULL;
  return copy;
}
*/
// 프로세스를 타겟 큐에서 팝
Process* pop(Queue* target)
{
  if(target == NULL || target->head == NULL)
    return NULL;
 
  Process* head = target->head;
  Process* poped = copy_Process(target->head);

  target->head = target->head->next;
  free(head);

  return poped;
}
// 프로세스를 타겟 큐에 삽입.실패시 NULL 리턴
void push(Queue* target, Process* new)
{
  if(target == NULL || new == NULL)
    return;

  if(target->head == NULL) 
  {
    target->head = new;
    target->tail = target->head;
    return;
  }
  target->tail->next = new;
  target->tail = target->tail->next;
}
// 큐 생성, 실패시 NULL 리턴
Queue* new_Queue()
{
  Queue* new = NULL;
  new = (Queue*)malloc(sizeof(Queue));
  
  if(new == NULL)
    return NULL;

  new->head = NULL;
  new->tail = new->head;
  return new;
}
// 새 프로세스 생성, 실패 시 NULL 리턴
Process* new_Process(char name, int arrival_time, int service_time)
{
  Process* new = NULL;
  new = (Process*)malloc(sizeof(Process));
  new->name = name;
  new->arrival_time = arrival_time;
  new->service_time = service_time;
  return new;
}

// 스케줄링 정책 별 프린트 하는 함수입니다.
// 세 함수 내용 채우면 될 것 같습니다.
void FCFS(Queue* wait_queue, Queue* ready_queue)
{
  printf("\n");
}

void RR(Queue* wait_queue, Queue* ready_queue)
{
  printf("\n");
}

void HRRN(Queue* wait_queue, Queue* ready_queue)
{
  printf("\n");
}

Scheduling_Policy simulater[3] = {{"FCFS",FCFS},{"RR",RR},{"HRRN",HRRN}};

int main(void)
{
  Queue *ready_queue = new_Queue();
  Queue *wait_queue = new_Queue();
  
  int i = 0,time_axis = 0, total_service_time = 0;
  int policy_count = sizeof(simulater)/sizeof(Scheduling_Policy);
  int process_count = 5;
  if(ready_queue == NULL || wait_queue == NULL)
    return;
 
  // DEBUG
  Process* head = NULL;
  
  // 정렬 필요. +additional : 프로세스 삽입 방식 개선.. 
  push(wait_queue,new_Process('A',0,3));
  push(wait_queue,new_Process('B',2,6));
  push(wait_queue,new_Process('C',4,4));
  push(wait_queue,new_Process('D',6,5));
  push(wait_queue,new_Process('E',8,2));

  // 모든 프로세스  수행 시간
  for(head = wait_queue->head ; head!=NULL; head = head->next)
    total_service_time += head->service_time;
  
  printf("<Scheduling Simulater>\n");
  printf("policy / time\n");
  printf("\n");

  system("clear");
  for(i = 0; i < policy_count ; i++)
  { 
    // 스케줄링 정책 이름
    printf("%s",simulater[i].name);
    // 시간 축 출력
    for(time_axis = 0; time_axis<total_service_time; time_axis++)
      printf("\t%d",time_axis);
    printf("\n");

    for(head = wait_queue->head; head!=NULL; head = head->next)
      printf("%c\n",head->name);
      
    simulater[i].scheduling(wait_queue, ready_queue);
  }
}
