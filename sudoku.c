#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define size 9
#define easy 20
#define normal 30
#define difficult 40
#define outoferror -1
#define alreadyis -2
#define QUIT 2
#define SUBMIT 1
#define ONEMORE 3
int map[size][size]={{0}};
int usersol[size][size] = {{0}};
char display[size][size]={{' '}};
int fixed[size][size]={{0}};
void clear()
{
  while(getchar()!='\n');
}
void printfixed()
{
  int i=0,j=0;
  for(i=0;i<size;i++)
  {  
    for(j=0;j<size;j++)
      printf("%4d",fixed[i][j]);
    printf("\n");
  }
}
void printusersol()
{
  int i=0,j=0;
  for(i=0;i<size;i++)
  {  
    for(j=0;j<size;j++)
      printf("%4d",usersol[i][j]);
    printf("\n");
  }
}
void printmap()
{
  int i=0,j=0,p=0;
  printf("%3c",' ');

  for(p=0;p<(size+2)*3+1;p++)
    printf("ㅁ");
  printf("\n");


  for(i=0;i<size;i++)
  {

    for(p=0;p<(size+2);p+=3)
      printf("%3cㅁ%17c",' ',' ');
    printf("\n");

    for(j=0;j<size;j++)
    {
      if(j%3==0)
        printf("%3cㅁ%3c",' ',display[i][j]);
      else printf("%7c",display[i][j]);
    }
    printf("%3cㅁ\n",' ');

    for(p=0;p<(size+2);p+=3)
      printf("%3cㅁ%17c",' ',' ');
    printf("\n");

    if(i%3==2) 
    {
      printf("%3c",' ');

      for(p=0;p<(size+2)*3+1;p++)
        printf("ㅁ");
      printf("\n");

    }
  }
 }

int cross_check(int x, int y,int turn)
{
  int cnt=0;
  int i=0;
  if(x>=9 || y>=9 || x<0 || y<0)
    return outoferror;

  //vertical
  while(i<size)
  {
    if(usersol[i][y]==turn)
      cnt++;
    i++;
  }
  i=0;
  while(i<size)
  {
    if(usersol[x][i]==turn)
      cnt++;
    i++;
  }
  if(cnt>=1)
    return alreadyis;
  else return 0;
}
int square_check(int x, int y, int turn)
{
  int cnt=0, i=0,j=0;
  int boarderx=(x/3)*3;
  int boardery=(y/3)*3;
  
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(usersol[boarderx][boardery]==turn)
        cnt++;
    }
    boarderx++;
  }
  if(cnt>=1)
    return alreadyis;
  else return 0;
}

