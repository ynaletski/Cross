
/*
     Main
     ���稭���� ����஫���
*/

#include "ALL.h"

//  ���� ���⥯த�⮢ , 2 ������� � ࠧ�묨 ��室���
//  � �ਢ���� "Commander SK" ,"Delta" ��� � ���஬ � ���⠪�஬.
//  �� �ᯮ�짮����� �ਢ��� - ॣ���� �������� ������� ����� ��饭��
// ���� ��� �����ঠ��� ��������� �������� (MDP==0).
//  �᫨ MDI == 1 , � �㭪樨 ⮪� �����⥫�
// ��������� ���孨� �।�� ����� ��饭�� �����⥫�.

/*
#if defined(PMP_LG)
char sw_ver[20]="N4.10.1 16 Feb 2018";  // COM0 COM1 COM2 COM3 COM4
#else
char sw_ver[20]="N4.10 16 Feb 2018";  // COM0 COM1 COM2 COM3 COM4
#endif
*/

char sw_ver[20]="N1.4 - 02 Jul 2021";
//02.07.2021 YN char sw_ver[20]="N1.3 - 20 May 2021";
//20.05.2021 YN char sw_ver[20]="N1.2 - 05 May 2021";
//char sw_ver[20]="N3.26.08.08 Jun2011";
char sw_ver1[20]="N3.10. 15 Apr 2019";

unsigned long ComBaud[5]={9600,9600,9600,9600,115200};
int Com_lgth[5]={8,8,8,8,8};
int Com_parity[5]={0,0,0,0,0};//0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)

int Com_stop[5]={1,1,1,1,1};

int  ComProt[5]={0   ,0,1,0,0};

long int baudrate_val[]={1200,1200,1200,1200,2400,4800,9600,19200,38400,57600,115200};

/*
int flag_Serv=0; // 0 - ��� � Host PC ��� �⫠���
unsigned long ComBaudPmp1=115200L;
int Com_lgthPmp1  =8;
int Com_parityPmp1=0;// Odd   //0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)
int Com_stopPmp1  =1;
int ComPortPmp1 = 4;
int P_addr=1;
//int flag_spec = 0; // 䫠� ���७���� ����
//long int WD_PMP_Per=20000;
*/

int  MMI_inp_err=0;
int  MMI_out_err=0;

#if defined(MMI_ICP)
int  ZeroPage=9;
int  EmptPage=0 ;
#endif

#if defined(MMI_NEW)
int  ZeroPage=2;
int  EmptPage=2 ;
#endif


//------------------------
int f_get_nb( long int baud)
{
int i;
 for(i=3;i<11;i++)
  if(baudrate_val[i]== baud)
    return i;
 return -1;
}
//------------------------
/*
float var[3000]={
 1.235,
 3.546,
 789000,
 345.678,
 45.678,
 5.678,
 0.678,
 0.0678,

};
*/
//--------------------------
void ShowPort(int port)
{
  Show5DigitLedWithDot(1,port);
}
void ShowChecksum(int checksum)
{
  Show5DigitLedWithDot(2,checksum);
}
void ShowBaudrate(long baud)
{ int data;

  if(baud>100000) data=baud/1000;
  else data=baud/100;

  Show5DigitLed(5,data%10);
  data/=10;
  Show5DigitLed(4,data%10);
  data/=10;
  Show5DigitLed(3,data%10);
}

void ShowCom( int port,int checksum,long int baud)
{
  ShowPort(port);
  ShowChecksum(checksum);
  ShowBaudrate(baud);

}
//-------------------
int i_ish;
void ShowNumber(long Num)
{ // �뢮��� �᫮ � �����筮� �ଥ �� 5DigitLed
int i,i1,dig;
char buf[10];

i_ish=Num;
return;
/*
  sprintf(buf,"%ld",Num);
  i=strlen(buf);
  if(i>0) i--;

  for(i1=0;i1<5;i1++,i--)
  {
    if(i>=0)
    {
     dig=buf[i]-'0';
    }
    else dig=0;
      Show5DigitLed(i1,dig);
  }
  printf("\n\r==%s==\n\r",buf);
*/

}
//-------------------
int getch_host()
{
while(!IsCom(ComPortHost));
 return(ReadCom(ComPortHost));
}
//-------------------
int puts_host(char *str)
{
int i;
 for(i=0;str[i];i++)
 putch(str[i]);
 return i;
}
//-------------------
void f_cycle_cmn()
{
     f_time_dd();

     if(flag_prn_mass)
     {
      MassTT = s_MVD[0].MassT;
      VolTT  = s_MVD[0].VolT;
     }
     else
     {
      MassTT = 0.;
      VolTT  = 0.;
     }

         if(flag_wd_err != 0)
         {
      flag_wd_err=0;
      f_icp_errS(WD_host);
         }


//   f_send_slv();


     if( WDOG[0].status)  f_WDOG(0);

      f_ctrl_v2();

     if(flag_Slv ==0 )
     {
       ServiceCOM(1);
       ServiceCOM(2);
       ServiceCOM(3);
     }
     else
     {
      if(ComPortSlv == 3)
      {
        ServiceCOM(1);
        ServiceCOM(2);
      }
      else if(ComPortSlv == 2)
      {
        ServiceCOM(1);
        ServiceCOM(3);
      }
      else if(ComPortSlv == 1)
      {
        ServiceCOM(2);
        ServiceCOM(3);
      }
      else if(ComPortSlv == 4)
      {
        ServiceCOM(1);
        ServiceCOM(2);
        ServiceCOM(3);
      }
     }

//   f_send_slv();

#if( Test == 0)
        if(MVD[0].status)  f_MVD(0);
        else
        {
         MVD_fl[0]=0;
         f_sim_MVD0();
        }
#else
        f_sim_MVD();
#endif

       f_ctrl_v2();

       f_out();
//   f_send_slv();

       if(I7060[0].status)  f_7060(0);
       else I7060_fl[0]=0;

#if defined(ICP_7041)
       if(I7041[0].status)  f_7041(0);
       else I7041_fl[0]=0;
#endif

       f_inp7188();

#if defined(RTU_ComSK)
        if(ComSK[0].status)  f_ComSK(0);
        else ComSK_fl[0]=0;
#endif

#if ( defined(RTU_Delta) || defined(RTU_Delta_C))
        if(Delta[0].status)  f_Delta(0);
        else Delta_fl[0]=0;
#endif

#if defined(RTU_OFP)
        if(OFP[0].status)  f_OFP(0);
        else
         if (INP_OFP != 0xc0ff)
                 INP_OFP=0xff;
#endif

      f_print_TSD(0);
#if defined(ICP_TSD)
      if(TSD[0].status)  f_TSD(0);
#endif

#if defined(TSD_GLB)
      if(TSD[0].status)  f_TSD_GLB(0);
      else TSD_GLB_fl[0]=0;
#endif
        f_ctrl_v2();
                f_out();

     if(ff_serv_N != NULL) (*ff_serv_N)(); // ����,�����襭�� ���᪠/�ਥ��

     f_sens();
//   f_one_shot();
//   f_send_slv();

     f_var_i();


     f_reg_cmn_clk();


     if(flag_pool)
     {
#if defined(ICP_7017C)
          if(I7017C[0].status)  f_7017C(0);
#endif
       f_one_sec();
       if(ff_serv != NULL) (*ff_serv)(); // ᪠��஢���� ������ࠫ�,
//     f_one_shot();
     }


      f_mirr();
      f_MVD_31();

}
// ==================================================
int f_cycle()
{  // �᭮���� 横�

     f_cycle_cmn();

       if(flag_Slv != 0)
             f_SlaveRTU();

//   if(flag_pool)
     {
       if(f_menu_MMI()) return -1;
       if(MMI.status)
       {
         f_MMI();
       }
/*
       if(Ekd.status)
       {
         if(f_menu_Ekd()) return -1;
         f_Ekd();
       }
       else Ekd_fl=0;
*/

     }

//     if(f_host()) return -1;
     if((flag_Slv !=0 )&&(ComPortSlv == ComPortHost) );
//   if((flag_Slv !=0 )&&(ComPortSlv == 4) );
     else  if(f_host()) return -1;
//   trace();
     return 0;
}
/* ================================================== */
int f_cycle0()
{   // ��� �맮�� f_host()
     f_cycle_cmn();
 //  if(flag_pool)
     {
       if(MMI.status)
       {
         if(f_menu_MMI()) return -1;
         f_MMI();
       }
/*
       if(Ekd.status)
       {
         if(f_menu_Ekd()) return -1;
         f_Ekd();
       }
       else Ekd_fl=0;
*/
     }
//   trace();
     return 0;
}
//-------------------
int f_cycle1()
{   // ��� �맮�� f_MMI()

     f_cycle_cmn();


     if((flag_Slv !=0 )&&(ComPortSlv == 4) );
     else  if(f_host()) return -1;

       if(flag_Slv != 0)
             f_SlaveRTU();

//   trace();
     return 0;
}
/* ================================================== */

