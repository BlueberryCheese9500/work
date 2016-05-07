
#include"process_queue.h"
int xcur;
int ycur;
int current_time;
int total_service_time;

// 커서이동하여 출력
void setCursorMove(int XPos, int YPos);
void FCFS(Queue* wait_queue, Queue* ready_queue);
void RR(Queue* wait_queue, Queue* ready_queue);
void HRRN(Queue* wait_queue, Queue* ready_queue);
