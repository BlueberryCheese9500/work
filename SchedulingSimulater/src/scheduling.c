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

void printService(int x, int current_process, int service_time)
{
  int i = 0;
  // 커서 옴겨서
  setCursorMove(x, ycur+current_process);
  // 서비스 타임 만큼 찍는다.  
  for(i = 0; i < service_time ; i++)
  {
    printf("%s",str);
    xcur += 8;
  }
}

void FCFS(Queue* wait_queue, Queue* ready_queue)
{
  int time = 0;
  xcur = start;
  ycur = 3;
  Process* current = NULL;

  setCursorMove(xcur,ycur);
  
  // FCFS 찍기 
  while(time < total_service_time && wait_queue->head!=NULL)
  {
    current = pop(wait_queue);
    printService(xcur, current->order, current->service_time);
    time += current->service_time;
    free(current);
  }
}

void RR(Queue* wait_queue, Queue* ready_queue)
{
  int time = 0;
  xcur = start;
  ycur = 10;
  setCursorMove(xcur,ycur);
  
  // RR 찍기 
  printf("RR 우와와와와");

  // RR end
}

void HRRN(Queue* wait_queue, Queue* ready_queue)
{
  xcur = start;
  ycur = 17;
  setCursorMove(xcur,ycur);
  /* HRRN 찍기 */
  printf("HRRN 우와와와와");
  /* HRRN 찍기 */
  printf("\n");
}