/* ---- main ------------------------------------------------------------- */

  //10.10.20 YN -\\//- ��� �६ﭪ� 
  int time_s,time_b,time_3;
  //-------- YN -//\\-

  int ttt1,ttt2,ttt3,ttt4;
  int itt1,itt2,itt3,itt4;
  long int rltt1,rltt2,rltt3,rltt4;
  long int ltt1,ltt2,ltt3,ltt4;
  int  flag_prn=0;

  unsigned long ttt1_l,ttt2_l,ttt3_l;

  //01.10.20 YN -\\//-
  //16.02.2021 YN int intrpt_nb=0; //��।� � ���뢠��� 
  int di_1 = 0;
  int di_2 = 0;
  //-------- YN -//\\-

  int flag_H=0;
void main(void)
{
  double dtmp1,dtmp2,dtmp3,dtmp4;
  float ftmp,ftmp1,ftmp2,ftmp3,ftmp4;
  int iitmp1,iitmp2,iitmp3;
  int i,j;

  char cmd[40];
//  int checksum=1;
  int key;
  int iRet;
  int year,month,day,hour,min,sec;

  int itmp;

/*
  if(!Is7188xa())
  {
    printf("MMICON.EXE must run on I-7188xa");
    exit (0);
  }
  else
    printf("7188xa is found. Flash size %d\n",itmp);
*/

  InitLib();
  tzset();
  f_ns_count();

  daylight=0;
  timezone=0;

  ComPortHost=4;

  *(long int *)&(TimeStamp)=0;
  InstallCom(ComPortHost,115200L,8,0,1);

  f_get_SlvBuf();
  Com_Baud_Slave=ComBaudSlv;

  for(;TimeStamp < 600;)
  {
    if(!IsCom(ComPortHost)) continue;
    key=ReadCom(ComPortHost);
    if(key == '\b')
    {
      flag_H=1;
      printf("\n\r BS pushed.RTU Slave disabled.");
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */

      break;
    }
    if(key == 0x1b )
    {
      flag_H=2;
      printf("\n\r ESC pushed  ");
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */

      break;
    }
  }

  RestoreCom(4);
/*
  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  RestoreCom(4);
*/
//  X607_Init();
  InitEEPROM();

  f_get_flash_p();

  f_wr_evt(evt_t_off);
  f_wr_evt(evt_t_on);


  flag_echo_host=1;

  f_queue_init();
  f_ee_num_init();
  Init5DigitLed();

//   Disable5DigitLed();

// f_init_et();
  if( flag_H == 2)  goto m_n_ee;
  if(f_chk_EEE_CRC()<0)
  {
 m_n_ee:
    InstallCom(ComPortHost,ComBaud[4],8,0,1);
    ShowCom(ComPortHost,8,ComBaud[ComPortHost]);
    printf("CRC Error.Default loaded\n");
    f_icp_errS(EEE_CRC_error);
    sw_mmi=99;
  }
  else
  {
    f_rd_eee();

//  Out_on(OUT8);

    if( flag_H != 0) flag_Slv=0;

    if((flag_Slv==0)||(ComPortHost != ComPortSlv ) )
    {
     if(f_get_nb(ComBaud[ComPortHost]) <0 ) ComBaud[ComPortHost]=115200L;
     InstallCom(ComPortHost,ComBaud[ComPortHost],Com_lgth[ComPortHost],Com_parity[ComPortHost],Com_stop[ComPortHost]);
     ShowCom(ComPortHost,Com_lgth[ComPortHost],ComBaud[ComPortHost]);
    }

    if(flag_Slv==1)
    {
     if(f_get_nb(ComBaudSlv) <0 ) ComBaudSlv=9600L;
     InstallCom(ComPortSlv,ComBaudSlv,Com_lgthSlv,Com_paritySlv,Com_stopSlv);
     ShowCom(ComPortSlv,Com_lgthSlv,ComBaudSlv);
    }

    if(FlagWinSum) init_win_sum(1);
  }

  Com_Baud_Slave=ComBaudSlv;

//  f_init_Fl_m();

  f_rd_cor();
/*
  f_init_COR(0);
  f_init_COR(1);
*/
           if( f_check_id(n_id) == 0)
           {
            id_ok=1;
           }
           else
           {
            id_ok=0;
           }
//  baud=ComBaud[4];
//ShowPort(ComPortHost);
//ShowChecksum(checksum);
//ShowBaudrate(ComBaud[ComPortHost]);
/*=========
    if(EepType==16)
     printf("EEPROM 24LC16 is found (2k bytes)\n");
    else if (EepType==128)
     printf("EEPROM 24WC128 is found (16k bytes)\n");
    else
     printf("Unknown EEPROM.\n");
===========*/
//  TimerOpen();

  f_clr_scr_MMI();
/*
#if defined(EKD_800)
  f_clr_scr_Ekd();
  f_clr_scr_c_Ekd();
  SetEkdPage(ZeroPage);
  f_prn_beginEkd();
#endif
*/

#if defined(ICP_TSD)
  f_clr_TSD(0);
//f_clr_TSD(1);
  f_rev_TSD(0);
//f_rev_TSD(1);
#endif

  if(sw_mmi==0 )
  {

   if((flag_Slv==0)||(ComPortHost != ComPortSlv ) )
   {
#if( Test == 0)

     printf("\nFacom Ver.%s",sw_ver);

#else
     printf("\nFacom.Test version.MVD simulate. Ver. %s",sw_ver);
#endif

      if(id_ok==0)
            printf("\n\r == Not correct ID !");
   }
   f_prn_begin();
  }
  else f_prn_CRC_error();

  SetDisplayPage(ZeroPage);

 /* MMI use I_7188 COM1(RS-232,RS-485),9600,N,8,1 */

  for(i=1;i<4;i++)
  {
   if(i != ComPortSlv)
   {
    if(f_get_nb(ComBaud[i]) <0)  ComBaud[i]=9600L;
    InstallCom(i,ComBaud[i],Com_lgth[i],Com_parity[i],Com_stop[i]);
   }
  }

#if defined(ICP_TSD)
   f_init_TSD();
#endif

#if defined(TSD_GLB)
   f_init_TSD();
#endif

 if((flag_Slv==0)||(ComPortHost != ComPortSlv ) )
 printf("\n\r>");

  one_sec_time=TimeStamp;

  if(I7017C[0].status == 0 )
  {
     s_MVD[0].Press= analog_offset[0];
     s_MVD[0].TempR= analog_offset[1];
  }

  if( fabs(CL_val[1]) > Cor_max) CL_val[1]=0;
  if( fabs(CL_val_L[1]) > Cor_max) CL_val_L[1]=0;

  InstallUserTimerFunction_us(2000,fun_tim_u); //01.10.20 YN was:10000==1ms now:2000==0.2ms

  ///ttt/////////////////////////
  iv_msk[14] = 0xffff;
  iv_msk[15] = 0xffff;
  ///////////////////////////////


  while(1)
  {
     if(f_cycle()<0) break;
  }
printf("\n\rExit\n\r");

  StopUserTimerFun();
  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
  RestoreCom(4);
  f_free_SlvBuf();
}

