//#include"../include/process_queue.h"
#include"../include/scheduling.h"

// 스케줄링 정책 관련 구조체
typedef struct Scheduling_Policy
{
  char name[10];
  void(*scheduling)();
  int quantum;
}Scheduling_Policy;

// 큐를 초기 상태로 복원
void default_wait_queue(Queue* wait_queue)
{
 // +additional : 프로세스 삽입 방식 개선.. 
  push(wait_queue,new_Process('A',0,3,0));	//큐에 프로세스 데이터 삽입
  push(wait_queue,new_Process('B',2,6,1));	//동일 큐에 이어서 삽입
  push(wait_queue,new_Process('C',4,4,2));
  push(wait_queue,new_Process('D',6,5,3));
  push(wait_queue,new_Process('E',8,2,4));
}

int main(void)
{
  Scheduling_Policy simulater[4] = {{"FCFS",FCFS,0},{"RR(q=1)" ,RR,1},{"RR(q=4)",RR,4},{"HRRN",HRRN,0}};
  
  Queue *ready_queue = new_Queue();	//준비상태 큐 생성
  Queue *wait_queue = new_Queue();	//대기상태 큐 생성
  
  int i = 0, j = 0;
  int policy_count = sizeof(simulater)/sizeof(Scheduling_Policy);
  int process_count = 5;
  Process *head = NULL;	//프로세스 구조체 형의 head 생성, 초기화

  if(ready_queue == NULL || wait_queue == NULL)
    return;
  default_wait_queue(wait_queue);	//초기 대기상태 큐에 프로세스 정책 삽입
 
  time_axis = wait_queue->head->arrival_time;
	//프로세스의 최초 수행시간을 고려하기 위해 첫 프로세스의 수행시작시간을 별도 관리

  // 모든 프로세스  수행 시간
  //초기값 = 큐의 head, null이 아닐동안, 다음 프로세스로 진행
  for(head = wait_queue->head ; head!=NULL; head = head->next)
		  total_service_time += head->service_time;	
  			//큐에 들어온 프로세스의 서비스타임의 총합

  system("clear");
  printf("<Scheduling Simulater>\n");
  printf("policy / time\n");
  
  for(i = 0; i < policy_count ; i++)
  { 
    // 스케줄링 정책 이름
    printf("%s\t",simulater[i].name);
    // 시간 축 출력
    for(j = time_axis; j <total_service_time+time_axis; j++)
      printf("%-8d",j);
    printf("\n");

    for(head = wait_queue->head; head!=NULL; head = head->next)
      printf("%c\n",head->name);    
    printf("\n");
  }
   
  // 스케줄링 정책 모두 실행
  for(i=0; i < policy_count ;i++)
  {
    quantum = simulater[i].quantum;
    simulater[i].scheduling(wait_queue, ready_queue);
    default_wait_queue(wait_queue);
  }
  // 커서 제자리에
  setCursorMove(0,32);
  ProcessSetTable(wait_queue, ready_queue);	//Process set 출력
}
