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
  int time = time_axis;
  xcur = start;
  ycur = 3;
  Process* current = NULL;

  setCursorMove(xcur,ycur);  
  
  // FCFS 찍기 
  while(time < total_service_time+time_axis && wait_queue->head!=NULL)
  {
    current = pop(wait_queue);
    printService(current->order, current->service_time);

    time += current->service_time;
    free(current);
  }
}

void RR(Queue* wait_queue, Queue* ready_queue)
{
  int time = time_axis, time_flow = 0;
  const int quantum = 1;
  xcur = start;
  ycur = 10;
  Process* current = NULL;
  Process* head = NULL;
  
  setCursorMove(xcur,ycur);
  
  // RR 찍기 
  while(time <= total_service_time+time_axis)
  { 
   while(wait_queue->head != NULL)
   {
     if(wait_queue->head->arrival_time <= time)
      push(ready_queue, pop(wait_queue));
     else
       break;
   }

   if(ready_queue->head != NULL)
   {
     current = pop(ready_queue);
     time_flow = current->service_time < quantum ? current->service_time : quantum;
     printService(current->order,time_flow);
     current->service_time -= quantum;

     if(current->service_time <= 0)
       free(current);
     else
       push(ready_queue,current);
   }
   time += time_flow;
  }
}

void HRRN(Queue* wait_queue, Queue* ready_queue)
{
  int time = time_axis;
  xcur = start;
  ycur = 17;
  setCursorMove(xcur,ycur);
  /* HRRN 찍기 */
  printService(1,2);
  /* HRRN 찍기 */
  printf("\n");
}