/* ================================================== */
int last_out[5]={-1,-1,-1,-1,-1};
long int scom_tim[5]={1,1,1,1,1};
unsigned long Tm_snd[5]= {0,0,0,0,0};// long int Tm_snd[5]= {0,0,0,0,0};

void ServiceCOM ( int ii)
/*
  �㭪�� �ਭ����� �⢥� �� SLAVE ����஫���
  �㭪�� �ਭ����� �⢥� �� ������� ��᫠���� �  COM ii.
  ��᫥ �����襭�� �ਥ�� �������, �ਭ��� ������� ��ࠡ��뢠����
  ���ॡ�⥫��, ��᫠�訬 ������� � Slave
*/
{
int i,Addr_rcv,itmp;
struct COM_rqst *request;
struct s_icp_dev *ICPl_DEV;
int  tmp;

 if(scom_tim[ii]!=0)
  if(  f_timer(time_rcv[ii],scom_tim[ii]) == 0)
  {
   if(IsCom(ii)!=0)
   {
     while(IsCom(ii)!=0)
     {
      tmp= ReadCom(ii);

    if(flag_Deb)
      printf("\n%02X",tmp&0xff);
      time_rcv[ii]= TimeStamp;
     }
   }
   return;
  }

  if(COM_que[ii].busy_ptr != COM_que[ii].empt_ptr)
  {
    if(last_out[ii] != COM_que[ii].empt_ptr)
    {
      request=COM_que[ii].request[COM_que[ii].empt_ptr];
      if(request==NULL)
         goto m1;

      last_out[ii]=COM_que[ii].empt_ptr;

      // �����⮢�� � ���㦨����� ����� � �뢮� � ����

      ff_gets_com[ii]=request->gets_com;
      ff_answ_com[ii]=request->answ_com;
      ff_answ_flt[ii]=request->answ_flt;
      ToutAns[ii]=request->timeout;
      time_snd[ii]= TimeStamp;
      Tm_snd[ii]= TimeStamp;

      ICPl_DEV=request->ICP_dd;
      ICPl_DEV->time_stamp_snd=TimeStamp-request->time_stamp;

      // �뢮� � ����
//  ltt1=TimeStamp;
//  tim1();

#if defined(I7188D)
  Set485DirToTransmit(ii); //qqq
#endif

   ToComBufn(ii,request->Cmd,request->cmd_lgth);
/*
   if(ii == 3)
   {  printf("\n\rOUT_C3=");
      for(i=0;i<request->cmd_lgth;i++)
      putch(request->Cmd[i]);
   }
*/
#if defined(I7188D)
  WaitTransmitOver(ii);
  Set485DirToReceive(ii);
#endif

//  tim2();
//  ltt2=TimeStamp;

//   itt1=ttt2-ttt1-10;  // 10 ᫥��� ����� - �� �६� ���������
//   if(itt1 < 0) itt1+=10000;
//   rltt1=ltt2-ltt1;

//   if(flag_prn)
//   {
//     flag_prn=0;
//     printf("\n %d bytes send, time=%ld ms, %.1f mks",request->cmd_lgth,rltt1,(float)(itt1)/10.);
//   }
      request->status=2;
    }
  }

m1:
  if( (*ff_gets_com[ii])(ii) )
 /* ���� �⢥� �� �������. �����⥫� �� �㭪�� �����
    ��⠭�������� �㭪��, ���樨஢���� ��।��� �������
 */
  {
     time_rcv[ii]= TimeStamp;
     request=COM_que[ii].request[COM_que[ii].empt_ptr];
     ICPl_DEV=request->ICP_dd;
     ICPl_DEV->time_stamp_rcv=TimeStamp - request->time_stamp;

   /* � cb_COM[ii][] ��室���� ������� ������  n_bcom[ii]  */

   /* ��ࠡ�⪠ �������. �����⥫� �� �㭪�� ��ࠡ�⪨ ��⠭��������
      �㭪��, ���樨����� ��।���
   */

     ff_gets_com[ii]=f_empty_gets;
     (*ff_answ_com[ii])(ii);

     ff_answ_com[ii]=f_empty;
     n_bcom[ii]=0;
  }
}
/* ================================================== */
int f_timer(unsigned long int time_stamp,unsigned long int delay)
{
// �᫨ �६� � ������ ����� �६������ �⠬�� �ॢ�蠥�
 // delay �� - �����頥� 1, ���� 0.
// if((TimeStamp-time_stamp) > delay) return 1;
// else return 0;
 if((TimeStamp-time_stamp - delay) & 0x80000000 ) return 0;
 else return 1;
}
/* ================================================== */

