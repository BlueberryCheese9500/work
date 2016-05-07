// 프로세스
// 이름, 도착시간, 서비스 시간, 프로세스가 차트에 찍힐 라인, 다음 프로세스
typedef struct Process Process;
struct Process
{
  char name;
  int arrival_time;
  int service_time;
  int order;
  Process* next;
};