int setfirstset(int firstline[])
{
  int temp=0;
  int i=3;
  while(temp<size)
  {  
    map[0][temp]=firstline[temp];
    temp++;
  }
  temp=0;
  while(temp<size)
  {
    if(i>=9)i=0;
     map[1][temp]=firstline[i++];
     temp++;
  }
  i=6;temp=0;
  while(temp<size)
  {
    if(i>=9)i=0;
      map[2][temp]=firstline[i++];
      temp++;
  }
}
int setremainset(int shift)
{
  int temp=0,i=0,start=shift;
  int setnumber=1;
  while(setnumber<=2)
  {
    temp=0;
    while(temp<size)
    { 
      if(start>=9)
        start=0;
      map[setnumber*3][temp]=map[(setnumber-1)*3][start];
      map[setnumber*3+1][temp]=map[(setnumber-1)*3+1][start];
      map[setnumber*3+2][temp]=map[(setnumber-1)*3+2][start];
      temp++;start++;
    }
    setnumber++;
  }
}
int makemap()
{
  int i=0,j=0,turn=0;
  int firstline[9]={0} , full=0,number=1, irand, shift=0;
  char num[3];
  num[2]='\0';
  srand(time(NULL));
  shift=rand()%2+1;
  while(full<9)
  {
     irand=rand()%9;
     if(firstline[irand]==0)
     {
        firstline[irand]=number;
        number++;
        full++;
     }
  }
  setfirstset(firstline);
  setremainset(shift);
  for(i=0;i<size;i++)
    for(j=0;j<size;j++)
    {
      sprintf(num,"%d",map[i][j]);
      display[i][j] = num[0];
      usersol[i][j]=map[i][j];
    }
  return 0;
}
int applylevel(int level)
{
  int i=0,j=0,cnt=0, isinfinite=0;
  srand(time(NULL));
  while(cnt<level)
  {
    isinfinite++;
    i=rand()%9;
    j=rand()%9;
    if(fixed[i][j]!=-1)
    {
      fixed[i][j]=-1;
      display[i][j]=' ';
      usersol[i][j]=0;
      cnt++;
    }
    if(isinfinite>=1000)
      return -1;
  }
  return 0;
}
int input()
{
  int x=0,y=0,number=0,result=0;
  char num[3]=" ";
  char opt[3]=" ";
  char temp=' ';
  opt[2]='\n';
  printf("\n x y number : ");  
  result=scanf("%c",&opt[0]);
  
  if(opt[0]=='s')
     return SUBMIT;
  else if(opt[0]=='q')
     return QUIT;
   
  x=atoi(opt);  
 
  result+=scanf(" %d",&y);
  result+=scanf(" %c",&temp);
  clear();
  opt[0]=temp;
  
  if(result!=3)
  {  
    printf("invalid input\n");
    return -1;
  }
  
  if(opt[0]=='d')
    number=-1;
  else 
    number=atoi(opt);

  if(x>=1 && x<=9 && y>=1 && y<=9)
  {
    if( fixed[x-1][y-1]!=0 && number!=0)
    {
      if(number>=1 && number<=9)
      {
        if(cross_check(x-1,y-1,number)==alreadyis || square_check(x-1,y-1,number)==alreadyis )
        {
          printf("your input was %d, and %d is already exist.\n",number,number);
          return alreadyis;
        }
        usersol[x-1][y-1]=number; 
        sprintf(num,"%d",number);
        display[x-1][y-1]=num[0];
        return 0;
      }
      else if(number==-1)
      {
        usersol[x-1][y-1]=0; 
        display[x-1][y-1]=' ';
        return 0;
      }
    }
    else
    {
      printf("your input was %d, %d, %d . you can't change original setting\n",x,y,number);
      return -1;
    }
  }
  else
  { 
    printf("your input was %c %d %c, please check your input\n",opt[0],y,temp);
    return -1;
  }
}
int check()
{
  int i=0,j=0,correct=0;
  for( i=0;i<size;i++)
    for(j=0;j<size;j++)
      if(map[i][j]!=usersol[i][j])
        correct--;
  return correct;
}
int run()
{
   int prevent =50,result=0; 
   char onemore='n';
   printf("q is exit and s is submit\n");
   while(prevent--)
   {
     printmap();
     result=input();
     switch(result)
     {
       case SUBMIT:
         if(check()==0)
         { 
           printf("well done!~ do you want more? (if yes, input y)\n");
           clear();
           scanf("%c",&onemore);
           if(onemore=='y') return ONEMORE;
           return QUIT;
         }
         else printf("not yet...\n");
         break;
       case QUIT:
         printf("quit.bye~!\n");
         return QUIT;
         break;
       case 0:
         break;
       default:
         printf("input failed.\n");
         break;
     }
   }
}

int main(void)
{
  int opt=0, level=0, keep=ONEMORE, prevent=10;
  while(keep==ONEMORE && (prevent--))
  { 
    printf("welcome to sudoku. there is a {1,2,3} Level. which one? ");
    scanf("%d",&opt);
    clear();
    switch(opt)
    { 
      case 1:
        level=easy;
        break;
      case 2:
        level=normal;
        break;
      case 3:
        level=difficult;
        break;
      default :
        printf("there is no such level.\n");
        return;
        break;
    }
    if(makemap()!=0)
    {
      printf("failed to make map\n");
      return 0;
    }
    else 
    {
      if(applylevel(level)==0)
      {
        keep=run();
      }
      else
      {
        printf("level apply error\n program exit\n");
        return 0;
      }
    }
  }
}