unsigned long int time_snd[5]={0,0,0,0,0};
unsigned long int time_rcv[5]={0,0,0,0,0};


 char cb_COM[5][n_bufcom];
 int ghj=0;
 int n_bcom[5]={0,0,0,0,0};

void (*ff_serv)() = NULL;

int  (*ff_gets_com[5])(int ii) = {f_empty_gets,f_empty_gets,f_empty_gets,f_empty_gets,f_empty_gets};
void (*ff_answ_com[5])(int ii) = {f_empty,f_empty,f_empty,f_empty,f_empty};
void (*ff_answ_flt[5])(int ii) = {f_empty,f_empty,f_empty,f_empty,f_empty};
int i_empty;
void f_empty(int ii)
{
 i_empty=ii;
}
/* ---------------------------------------- */
/*================================================================*/
float ftmp_naMMI[2];
struct dis_set_MMI ds_list1[]=
{
//----1------
  list1_dsr,
  17,
  &flag_Slv,
  0,
  1,
  T_INT,
//----2------
  list1_dsr,
  15,
  &AddrSlv,
  0,
  255,
  T_INT,
//----3-----------
  /*list1_dsr,
  9,
  &n_ASN,
  0,
  BIG_P,
  T_INT,
//----4-----------
  list1_dsr,
  7,
  &valve_modeL ,     // LOW mode
  0,
  3,
  T_INT,
//----5-----------
  list1_dsr,
  8,
  &valve_mode ,      // HIGH mode
  0,
  3,
  T_INT,
//----6-----------
  list1_dsr,
  2,
  &flag_prok ,
  -1,
  3,
  T_INT,*/
/*----------------*/
//-----------
//----7-----------
  /*list1_dsr,
  158,
  &Flow_nom,
  0,
  BIG_P,
  T_FLOAT,
//----8------
  list1_dsr,
  141,
  &Flow_nomL,
  0,
  BIG_P,
  T_FLOAT,
//----9------
  list1_dsr,
  165,
  &type_liq ,
  1,
  6,
  T_INT,
//---10-----

#if defined(PMP_LG)

  list1_dsr,
  3,
  &T_Pmp_LG ,
  0,
  32000,
  T_INT,
//---11------
  list1_dsr,
  4,
  &OUT_Pmp ,
  0,
  1,
  T_INT,
//-----------

#endif

  list1_dsr,
  1,
  &Flag_mass ,
  -1,
  3,
  T_INT,
//----------------
//-----------
  list1_dsr,
  91,
  &ftmp_naMMI[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  93,
  &ftmp_naMMI[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  92,
  &analog_offset[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,*/
/*----------------*/
 /* list1_dsr,
  94,
  &analog_offset[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,*/
/*----------------*/
  /*list1_dsr,
  157,
  &CL_val[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,*/
/*----------------*/
 /* list1_dsr,
  99,
  &CL_val_L[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,*/
/*----------------*/
  /*list1_dsr,
  156,
  &CL_val[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  list1_dsr,
  98,
  &CL_val_L[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  list1_dsr,
 102,
  &CL_T3,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  list1_dsr,
 103,
  &CL_T4,
  -BIG_P,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  154,
  &Out3_delay_off,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  106,
  &t_mvd_cor,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  104,
  &fct_offs,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  list1_dsr,
  105,
  &fct_offs_L,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  80,               // ������ ��� N ���.
  &num_out1,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  81,               // ������ ��� N ���.
  &num_out2,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  85,               // ��.�.��� N ���.
  &num_out5,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  86,               // ��.�.��� N ���.
  &num_out6,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  142,               // ���.���� N ���.
  &num_out3,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  84,               // �-����.�.�.N ���.
  &num_out4,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  87,               // ��� ���ਨ N ���.
  &num_out8,
  0,
  16,
  T_INT,
//-----------

//----------------
  list1_dsr,
  148,               // �������� N ����.��.
  &analog_num[0],
  0,
  8,
  T_INT,
//----------------
  list1_dsr,
  149,               // �������.N ����.��.
  &analog_num[1],
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  143,               // ��.��.����. N ��.
  &num_in1,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  144,               // ��.��.����. �.���
  &mski_inp1,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  145,               // ������ ���. N ��.
  &num_in2,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  146,               // ������ ���. 䫠� �����ᨨ
  &mski_inp2,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  126,               // ����.��.���.  N ��.
  &num_in3,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  127,               // ����.��.���.�.���
  &mski_inp3,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  128,               // ��.� =Start=  N ��.
  &num_in4,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  129,               // ��.� =Start= �.���
  &mski_inp4,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  130,               // ��.� =Stop=   N ��.
  &num_in5,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  131,               // ��.� =Stop=  �.���
  &mski_inp5,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  115,               // ���.'�������' N ��.
  &num_in6,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  116,               // ���.'�������' �.���
  &mski_inp6,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  132,               // ������ '����' N ��.
  &num_in7,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  133,               // ������'����'�.���.
  &mski_inp7,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  137,               // ��.��.����. N ��.
  &num_in8,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  138,               // ��.��.����.�.���
  &mski_inp8,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  139,               // ����.��� �.N ��.
  &num_in9,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  140,               // ����.��� � �.���.
  &mski_inp9,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  121,               // ���.��.���.N ��.
  &num_in10,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  122,               // ���.��.���.�.���
  &mski_inp10,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  61,               // ��.�.=Stop= N ��.
  &num_in11,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  62,               // ��.�.=Stop=�.���.
  &mski_inp11,
  0,
  8,
  T_INT,
//-----------
  list1_dsr,
  63,               // ��.�.=Start= N ��.
  &num_in12,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  64,               // ��.�.=Start=�.���
  &mski_inp12,
  0,
  8,
  T_INT,*/
//-----------
//----------------
//-----------
  list1_dsr,
  51,
  &MVD[0].status,
  0.,
  1.,
  T_INT,
//-----------
  /*list1_dsr,
  6,
  &I7017C[0].status,
  0.,
  1.,
  T_INT,
//-----------
  list1_dsr,
  18,
  &I7060[0].status,
  0.,
  1.,
  T_INT,
//-----------
#if defined(ICP_7041)
  list1_dsr,
  22,                   // 7041:�����
  &I7041[0].status,
  0.,
  1.,
  T_INT,
//-----------
#endif
  list1_dsr,
  56,
  &TSD[0].status,
  0.,
  1.,
  T_INT,
//-----------
  list1_dsr,
  23,   // OFP:�����
  &OFP[0].status,
  0.,
  1.,
  T_INT,
//-----------
#if ( defined(RTU_Delta) || defined(RTU_Delta_C))
  list1_dsr,
  16,   // Delta :�����
  &Delta[0].status,
  0.,
  1.,
  T_INT,
//-----------
#endif*/
  list1_dsr,
  37,
  &WDOG[0].status,
  0.,
  1.,
  T_INT,
//-----------

//-----------
 /* list1_dsr,
  151,
  &Drive_SV_beg[0],
  0.,
  BIG_P,
  T_INT,
//----------------
  list1_dsr, //
  14,        // Mode P
  &mode_r ,
  0,
  3,
  T_INT,
//----------------
  list1_dsr, //
  10,
  &ftmp_DP,
  0,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr, //
  12,
  &k_p,
  0,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr, //
  13,
  &k_i,
  0,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr, //
  11,
  &k_d,
  0,
  BIG_P,
  T_INT_L,
//-----------
  list1_dsr, //
  19,
  &kf_p,
  0,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr, //
  20,
  &kf_i,
  0,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr, //
  21,
  &kf_d,
  0,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr,
  42,
  &Sl3_addr_e,
  0,
  65535,
  T_INT,
//----------------
  list1_dsr, //
  43,
  &Sl3_lgth_e,
  0.,
//  max_lgth_sl3+1,
  10,
  T_INT,
//----------------
  list1_dsr, //
  44,
  &Sl3_time_e,
  0.,
  32767,
  T_INT,
//----------------
  list1_dsr, //
  45,
  &Sl3_time_mul_e,
  0.,
  32767,
  T_INT,
//----------------
  list1_dsr, //
  46,
  &Sl3_nn_e,
  -1.,
  32767,
  T_INT,
//----------------
  list1_dsr, //
  47,
  &Sl3_fl_jrn_e,
  0.,
  2,
  T_INT,
//----------------
  list1_dsr, //
  32,
  &Cor_max,
  -BIG_P,
  BIG_P,
  T_FLOAT,*/
/*----------------*/

//----------------
  list1_dsr, // ���室 ��⭥� �६�
  89,
  &FlagWinSum,
  0,
  1,
  T_INT,
  //----------------
  //28.10.20 YN -\\//-
  list1_dsr, //�����樥�� ��� �६���
  170,
  &k_t,
  0,      //16.02.2021 YN was: 1
  100,
  T_FLOAT,
  //-------- YN -//\\-
  //29.10.20 YN -\\//-
  list1_dsr, //�����樥�� ��� �६���
  171,
  &k_v,
  0,    //16.02.2021 YN was: 1
  100,
  T_FLOAT,
  //-------- YN -//\\-

