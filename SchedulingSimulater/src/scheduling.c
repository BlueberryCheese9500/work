#include"../include/scheduling.h"

int start = 8;
char str[] = {177,177,177,177,177,177,177,177,'\0'};
int str_size = sizeof(str)/sizeof(char)-1;

// 커서이동하여 출력
void setCursorMove(int XPos, int YPos)
{
   printf("\033[%d;%dH", YPos+1, XPos+1);
}

// 주어진 프로세스의 차트 라인에
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
    // 만일 프로세스가 할일이 남아 아래에서 해제되지 않았다면,
    // 다시 큐로 집어넣는다.
    if(current != NULL)
      push(ready_queue, current);

    // 큐에 뭔가가 있을 때 하나 꺼내서
    if(ready_queue->head != NULL)
    {
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

// 우선 순위 계산 
float priorty(Process * p,int time)
{
    return (time-(p->arrival_time)+p->service_time)/p->service_time;  
}

// HRRN
void HRRN(Queue* wait_queue, Queue* ready_queue)
{
  // NULL 처리
  if(wait_queue == NULL) return;
  if(wait_queue->head == NULL) return;

  // 커서 세팅
  int time=0;
  xcur = start;
  ycur = 17;

  Process*list=NULL;
  Process*temp=NULL;

  setCursorMove(xcur,ycur);
  
  while(time<total_service_time)
  {
    while(wait_queue->head!=NULL)//input and sort list
    { 
      temp=pop(wait_queue);
      float p=priorty(temp,time);
      Process * search;

      if(list==NULL)
        list=temp;
      else if(p>1 && p>priorty(list,time))
      {
        temp->next=list;
        list=temp;
      }
      else
      { 
        search=list;
        while(search->next!=NULL)
          search=search->next;
        search->next=temp;
      }
    }
    printService(list->order,list->service_time);
    time+=list->service_time;
    list=list->next;
    while(list!=NULL)//push queue
    {
      push(wait_queue,copy_Process(list));
      list=list->next;
    }
  }
}



