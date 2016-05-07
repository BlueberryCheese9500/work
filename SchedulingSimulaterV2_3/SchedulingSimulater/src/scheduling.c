#include"../include/scheduling.h"

// 시간 축 위치, 수행결과 표시할 문자열, 문자열크기
int start = 8;
char str[] = {177,177,177,177,177,177,177,177,'\0'};
int str_size = sizeof(str)/sizeof(char)-1;


// 커서이동하여 출력
//CUI 환경에서 커서(|)의 이동을 이용하여 그래프 출력
void setCursorMove(int XPos, int YPos)
{
   printf("\033[%d;%dH", YPos+1, XPos+1);
}

// 프로세스의 해당 라인에
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

void ProcessSetTable(Queue* wait_queue, Queue* ready_queue)	//ProesssetTable 출력
{
	Process* current = NULL;	//진행중 Process 초기화
	
	char part[] = "---------------------------------------------"; 	//45개가로
	char part2[] = "||";
	
	printf("%s\n%s Process %s Arrival Time %s Service Time %s\n",part, part2, part2, part2, part2);

	while(wait_queue->head != NULL)
	{
			current = pop(wait_queue);

			printf("%s\n",part);
			printf("%s    %c    %s",part2, current->name, part2);	//Process Name
			printf("      %d       %s",current->arrival_time, part2);	//Arrival Time
			printf("       %d      %s\n",current->service_time, part2);	//Service TIme

			free(current);
	}
	printf("%s\n",part);
}


void FCFS(Queue* wait_queue, Queue* ready_queue)
{
  int time = 0;
  xcur = start;	//커서의 x 위치 초기화
  ycur = 3;	//커서의y 위치 초기화
  Process* current = NULL;	//현재 진행중인 process 초기화

  setCursorMove(xcur,ycur);  //커서 초기위치로 이동
  
  // FCFS 찍기 
  while(time < total_service_time && wait_queue->head!=NULL)
  {
    current = pop(wait_queue);
    printService(current->order, current->service_time);

    time += current->service_time;
    free(current);
  }
}

void RR(Queue* wait_queue, Queue* ready_queue)
{
  int time = 0, time_flow = 0;
  const int RR_quantum = quantum;
  xcur = start;
  ycur += 7;
  Process* current = NULL;
  
  setCursorMove(xcur,ycur);
  
  // RR 찍기 
  // 총 수행시간 동안
  while(time < total_service_time)
  { 
    // 큐에 수행시간 동안 들어온 새 프로세스를 담는다.
    while(wait_queue->head != NULL)
    {
      if(wait_queue->head->arrival_time <= time)
        push(ready_queue, pop(wait_queue));
      else
        break;
    }
     // 프로세스가 실행이 남아 아래서 해제가 안됬을 경우 
     // 다시 준비 큐에 삽입
    if(current != NULL)
      push(ready_queue, current);
    // 레디 큐에 프로세스가 있을 경우
    if(ready_queue->head != NULL)
    {
      // 꺼내서 수행시키고, 시간 업데이트
      current = pop(ready_queue);
      // 수행시간은 할당된 시간과 서비스 시간 중 작은 것으로 한다.
      time_flow = current->service_time < RR_quantum ? current->service_time : RR_quantum;
      printService(current->order,time_flow);
      current->service_time -= RR_quantum;
      // 만일 프로세스가 다 수행되었다면 메모리 해제
      if(current->service_time <= 0)
        free(current);
    }
    // 시간 업데이트
    time += time_flow;
  }
}

void HRRN(Queue* wait_queue, Queue* ready_queue)
{
  int time=0;
  xcur = start;
  ycur += 7;
  Process*list=NULL;
  Process*temp=NULL;
  setCursorMove(xcur,ycur);
	  
/* HRRN 찍기 */
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
float priorty(Process * p,int time)
{
	return (time-(p->arrival_time)+p->service_time)/p->service_time;	
}