  //-----------///uuu/////////////////
  /*list1_dsr,
  166,               // ���.'����.�.' N ��.
  &num_in16,
  0,
  KOL_INP,
  T_INT,
//-----------
  list1_dsr,
  167,               // ���.'����.�.'�.���
  &mski_inp16,
  0,
  8,
  T_INT,      ///ccc/////////////////////
  //-----------
  list1_dsr,
  168,               // ��.�.����. N ���.
  &num_out9,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  169,               // ��.�.����. N ���.
  &num_out10,
  0,
  16,
  T_INT,*/
//-----------
//-----------
  NULL,
  0,
  NULL,
  0,
  1,
  T_INT,
//-----------
//-----------
};
//-----------------------------------------
/*
  list1_dsr, // ��� ��.�롮ન
  88,
  &s_mode,
  1,
  4,
  T_INT,
//--------------------------
  list1_dsr,
  117,
  &TimDensWt1,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  124,
  &TimDensOff,
  0,
  BIG_P,
  T_INT_L,
//----------------------
  list1_dsr,
  125,
  &TimDensOn,
  0,
  BIG_P,
  T_INT_L,
//-----------------------
  list1_dsr,
  109,
  &cutoff_off,
  0,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  110,
  &vol_mom0,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  111,
  &vol_mom,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  112,
  &flow_mom,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  113,
  &offs_cor,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  114,
  &dsc_tmp,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
*/

