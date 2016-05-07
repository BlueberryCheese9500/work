
#include"process_queue.h"

// 현재 커서 위치
int xcur, ycur;
// 총 수행시간, 처음 프로세스 수행시작 시간, 퀀텀
int total_service_time, time_axis, quantum;
// 커서이동하여 출력
void setCursorMove(int XPos, int YPos);
void FCFS(Queue* wait_queue, Queue* ready_queue);
void RR(Queue* wait_queue, Queue* ready_queue);
void HRRN(Queue* wait_queue, Queue* ready_queue);
float priorty(Process*p, int time);
void ProcessSetTable(Queue* wait_queue, Queue* ready_queue);
