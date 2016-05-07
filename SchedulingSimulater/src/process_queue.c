#include"../include/process_queue.h"

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
  copy->order = src->order;
  copy->next = NULL;
  return copy;
}

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
Process* new_Process(char name, int arrival_time, int service_time, int order)
{
  Process* new = NULL;
  new = (Process*)malloc(sizeof(Process));
  new->name = name;
  new->arrival_time = arrival_time;
  new->service_time = service_time;
  new->order = order;
  return new;
}