/*
  list1_dsr,
  107,
  &t_ctrl,
  0,
  2,
  T_INT,
*/
/*
  list1_dsr,
  38,
  &WDOG[0].port,
  1.,
  3.,
  T_INT,
//-----------
  list1_dsr,
  39,
  &WDOG[0].pool_time,
  50,
  10000,
  T_INT_L,
//-----------
  list1_dsr,
  40,
  &WDOG_Rqst[0].timeout,
  1,
  255,
  T_INT_L,
//-----------
  list1_dsr,
  41,
  & WDOG[0].CRC_flag,
  0,
  1,
  T_INT,
//-----------
*/
/*
  list1_dsr,
  19,
  &I7060[0].port,
  1.,
  3.,
  T_INT,
//-----------
  list1_dsr,
  20,
  &I7060[0].addr,
  0,
  255,
  T_INT,
//-----------
  list1_dsr,
  21,
  &I7060[0].pool_time,
  50,
  10000,
  T_INT_L,
//-----------
  list1_dsr,
  22,
  &I7060_Rqst[0].timeout,
  100,
  20000,
  T_INT_L,
//-----------
  list1_dsr,
  23,
  &I7060[0].CRC_flag,
  0,
  1,
  T_INT,
//-----------

//-----------
  list1_dsr,
  47,
  &I7060_wd_E[0],
  0.,
  1,
  T_INT,
//-----------
  list1_dsr,
  48,
  &I7060_wd_VV[0],
  0.,
  255,
  T_INT,
//-----------
*/
/*
  list1_dsr,
  52,
  &MVD[0].port,
  1.,
  3.,
  T_INT,
//-----------
  list1_dsr,
  53,
  &MVD[0].addr,
  0,
  255,
  T_INT,
//-----------
  list1_dsr,
  54,
  &MVD[0].pool_time,
  30,
  10000,
  T_INT_L,
//-----------
  list1_dsr,
  55,
  &MVD_Rqst[0].timeout,
  100,
  20000,
  T_INT_L,
//-----------
  list1_dsr,
  57,
  &TSD[0].port,
  1.,
  3.,
  T_INT,
//-----------
  list1_dsr,
  58,
  &TSD[0].addr,
  0,
  255,
  T_INT,
//-----------
  list1_dsr,
  59,
  &TSD[0].pool_time,
  50,
  10000,
  T_INT_L,
//-----------
  list1_dsr,
  60,
  &TSD_Rqst[0].timeout,
  100,
  20000,
  T_INT_L,
//-----------
*/
//-----------------------------------------
/*=====================================

//---------------
  list1_dsr,
  152,
  &Drive_SA_beg[0],
  0.,
  BIG_P,
  T_INT,
//----------------
  list1_dsr,
  155,
  &Drive_SD_beg[0],
  0.,
  BIG_P,
  T_INT,
//-----------
  list1_dsr,
  118,
  &TimDensWt0,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  123,
  &cl1_delay_off,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
  153,
  &cl2_delay_off,
  0,
  BIG_P,
  T_INT_L,
//---------------
  list1_dsr,
 100,
  &CL_T1,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  list1_dsr,
  101,
  &CL_T2,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  159,
  &Mass_min ,
 -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  160,
  &Flow_min,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  161,
  &Mass_min1 ,
 -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  162,
  &Flow_min1,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  163,
  &Mass_min2 ,
 -BIG_P,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  164,
  &Flow_min2,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  34,
  &ToutLicpScan,
  0.,
  BIG_I,
  T_INT,
//-----------
  list1_dsr,
  35,
  &licp_amax,
  0.,
  255,
  T_INT,
//-----------
  list1_dsr,
  36,
  &LICP_Rqst.CRC_flag,
  0,
  1,
  T_INT,
//-----------
  list1_dsr,
  85,
  &ComProt[1],
  0,
  2,
  T_INT,
//-----------
  list1_dsr,
  86,
  &ComProt[2],
  0,
  2,
  T_INT,
//-----------
  list1_dsr,
  87,
  &ComProt[3],
  0,
  2,
  T_INT,
//-----------
  list1_dsr,
  4,
  &TSD_vn[0][0] ,
  1,
  8,
  T_INT,
//-----------
  list1_dsr,
  95,
  &TSD_vn[0][1] ,
  1,
  8,
  T_INT,
//-----------
  list1_dsr,
  96,
  &TSD_vn[0][2] ,
  1,
  8,
  T_INT,
//-----------
  list1_dsr,
  1,
  &n_dot[0][0],
  1,
  6,
  T_INT,
//-----------
  list1_dsr,
  2,
  &n_dot[0][1],
  1,
  6,
  T_INT,
//-----------
  list1_dsr,
  3,
  &n_dot[0][2],
  1,
  6,
  T_INT,
//-----------
  list1_dsr,
  97,
  &TSD_period,
  1,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr,
  108,
  &tim_MVD_delay,
  -BIG_P,
  BIG_P,
  T_INT_L,
//----------------
  list1_dsr,
  121,
  &k_Den_Off,
  0,
  BIG_P,
  T_FLOAT,
//----------------
  list1_dsr,
  122,
  &k_Den_On,
  0,
  BIG_P,
  T_FLOAT,
//-------------
  list1_dsr,
  137,           // �६� ����.��९,⨪
  &TimeBegFlch,
  0,
  BIG_P,
  T_INT,
//-----------
  list1_dsr,
  138,           // ���� ��砫� ��।.��९
  &val0_flch,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  139,           // ���� ��।.��९ BIG
  &val_flch,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  140,           // ���� ��।.��९ LTL
  &val_flch2,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  141,           // �६� ��९���,⨪
  &time_flch,
  0,
  max_fl_ch_m1,
  T_INT,
//-----------
//-----------
  list1_dsr,
  32,
  &ComBaud[3],
  1200,
  115200,
  T_INT_L,
//-----------
  list1_dsr,
  33,
  &ComBaud[4],
  1200,
  115200,
  T_INT_L,
================================*/


//-----------------------------------------
int max_list1=(sizeof(ds_list1)/sizeof(ds_list1[0])) -1;
/*-----------------------------------------*/
long int time1=0,dd_time,dd_max=-1,dd_min=10000000;
void f_time_dd()
{
long int ltmp;
ltmp=TimeStamp;
dd_time=ltmp-time1;
time1=ltmp;
if(dd_time > dd_max) dd_max=dd_time;
else if(dd_time < dd_min) dd_min=dd_time;
}
//---
void f_print_dd()
{
 printf(" %ld , min= %ld, max=%ld",dd_time,dd_min,dd_max);
 dd_min=10000000;
 dd_max=-1;
}
/*-----------------------------------------*/
unsigned long int one_sec_time=0;

