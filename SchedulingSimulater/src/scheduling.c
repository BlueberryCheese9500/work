#include"../include/scheduling.h"

/*
 * current_time
 * total_service_time
 * */

int start = 8;
char str[] = "oooooooo";
int str_size = sizeof(str)/sizeof(char)-1;

// 커서이동하여 출력
void setCursorMove(int XPos, int YPos)
{
   printf("\033[%d;%dH", YPos+1, XPos+1);
}

void printService(int current_process, int service_time)
{
  int i = 0;
  // 커서 옴겨서
  setCursorMove(xcur, ycur+current_process);
  // 서비스 타임 만큼 찍는다. 
  for(i = 0; i < service_time ; i++)
  {
    printf("%s",str);
    xcur += str_size;
  }

}

void FCFS(Queue* wait_queue, Queue* ready_queue)
{
  // NULL 처리
  if(wait_queue == NULL) return;
  if(wait_queue->head == NULL) return;

  int time = time_axis;
  xcur = start;
  ycur = 3;
  Process* current = NULL;

  setCursorMove(xcur,ycur);  
  
  // FCFS 찍기 
  while(time < total_service_time+time_axis && wait_queue->head!=NULL)
  {
    // 주욱 뽑아서 순차적으로 실행시킨다.
    current = pop(wait_queue);
    printService(current->order, current->service_time);
    time += current->service_time;
    free(current);
  }
}

void RR(Queue* wait_queue, Queue* ready_queue)
{
  // NULL 처리
  if(wait_queue == NULL) return;
  if(wait_queue->head == NULL) return;

  int time = 0, time_flow = 0;
  const int quantum = 4;
  xcur = start;
  ycur = 10;
  Process* current = NULL;
  // 커서 초기화
  setCursorMove(xcur,ycur);
  
  // RR 찍기
  
  while(time < total_service_time)
  {
    // 서비스 하는 동안 들어온 프로세스를 먼저 큐에 넣는다.
    while(wait_queue->head != NULL)
    {
      if(wait_queue->head->arrival_time <= time)
        push(ready_queue, pop(wait_queue));
      else
        break;
    }
    
    if(current != NULL)
      push(ready_queue, current);

    if(ready_queue->head != NULL)
    {
      // 큐에 뭔가가 있을 때 하나 꺼내서
      current = pop(ready_queue);
      // 서비스 타임과 퀀텀을 비교하여 작은 쪽을 실행시킨다.
      time_flow = current->service_time < quantum ? current->service_time : quantum;
      printService(current->order,time_flow);
      // 실행하고 난 뒤, 프로세스 상태 업데이트
      current->service_time -= quantum;
      // 만일 수행이 끝났다면 프리시키고
      if(current->service_time <= 0)
        free(current);
    }

   // 시간 업데이트
   time += time_flow;
  }
}

float calc_process_priority(Process* p, int time)
{
  printf("%c %f %d",p->name ,(float)time / p->service_time, time);
  return time / p->service_time; 
}

Process* choose_process_by_minpriority(Queue* queue, int time)
{
  // NULL 처리
  if(queue == NULL) return NULL;
  if(queue->head == NULL) return NULL;

  Process *ret = NULL, *prev_ret = NULL, *head = NULL, *tmp = NULL;
 
  for(tmp = head = queue->head; head != NULL; head = head->next)
  {  
      if(calc_process_priority(head, time) < calc_process_priority(tmp, time))
      {
        prev_ret = tmp;
        ret = head;
        printf("%c",tmp->name);
      }  
      tmp = head;
  }
//  prev_ret->next = ret->next;
  
  return ret;
}

// HRRN
void HRRN(Queue* wait_queue, Queue* ready_queue)
{/*
 // NULL 처리
  if(wait_queue == NULL) return;
  if(wait_queue->head == NULL) return;

  // 시간 축 (첫번째 프로세스 시작 시간에 따른 시작 점 설정)
  int time  = time_axis;
  float priority = 0.0;
  xcur = start;
  ycur = 17;
  
  Process* current = NULL;
  // 커서 설정
  setCursorMove(xcur,ycur);


    current = pop(wait_queue);
 // HRRN 찍기 
  while(time < total_service_time && wait_queue->head != NULL)
  {
    // 일단 먼저 온거 실행 
    printService(current->order, current->service_time);
    time += current->service_time;
    free(current);

    // 다음 프로세스 경정
    current = choose_process_by_minpriority(wait_queue, time);
    if(current == NULL)
      return;
  }
  */
}



