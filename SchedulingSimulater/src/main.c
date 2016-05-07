//#include"../include/process_queue.h"
#include"../include/scheduling.h"
typedef struct Scheduling_Policy
{
  char name[10];
  void(*scheduling)();
}Scheduling_Policy;

void default_wait_queue(Queue* wait_queue)
{
 // +additional : 프로세스 삽입 방식 개선.. 
  push(wait_queue,new_Process('A',0,3,0));
  push(wait_queue,new_Process('B',2,6,1));
  push(wait_queue,new_Process('C',4,4,2));
  push(wait_queue,new_Process('D',6,5,3));
  push(wait_queue,new_Process('E',8,2,4));
}

int main(void)
{
  Scheduling_Policy simulater[3] = {{"FCFS",FCFS},{"RR",RR},{"HRRN",HRRN}};
  
  Queue *ready_queue = new_Queue();
  Queue *wait_queue = new_Queue();
  
  int i = 0,time_axis = 0;
  int policy_count = sizeof(simulater)/sizeof(Scheduling_Policy);
  int process_count = 5;
 
  current_time = 0;
  Process *head = NULL;

  if(ready_queue == NULL || wait_queue == NULL)
    return;
  
  default_wait_queue(wait_queue);
 
  // 모든 프로세스  수행 시간
  for(head = wait_queue->head ; head!=NULL; head = head->next)
    total_service_time += head->service_time;

  system("clear");
  printf("<Scheduling Simulater>\n");
  printf("policy / time\n");
  
  for(i = 0; i < policy_count ; i++)
  { 
    // 스케줄링 정책 이름
    printf("%s\t",simulater[i].name);
    // 시간 축 출력
    for(time_axis = 0; time_axis<total_service_time+1; time_axis++)
      printf("%-8d",time_axis);
    printf("\n");

    for(head = wait_queue->head; head!=NULL; head = head->next)
      printf("%c\n",head->name);    
    printf("\n");
  }
   
  // 스케줄링 정책 모두 실행
  for(i=0; i < policy_count ;i++)
  {
    simulater[i].scheduling(wait_queue, ready_queue);
    default_wait_queue(wait_queue);
  }
  // 커서 제자리에
  setCursorMove(0,25);
}