void f_one_sec()
{
union  { float f; char c[4]; } o;
  int win_sum;
  TIME_DATE t;

 if(flag_pool)
 {
  if( f_timer(one_sec_time,1000L) == 0)  return;

  one_sec_time+=1000;

  GetTimeDate(&t);


  if(FlagWinSum)
   {
      if((t.sec <= 2)&& (t.minute==0))
        if((t.day >= 25)&&(t.weekday==0))
        {
          if( (t.month==3)&& (t.hour==2) )
          // � 2 �� ,�� ��, mart,�+=1
          {  /*���室 �� ��⭥� �६� */

           win_sum = ReadNVRAM( nr_win_sum )  ;
           if(win_sum==0)
           { // �� �� ��ॢ�����
            f_wr_evt(evt_none);
            t.hour++;
            win_sum=1;  // 1 - ���
            SetTime((int)t.hour,(int)t.minute,(int)t.sec);

            WriteNVRAM((int)nr_win_sum,(int)win_sum );
            f_wr_evt(evt_ch_sum);
           }
          }
          else if((t.month==10)&& (t.hour==3) )
           // � 3 �� ,�� ��, oct,�-=1
          { //���室 �� ������ �६�

            win_sum  = ReadNVRAM( nr_win_sum )  ;
            if(win_sum)
            { // �� �� ��ॢ�����
              f_wr_evt(evt_none);
              t.hour--;
              win_sum=0; // ������
              SetTime((int)t.hour,(int)t.minute,(int)t.sec);
              WriteNVRAM((int)nr_win_sum,(int)win_sum );
              f_wr_evt(evt_ch_win);
            }
          }
        }
   }
    WriteNVRAM((int)nr_year   ,(int)(t.year-2000));
    WriteNVRAM((int)nr_month  ,(int)t.month  );
    WriteNVRAM((int)nr_day    ,(int)t.day    );
    WriteNVRAM((int)nr_hour   ,(int)t.hour   );
    WriteNVRAM((int)nr_min    ,(int)t.minute );
    WriteNVRAM((int)nr_sec    ,(int)t.sec    );
    o.f=  s_MVD[0].VolI;
    WriteNVRAM((int) nr_v0   ,(int)o.c[0] );
    WriteNVRAM((int) nr_v1   ,(int)o.c[1] );
    WriteNVRAM((int) nr_v2   ,(int)o.c[2] );
    WriteNVRAM((int) nr_v3   ,(int)o.c[3] );
    o.f=  s_MVD[0].MassI;
    WriteNVRAM((int) nr_m0   ,(int)o.c[0] );
    WriteNVRAM((int) nr_m1   ,(int)o.c[1] );
    WriteNVRAM((int) nr_m2   ,(int)o.c[2] );
    WriteNVRAM((int) nr_m3   ,(int)o.c[3] );
 }
}
/*-----------------------------------------*/
float cl_val_c=-100000;
float cl_t_c=-100000;

