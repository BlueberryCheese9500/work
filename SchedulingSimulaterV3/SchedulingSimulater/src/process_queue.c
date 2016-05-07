#include"../include/process_queue.h"
// 프로세스를 복사하여 새로 하나 만들어 카피본 반환
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

Process* pop(Queue* target)	//큐 내용 추출
{
  if(target == NULL || target->head == NULL)
    return NULL;
 
  Process* head = target->head;	//큐의 head 데이터 추출
  Process* poped = copy_Process(target->head);	//추출된 큐의 내용을 복사하여 관리

  target->head = target->head->next;	//추출한head부분에 다음 프로세스(next)정볼를 대입
  free(head);

  return poped;	//추출된 프로세스 데이터 리턴 
}
// 프로세스를 타겟 큐에 삽입.실패시 NULL 리턴
void push(Queue* target, Process* new)	//큐 삽입
{
  if(target == NULL || new == NULL)
    return;

  if(target->head == NULL)	//큐가 비어있었다면
  {	
    target->head = new;	//큐 head에 Process new 를 삽입
    target->tail = target->head;	//data가 1개인 큐이기에 head와 tail 동일
    return;
  }
  target->tail->next = new;	//큐에 내용이 있었다면 새로운 프로세스 셍성
  target->tail = target->tail->next;	//큐 tail에 새로운 프로세스 삽입
  target->tail->next = NULL;	//새로운 프로세스 생성 부분 초기화
}
// 큐 생성, 실패시 NULL 리턴
Queue* new_Queue()
{
  Queue* new = NULL;	//큐 생성, 초기화
  new = (Queue*)malloc(sizeof(Queue));	//생성된 큐 메모리에 동적 할당
  
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
  new->next = NULL;
  return new;
}

