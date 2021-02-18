/*
  time_tst.c : Demo program for I-7188 to check time of math perform
  must run on I-7188XA
*/

#include"7188xa.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <time.h>
#include <sys\types.h>
#include <sys\timeb.h>

#define getch4 getch
#define kbhit4 kbhit
#define TimeStamp  *TimeTicks

int   quit_mmi=1;

int qwe=0;

/* ---- redefine stdin/out ------------------------------------*/

#define printf  printCom4
#define getch() getch4()
#define kbhit() IsCom(4)
#define putch   ToCom4
int getch4()
{ while(!IsCom(4)); return(ReadCom(4));
}
#define tim1()     asm{mov dx,0ff60H;in ax, dx;mov ttt1,ax}
#define tim2()     asm{mov dx,0ff60H;in ax, dx;mov ttt2,ax}
#define tim4()     asm{mov dx,0ff60H;in ax, dx;mov ttt4,ax}

void prnt(void);
void prnt_nm(void);
void prnt_nm1(void);

void prnt_nm(void)
{
  qwe=0;
  printf("\n\r\n\r prnt_nm \n\r");
  //*(long int *)&(TimeStamp)=0;

}

void prnt_nm1(void)
{
  qwe=1;
  printf("\n\r\n\r %ld \n\r", TimeStamp);
}

/*-------------------------------------------------------------*/

/* ---- main ---- */

  int ttt1,ttt2,ttt3,ttt4,ttt_nm;
  unsigned long ttt1_l,ttt2_l,ttt3_l,ttt4_l,ttt_l_nm;
  unsigned int nm1,nm2;

   float time_nm1;


int flag=0;


void prnt(void)
{
  /*if(qwe==0) prnt_nm1();
  else if(qwe==1) prnt_nm();*/
          nm1 = GetDi1();
          nm2 = GetDi2();

          if(nm1 == 1 && flag == 0){
            ttt1_l=*TimeTicks;
            tim1();
            flag = 1;
          }
          if(nm2 == 0 && flag == 1){
            ttt4_l=TimeStamp;
            tim4();

            ttt_nm = ttt4-ttt1-10;
            ttt_l_nm =ttt4_l - ttt1_l;

            if(ttt_nm<0)
            {
             ttt_nm+=10000; ttt_l_nm-=1;
            }

            time_nm1=ttt_l_nm*1000+ (float)(ttt_nm)/10.;
            printf("\n\rTime!!!!:%f mks",time_nm1);
            time_nm1=0;
            flag=3;
          }
}


void main(void)
{
  double dtmp1,dtmp2,dtmp3,dtmp4;
  float ftmp,ftmp1,ftmp2,ftmp3,ftmp4;
  int iitmp1,iitmp2,iitmp3;

  int key;
  int iRet;
  int year,month,day,hour,min,sec;

  int itmp;

  nm1 = GetDi1();
  nm2 = GetDi2();
/*
  if(!Is7188xa())
  {
    printf("MMICON.EXE must run on I-7188xa");
    exit (0);
  }
  else
    printf("7188xa is found. Flash size %d\n",itmp);
*/

  InstallCom(4,115200L,8,0,1);
  printf("----- Time_tst.exe ----\n\r\n\r");


    printf("\n\r   Q   -  for Quit");
    printf("\n\r   1   -  for int,double,float test & display");
    printf("\n\r>");
    printf("\n\r nm1 = %d nm2 = %d",nm1,nm2);
    printf("\n\r>");

*(long int *)&(TimeStamp)=0;

InstallUserTimerFunction_us(500, prnt);

     while(1)
     {
         /* nm1 = GetDi1();
          nm2 = GetDi2();

          if(nm1 == 1 && flag == 0){
            ttt1_l=*TimeTicks;
            tim1();
            flag = 1;
          }
          if(nm2 == 0 && flag == 1){
            ttt4_l=TimeStamp;
            tim4();

            ttt_nm = ttt4-ttt1-10;
            ttt_l_nm =ttt4_l - ttt1_l;

            if(ttt_nm<0)
            {
             ttt_nm+=10000; ttt_l_nm-=1;
            }

            time_nm1=ttt_l_nm*1000+ (float)(ttt_nm)/10.;
            printf("\n\rTime!!!!:%f mks",time_nm1);
            time_nm1=0;
            flag=3;
          }*/

        if( kbhit() )
         {
          itmp=getch();
          putch(itmp);
          if(( itmp == 'Q') || ( itmp == 'q'))
          {
            printf ("\n\r Quit  \n\r");
            goto m1;
          }
          else if( itmp == '1')
          {
            flag = 0;

        ttt1_l=*TimeTicks;     // ������ ���祭�� ⠩��� �  ����⮩ 1 ��
        tim1();

          //dtmp1=dtmp2*dtmp3;
          /*Delay(61234);
          Delay(61234);*/

          nm1 = GetDi1();
          nm2 = GetDi2();

          if (nm1==1 && nm2==2) 
          {
            ttt4_l=TimeStamp;
            tim4();
            ttt_nm = ttt4-ttt1-10;
            ttt_l_nm =ttt4_l - ttt1_l;

            if(ttt_nm<0)
            {
             ttt_nm+=10000; ttt_l_nm-=1;
            }

            time_nm1=ttt_l_nm*1000+ (float)(ttt_nm)/10.;
          }
          else time_nm1=0;

           printf("\n\rTime!!!!:%f mks",time_nm1);

          }
             printf("\n\r>");
         }
     }
m1:

printf("\n\r*-------- End Time_tst program -------------*");

  while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
  RestoreCom(4);
  StopUserTimerFun();

}
//======================================