void f_wr_cor()
{
float ftmp;
union  { float f; char c[4]; } o;

    ftmp=CL_val[1]+CL_val_L[1];

    if( (cl_val_c != CL_val[1]) || (cl_t_c != CL_val_L[1] ) )
    {
       o.f= CL_val[1] ;
       cl_val_c=o.f;
       WriteNVRAM((int) nr_dv0   ,(int)o.c[0] );
       WriteNVRAM((int) nr_dv1   ,(int)o.c[1] );
       WriteNVRAM((int) nr_dv2   ,(int)o.c[2] );
       WriteNVRAM((int) nr_dv3   ,(int)o.c[3] );

       o.f= CL_val_L[1];
       cl_t_c=o.f;
       WriteNVRAM((int) nr_dt0   ,(int)o.c[0] );
       WriteNVRAM((int) nr_dt1   ,(int)o.c[1] );
       WriteNVRAM((int) nr_dt2   ,(int)o.c[2] );
       WriteNVRAM((int) nr_dt3   ,(int)o.c[3] );

       o.f= ftmp;
       WriteNVRAM((int) nr_sm0   ,(int)o.c[0] );
       WriteNVRAM((int) nr_sm1   ,(int)o.c[1] );
       WriteNVRAM((int) nr_sm2   ,(int)o.c[2] );
       WriteNVRAM((int) nr_sm3   ,(int)o.c[3] );
    }
}
/*-----------------------------------------*/
void f_rd_cor()
{
union  { float f; char c[4]; } o;
float ftmp,ftmp1,ftmp2,ftmp3;

 o.c[0]= ReadNVRAM( nr_dv0 );
 o.c[1]= ReadNVRAM( nr_dv1 );
 o.c[2]= ReadNVRAM( nr_dv2 );
 o.c[3]= ReadNVRAM( nr_dv3 );
 ftmp = o.f;
 o.c[0]= ReadNVRAM( nr_dt0 );
 o.c[1]= ReadNVRAM( nr_dt1 );
 o.c[2]= ReadNVRAM( nr_dt2 );
 o.c[3]= ReadNVRAM( nr_dt3 );
 ftmp1 = o.f;
 ftmp3=ftmp+ftmp1;
 o.c[0]= ReadNVRAM( nr_sm0 );
 o.c[1]= ReadNVRAM( nr_sm1 );
 o.c[2]= ReadNVRAM( nr_sm2 );
 o.c[3]= ReadNVRAM( nr_sm3 );
 ftmp2 = o.f;
 if(ftmp2== ftmp3)
 {
   CL_val[1]=ftmp;
   CL_val_L[1]=ftmp1;
 }
}
/*-----------------------------------------*/
/*-----------------------------------------*/
int init_win_sum(int cor)
{
//  �����頥� �ਧ��� ������� ��� ��⭥�� �६���
//  ��� ⥪�饣� ������: 1 - ��⭥� �६� , 0 - ������ �६�
//  �᫨ cor != 0 ���४���� ⥪�饥 �६� �� ���室� ���./���.

  int year,month,day,hour,min,sec;
  int win_sum;
  time_t ltime1,ltime2;
  int prev_ws;

  struct tm *tdat;

 int i,i1;
 TIME_DATE t;
struct arch_str_t tim_0;

 f_prepare_t(&tim_0);
 GetTimeDate(&t);
/*
 tim_0.year  = t.year-2000;
 tim_0.month = t.month;
 tim_0.day   = t.day;
 tim_0.hour  = t.hour;
 tim_0.min   = t.minute;
 tim_0.sec   = t.sec;
*/

// printf("\n\r %02d.%02d.%02d  " ,tim_0.day,tim_0.month,tim_0.year);
// printf("%02d.%02d.%02d -- ",(int)tim_0.hour,(int)tim_0.min,(int)tim_0.sec);

 ltime1=f_get_time_t(&tim_0); // ⥪�饥 �६�

  switch((int)tim_0.month)
  {
   case 11:
   case 12:
   case 1:
   case 2: // ����
         win_sum=0;
         break;
   case 4:
   case 5:
   case 6:
   case 7:
   case 8:
   case 9: // ���
         win_sum=1;
         break;
   case 3:  // ����
        if(t.day>= 10) i=t.day-t.weekday;
        else i=t.day+7-t.weekday;
        for(;i<=31;i+=7)
         {
          i1=i;
         }
//        printf("\n\r==Last Sunday - %d Mart ",i1);
      // i1 - �᫮ ��᫥����� ����ᥭ�� ����
         tim_0.day=i1;
         tim_0.hour=2;
         tim_0.min=0;
         tim_0.sec=0;

    ltime2=f_get_time_t(&tim_0); // �६� �

    if(ltime1<ltime2)
         win_sum=0;
    else
         win_sum=1;
    break;
   case 10:  // ������
        if(t.day>= 10) i=t.day-t.weekday;
        else i=t.day+7-t.weekday;
        for(;i<=31;i+=7)
         {
          i1=i;
         }
      // i1 - �᫮ ��᫥����� ����ᥭ�� ������
         tim_0.day=i1;
         tim_0.hour=3;
         tim_0.min=0;
         tim_0.sec=0;
 //       printf("\n\r==Last Sunday - %d Oct ",i1);

// printf("\n\r %02d.%02d.%02d  " ,tim_0.day,tim_0.month,tim_0.year);
// printf("%02d.%02d.%02d -- ",(int)tim_0.hour,(int)tim_0.min,(int)tim_0.sec);

    ltime2=f_get_time_t(&tim_0); // �६� �
//    printf("\n\rltime1=%ld,ltime2=%ld",ltime1,ltime2);

    if( (ltime2>ltime1)&& ((ltime2 - ltime1)< 3600L))
    {
      win_sum=ReadNVRAM(nr_win_sum);
      break;
    }
    if(ltime1<ltime2)
    {
         win_sum=1;
    }
    else
    {
         win_sum=0;
    }
    break;
  }

  if(cor)
  {
    prev_ws=ReadNVRAM(nr_win_sum);
    if((prev_ws==0)&&(win_sum!=0))
    {// ���室 �� ��⭥� �६�
      ltime1+=3600L;

      tdat = localtime( &ltime1 );
      year   = tdat->tm_year+1900;
      month  = tdat->tm_mon+1;
      day    = tdat->tm_mday ;
      hour   = tdat->tm_hour;
      min    = tdat->tm_min;
      sec    = tdat->tm_sec;

      SetTime(hour, min,sec);
      SetDate(year, month, day);
      f_wr_evt(evt_ch_sum);
    }
    else if((prev_ws!=0)&&(win_sum==0))
    {// ���室 �� ������ �६�
      ltime1-=3600L;

      f_wr_evt(evt_ch_win);

      tdat = localtime( &ltime1 );
      year   = tdat->tm_year+1900;
      month  = tdat->tm_mon+1;
      day    = tdat->tm_mday ;
      hour   = tdat->tm_hour;
      min    = tdat->tm_min;
      sec    = tdat->tm_sec;
      SetTime(hour,min,sec);
      SetDate( year, month, day);
    }
  }
  WriteNVRAM((int)nr_win_sum,(int)win_sum );
  return win_sum;
}
/*-----------------------------------------*/

// �.  device.h

#if defined(MMI_ICP)
#include "MMI.c"
#endif

#if defined(MMI_NEW)
#include "MMI_new.c"
#endif


#if defined(ICP_7017C)
#include "7017c.c"
#endif

#include "i7060.c"

#if defined(ICP_7041)
#include "i7041.c"
#endif

#if defined(RTU_ComSK)
#include "sk.c"
#endif

#if defined(RTU_Delta)
#include "delta.c"
#endif

#if defined(RTU_Delta_C)
#include "deltaC.c"
#endif

#if defined(RTU_MVD)
#include "MVD.c"
#endif

#include "valve.c"

#include "avt_ctrw.c"

// �����⨬� ⮫쪮 ���� �� ���� ��ப
// ����室��� ����� �१ #define �ॡ㥬� 䫠� � device.h

#if defined(ICP_TSD)
// �������� ��ᯫ�� � ��⮪���� ICP
  #include "tsd.c"
#endif

#if defined(TSD_GLB)
// �������� ��ᯫ�� Gilbarco
  #include "tsd_glb.c"
#endif

#include "icp.c"
#include "queue.c"
#include "ref_t.c"

/*-----------------------------------------*/
long int TimeOneShot=0;
long int T_one_Shot=2500;

void f_one_shot()
{
// if( O_SH_IN)
// {
//  TimeOneShot=TimeStamp;
//  OUT_VAR |=  O_One_Shot;
// }

// if(OUT_VAR & O_One_Shot)
//   if( f_timer(TimeOneShot,T_one_Shot ) )
//       OUT_VAR &=  ~O_One_Shot;
}
/*-----------------------------------------*/
void f_out()
{

#if defined(BIO_1)
int OUT1cc=0;

 if(FL_err==0)
 {
   if(OUT_or & CL1_SRC)  OUT1cc |= OUT5;
   if(OUT_or & CL2_SRC)  OUT1cc |= OUT6;
   if(OUT_Pmp & Pump_MDB) OUT1cc |= OUT3;
 }
 i7060_out[0] = (OUT_VAR | OUT1cc) & 0xff;

#else

 #if defined (PMP_LG)


 if(FL_err==0)
 {
   if(OUT_Pmp & Pump_MDB)
   {
     OUT_VAR |= OUT3;
   }
 }
 else
 {
  flag_O3=0;
   OUT_VAR &= ~OUT3;
   if( flag_ext_t == 0)
      f_Drive_Stop();
 }

 i7060_out[0] = OUT_VAR  & 0xff;

 #else
 i7060_out[0] = OUT_VAR & 0xff;
 #endif

#endif

// i7060_out[1] = (OUT_VAR>>4) & 0xf;

}
/*-----------------------------------------*/
