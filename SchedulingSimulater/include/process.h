// 프로세스
typedef struct Process Process;
struct Process
{
  char name;
  int arrival_time;
  int service_time;
  int order;
  Process* next;
};

