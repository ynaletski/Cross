
//---------------------------
// ���� ���⥯த�⮢
//---------------------------
// ��������� �室�:
//     7017C Vin0+ (11) - ���稪 ��������
//     7017C Vin1+ (13) - ���稪 ⥬�������
//
//---------------------------
//                        ����� �室� (������� 'MKS')
//
// INP_VAR D0   7041-DI 0    1   ��. ���� ���孥�� ������
//         D1   7041-DI 1    2   ��. �⮯  ���孥�� ������
//         D2   7041-DI 2    3   ��. ���� ������� ������
//         D3   7041-DI 3    4   ��. �⮯  ������� ������
//         D4   7041-DI 4    5   �஢��� ������� ������
//         D5   7041-DI 5    6
//         D6   7041-DI 6    7
//         D7   7041-DI 7    8
//         D8   7041-DI 8    9
//         D9   7041-DI 9   10
//         D10  7041-DI 10  11   ��� ���孥�� � ������� ������
//         D11  7041-DI 11  12   ���᮫�
//         D12  7041-DI 12  13   �࠯
//         D13  7041-DI 13  14   �஢��� ���孥�� ������
//                          15
//                          16
//
// INP_OFP D0               17       ����ﭨ� ᥪ権 , 1 - 6, 1 - ok
//         D1               18
//         D2               19
//         D3               20
//         D4               21
//         D5               22
//         D6               23       ����ﭨ� ��饥 , 1 - ok
//         D7               24       ����ﭨ� PE    , 1 - ok
//
//---------------------------
//               ����� ��室� (������� 'MKO')
//
// OUT_VAR D0   7044-OUT1  1    ����訩 ������ ���孥�� ������  (p1.MKO)
//         D1   7044-OUT2  2    ����訩 ������ ���孥�� ������  (p2.MKO)
//         D2   7044-OUT3  3    ����訩 ������ �������  ������  (p5.MKO)
//         D3   7044-OUT4  4    ����訩 ������ �������  ������  (p6.MKO)
//         D4   7044-OUT5  5
//         D5   7044-OUT6  6    ������     (�� ��.)  p4.MKO
//         D6   7044-OUT7  7    ���.���� (�� ��.)  p3.MKO
//         D7   7044-OUT8  8    ��� ���ਨ (�� ��.)  p8.MKO
//---------------------------
//       1 2 3 4 5 6 7  8
//  "MKO 2 1 7 6 4 3 0  8"

int result_dlv=0;

int num_out1=1;  //  ����訩 ������ ॣ㫨஢���� ��室�,����� ��ଠ�쭮 ������ , /DN ������� �������� (OUT1=0)
int num_out2=2;  //  ����訩 ������ ॣ㫨஢���� ��室�,����� ��ଠ�쭮 ������� ,  UP ������ �������� (OUT2=1)
int num_out3=7;  //  ����祭�� ����
int num_out4=6;  //  ����祭�� air switch (OUT4)
int num_out5=3;  //  ����訩 ������ �������  ������  // BIO_1 - �ᯮ���⥫�� ��室 ��� CL1_SRC
int num_out6=4;  //  ����訩 ������ �������  ������  // BIO_1 - �ᯮ���⥫�� ��室 ��� CL2_SRC
int num_out7=0;  //  ������祭�� ��ᯫ�� , �� F1
int num_out8=8;  //  ᨣ��� ���ਨ , ������� , 1 - OK.
///ccc/////////////////
int num_out9=3;  // ������ ���孨� �� ����� �ࠢ���饩 �������� �� ���� � ���
int num_out10=4; // ������ ������ �� ����� �ࠢ���饩 �������� �� ���� � ���
///////////////////////
int CLP0=0;

// MKO 0 3 4 0 1 2 0 8 - BIO

//     1  2  3 4 5  6  7  8  9  10  11  12
// MKS 2 11 14 1 0 12 13  4 11   5   0   3

int num_in1  = 2;    //  ES_IN
int num_in2  = 11;   //  UZA_IN
int num_in3  =14;    //  LVL_IN
int num_in4  = 1;    //  STRT_IN
int num_in5  = 0;    //  STOP_IN
int num_in6  = 12;   //  CONS_IN
int num_in7  =13;    //  TRAP_IN
int num_in8  = 4;    //  ES_IN_L
int num_in9  =11;    //  UZA_IN_L
int num_in10 = 5;    //  LVL_IN_L
int num_in11 =0;     //  STOP_IN_L
int num_in12 = 3;    //  STRT_IN_L
int num_in13 =1;     //  O_SH_IN
int num_in14 = 0;    //  ������ ������� ������ ������
int num_in15 = 0;    //  ������ ���孥�� ������ ������

//uuu///////////////////////////////////////
int num_in16  = 5;   //  CONS_IN_L
////////////////////////////////////////////

//---------------------------
  // ������ �室�-��室�
 //  " MKS 8 2 1 3 4 5 6"
  // �����
  // p1...p7.MKS
  // inp1 - ES
  // inp2 - UZA           7060-IN2 (p.6) 2
  // inp3 - ���稪 �஢�� 7060-IN1 (p.3) 1
  // inp4 - ��. "Start"   7060-IN3 (p.4) 3
  // inp5 - ��. "Stop"    7060-IN4 (p.4) 4
  // inp6   �࠯          7188-DI1 (p.7) 5
  // inp7   ���᮫�       7188-DI2 (p.7) 6


//  "MKO 2 1 7 6 4 3 0  8"
  //p1.MKO  OUT1 -      - ����訩 ������ ���孥�� ������
  //p2.MKO  OUT2 -      - ����訩 ������ ���孥�� ������
  //p3.MKO  OUT3 - PUMP - ����祭�� ���� , �� ��.
  //p4.MKO  OUT4 - Air switch

  //p5.MKO  OUT5 - ����訩 ������ ������� ������
  //p6.MKO  OUT6 - ����訩 ������ ������� ������

  //p7.MKO  OUT7 = CLP0 - ᠬ� ����訩 ������ ���孥�� ������
  //p8.MKO  OUT8 -   - ��室 ᨣ���� ���ਨ , ᨣ��������   7060-OUT3  (p.5)


//---------------------------
void f_alarm();
unsigned int OUT_VAR=0;    // ���ﭨ� ������� ��室��
unsigned int OUT_VARi0=0;  // ���ﭨ� ������� ��室�� ��� Slave
unsigned int INP_VAR=0;    // ���ﭨ� ������� �室��
unsigned int INP_inv=0;    // ��᪠ �����ᨨ �室��
unsigned int INP_VAR_c=0;  // ����� ���ﭨ� ������� �室��
unsigned int INP_VARi0=0;  // ���ﭨ� ������� �室��  ��� Slave
unsigned int INP_MSK_OK=INP_MSK_OK_v;        // ���ﭨ� ������� �室�� ��� ���孥�� ������
unsigned int INP_MSK_OK_L=INP_MSK_OK_v_L;    // ���ﭨ� ������� �室�� ��� ������� ������
unsigned int OUT_VAR_c=0;  // ����� ���ﭨ� ������� �室��

//-----------------------------------------------------------------
//---------------------------

int  iv_msk[KOL_D_INP+2]  ;
int  inv_msk[KOL_D_INP+2] ;
int int_fict_11=1;
//---------------------------

void *p_ik[]=
{
&int_fict_11,
&INP_VAR, &INP_VAR, &INP_VAR, &INP_VAR,  //  1  2  3  4
&INP_VAR, &INP_VAR, &INP_VAR, &INP_VAR,  //  5  6  7  8
&INP_VAR, &INP_VAR, &INP_VAR, &INP_VAR,  //  9 10 11 12
&INP_VAR, &INP_VAR, &INP_VAR, &INP_VAR,  // 13 14 15 16
&INP_7188,&INP_7188,                     // 17 18
&INP_7017,&INP_7017,&INP_7017,&INP_7017, // 19 20 21 22
&INP_7017,&INP_7017,&INP_7017,&INP_7017, // 23 24 25 26
&INP_7017,&INP_7017,&INP_7017,&INP_7017, // 27 28 29 30
&i7060_inp[0],&i7060_inp[0],&i7060_inp[0],&i7060_inp[0], // 31 32 33 34
&i7060_inp[0],&i7060_inp[0],&i7060_inp[0],&i7060_inp[0], // 35 36 37 38

};

int msk_ik[]=
{
   1,
   1    ,2    ,4    ,    8,  0x10   ,0x20,  0x40  ,0x80,         //  1  2  3  4  5  6  7  8
 0x100,0x200,0x400  ,0x800,0x1000, 0x2000,0x4000,0x8000,       //  9 10 11 12 13 14 15 16
   1    ,2    ,                                              // 17 18
   1    ,2    ,4    ,    8,  0x10   ,0x20,  0x40  ,0x80,         // 19 20 21 22 23 24 25 26
 0x100  ,0x200,0x400,0x800,                                    // 27 28 29 30
   1    ,2    ,4    ,    8,  0x10   ,0x20,  0x40  ,0x80,       // 31 32 33 34 35 36 37 38

};
//---------------------------
int fict_npn=0;
int *num_pnt[KOL_D_INP+1]={&fict_npn,
&num_in1,&num_in2,&num_in3,&num_in4,&num_in5,&num_in6,&num_in7,&num_in8,
&num_in9,&num_in10,&num_in11,&num_in12,&num_in13,
&num_in14,&num_in15,
///uuu////////////////////////////////
&num_in16,
//////////////////////////////////////
//&num_in16,&num_in17,&num_in18,
};
//---------------------------
int en_bot[KOL_D_INP+2];

int f_ik(int i)
{
int ii;
   if(en_bot[i] == 1) return 1;
   else if(en_bot[i] == -1) return 0;
   ii=*num_pnt[i];
   return( ( ( *(int *)p_ik[ii]) ^ iv_msk[i]  ) & msk_ik[ii] );
}
//---------------------------
// #define    mski_inp1     inv_msk[1]
void f_init_mki()
{
int i;

  for(i=1;i<=KOL_D_INP;i++)
    {
     if(inv_msk[i] != 0.) iv_msk[i] = 0xffff;
     else   iv_msk[i] = 0;
    }
}
//-------------------------------
void f_var_i()
{

int itmp=0;

   if(LVL_IN ) itmp |= 1;      //D0   - ���稪 �஢�� ���孥�� ������,      1 - ok
   if(UZA_IN ) itmp |= 2;      //D1   - ���,                                1 - ok
   if(STRT_IN) itmp |= 4;      //D2   - ������ "Start" ���孥�� ������      1 - ������ �����
   if(ES_IN  ) itmp |= 8;      //D3   - ���਩��� ������ ���孥�� ������    1 - ok,0 - ������ �����

   if(CONS_IN   ) itmp |=0x10; //D4   - ���᮫� ���孥�� ������,            1 - ok
   if(TRAP_IN   ) itmp |=0x20; //D5   - �࠯,                               1 - ok
   ///uuu///////////////////////////////////////////
   if(CONS_IN_L ) itmp |=0x40; //D6   - ���᮫� ������� ������,             1 - ok
   ///////////////////////////////////////////////////
   if(LVL_IN_L  ) itmp |=0x80; //D7 = - ����஫��� ��࠭�祭�� ���������� ������� ������, 1 - ok

   if(STRT_IN_L ) itmp |=0x100;//D8   - ������ "Start" ������� ������       1 - ������ �����
   if(ES_IN_L   ) itmp |=0x200;//D9   - ���਩��� ������ ������� ������     1 - ok,0 - ������ �����
   if(IN_CLS_H  ) itmp |=0x400;//D10  - �������� ���孥�� ������ ������
   if(IN_CLS_L  ) itmp |=0x800;//D11  - �������� ������� ������ ������

INP_VARi0=  itmp;
itmp=0;

   if(OUT_VAR & OUT1  ) itmp |=0x1;  //
   if(OUT_VAR & OUT2  ) itmp |=0x2;  //
   if(OUT_VAR & OUT3  ) itmp |=0x4;  //
   if(OUT_VAR & OUT4  ) itmp |=0x8;  //
   if(OUT_VAR & OUT5  ) itmp |=0x10; //
   if(OUT_VAR & OUT6  ) itmp |=0x20; //
   if(OUT_VAR & OUT7  ) itmp |=0x40; //
   if(OUT_VAR & OUT8  ) itmp |=0x80; //

   ///ccc//////////////////////////////////////
   if(OUT_VAR & OUT9  ) itmp |=0x100; //
   if(OUT_VAR & OUT10  ) itmp |=0x200; //
    ///////////////////////////////////////////

OUT_VARi0=itmp;

}

//-----------------------------------------------------------------
int flag_ext_t=0;
int Drive_SV_beg[2]={5000,5000};  // 50 Hz, ���祭�� ����� ��饭��
int Drive_SA_beg[2]={20,20}; // ⥪�饥 ���ﭨ� �६��� �᪮७�� 2 ᥪ
int Drive_SD_beg[2]={20,20};  // ⥪�饥 ���ﭨ�  ���������� 2 ᥪ �� 100��

int f_St_chk_fict()
{
 return 1;
}
int f_Rn_chk_fict()
{
 return 0;
}
void f_fict()
{
}

void f_fict_stop()
{
 Out_off(OUT3);
}

void f_fict_run()
{
 Out_on(OUT3);
}


int status_fct=0;
int *DriveStatus=&status_fct;

int DriveSV[3]={1000,1000,1000};
int DriveSA[3]={100,100,100};
int DriveSD[3]={100,100,100};
int DriveState[3]={0,0,0};
int DriveCurrent[3]={0,0,0};
int DriveError[3]={0,0,0};

int (*f_Drive_St_chk)()=f_St_chk_fict;
int (*f_Drive_Rn_chk)()=f_Rn_chk_fict;
void (*f_Drive_Stop)()=f_fict_stop;
void (*f_Drive_Run)()=f_fict_run;


//             ⥬������
//          �������� |
//                 | |   0x60
int analog_num[8]={1,2,0,0,0,0,0,0};
float analog_scale[8]={1./NA_scale,250./NA_scale,1./NA_scale,1,1,1,1,1};
float analog_offset[8]= {0,-50,0,0,0,0,0,0};

int fl_GO=0;    // 䫠� ���᪠/�ਥ�� �१ MVD
int fl_EQ=0;    // 䫠� ��ࠢ������� �������� �१ MVD
int flagS_ES=0; // �ਧ��� ��⠭��� �� ������ ES
int flagS_UZA=0; // �ਧ��� ��⠭��� �� ������⢨� UZA
int flagE_UZA=0; // ��� �訡��


int flagS_DLT=0; // �ਧ��� ��⠭��� �� ���ﭨ�� DELTA

int flag_rcv=0;

long int time_com_cl=2000; // ��, �६� ����祭�� �������� ������樨
long int time_com_cl_off=2000; // ��, �६� �몫�祭�� ��������  ������樨
long int time_cnt_cl_off=2000; // ��, ����প� ����� ��⠭���� ��� � �몫�祭��� �������� ������樨
long int time_gas_cl_on =2000; // ��, �६� ����祭�� �������� ���
long int time_gas_cl_off=2000; // ��, �६� �몫�祭�� �������� ���

long int time_EQ_rcv=200; // ᥪ㭤
long int time_EQ_dlv=200; // ᥪ㭤
long int time_LIQ_rcv=600; // ᥪ㭤
long int time_LIQ_dlv=600; // ᥪ㭤

int flag_dlv_fst=0; // 0 - ����� Mass total ��। ��砫�� ���᪠ �ਥ��
int flag_prn_mass=0;

int sw_dlv_liq=0;
int sw_dlv_gas=0;
int sw_rcv_liq=0;
int sw_rcv_gas=0;

int flag_continue=0;

//char *list_avt[]={
char list_avt[][32]={

"����⢨� �⬥����.ESC - ����  ",  // 0
"Sht-ESC ���⪠ �訡��        ",  // 1
"   !����� ���਩��� ������   ", // 2
"   ����⢨� ����������.       ", // 3
"    !��� ᨣ���� ���          ", // 4
"����ன�� ��� ��室����   ", // 5
" !��� �裡 � ��室���஬    ", // 6
"������� �裡 � ��室���஬  ", // 7
"���㫥��� ����� ��室���� ", // 8
" !�஢��� ��� �����⨬���    ", // 9
"����祭�� ��⮪� �������     ", //10
" �࠯ �� � ࠡ�祬 ���������  ",//11
"                              ",//12
" �몫�祭�� ��⮪� �������   ",//13
"���᮫� �� � ࠡ�祬 ���������",//14
"����⢨� ��⠭������.ESC-����",//15
" �������� ������ ��. =���=  ",//16
"����.���-� ����.��஢�� 䠧 ",//17
"",//18
"2-�த������ ���� ����.䠧� ",//19
"ESC - �������� ����        ",//20
" �몫�祭�� ��⮪� ��஢      ",//21
"        �訡�� ��饭�        ",//22
" ESC - �த������             ",//23
"!�ࠩ���� MVD,7060 �� ����祭�",//24
"       !��⠭�� ���᪠       ",//25
"         ���� ���饭�        ",//26
" � ��室���� ��� ������ 䠧�",//27
" ESC - ����                   ",//28
" ���室 ᭨����� �� �।.����.",//29
"      ���� ��⠭�����       ",//30
"     ����� ������ =ESC=      ",//31
" ����� ���� �� �ମ����� ",//32
"     ����� ������ =STOP=     ",//33
"       ID �� ���४⥭        ",//34
"       �� ������� Host        ",//35
///uuu//////////////////////////////////////
"���᮫� ����. �� � ࠡ. �����.",//36
////////////////////////////////////////////
};

char *list_rcv[]={
"�ਥ�.���-� ����.��஢�� 䠧  ",//0 17
"2-�த������ �ਥ� ������ 䠧�",//1 19
"ESC - �������� �ਥ�         ",//2 20
"       !��⠭�� �ਥ��        ",//3 25
"        ���� �ਭ��          ",//4 26
"      �ਥ� ��⠭�����        ",//5 30
};

long int time_t_snd=0;
long int time_t_swtch=0;
int sw_ret=0;

long int Tim_Prep1  =12000;  // ms
long int Tim_Prep_ND=6000; // ms
float    P_beg_valve=0.2;     // MPa
float    F_Dns_off  =20;        // kg/hour

int Flag_dns_flow=0;

//-----------------------------
int key__1=0;
int f_dlv_liq(int key)
{
// �����⮢�� � ����� � ���� ������ 䠧�
//
//  �᫨ key == ESC - ��⠭�� ��⮪� , ��᫥ �����襭�� ��楤���
//  ��⠭��� ��⮪� �����頥� ���祭�� ESC.
//
// return: ESC -  ��⮪ ��⠭����� , ���室 � ���� ���᪠
//          �� ������ ������ 'ESC'
//
    sw_dlv_slv=sw_dlv_liq;
    if((FL_err) && (sw_dlv_liq != -1))
    {
      f_clr_scr_MMI();
      f_disp_error();

//    MmiGotoxy(0,5);   MmiPuts("���� ����������.ESC - ����");
//    MmiGotoxy(0,6);   MmiPuts("Sht-ESC ���⪠ �訡��");
      MmiGotoxy(0,14);   MmiPuts(list_avt[0]);
      MmiGotoxy(0,15);   MmiPuts(list_avt[1]);


    if(sw_dlv_liq==3)
    {
      f_reg_cmn(9);
    }

      result_dlv=0;

      fl_GO=0;
      fl_EQ=0;
      OUT_VAR=0;
      sw_dlv_liq=-1;
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
      f_wr_evt(evt_err_f+flag_rcv);
    }

//10.04.2021 YN
       if(flag_Slv != 0)
             f_SlaveRTU();

  switch(sw_dlv_liq)
  {
   // ��砫쭮� ���ﭨ� - �� ������� �������,
   // ���� ��⠭�����
   // �����⮢�� � ����� ������ 䠧�

   case 1:  // ��砫� ���᪠ � ������ 䠧�
 MVD_t_rslt[0]=0;
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
     if(flag_dlv_fst==0)   sw_dlv_liq=5;
     else
   //01.10.20 YN -\\//-
      //was: sw_dlv_liq=2; now:
      sw_dlv_liq=666;
   //-------- YN -//\\-
     time_t_swtch=TimeStamp;
   break;
//--------------------------
   case  5:
     // ���㫥��� Mass_Total � Volume_Total
 MVD_t_rslt[0]=0;

 time_t_snd=TimeStamp;
  MmiGotoxy(0,4);    MmiPuts(list_avt[8]); //"���㫥��� ����� ��室����");
   // Reset all totalizers
 if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 3,(int)1,(long int) 0,(float)0)== 0)
 { // �訡�� �� ��ࠢ�� ���뫪� MVD
       f_icp_errS(MVD_com);
//  MmiGotoxy(0,1);  MmiPuts("!��� �裡 � ��室���஬    ");
    MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
       goto m_err;
 }
  sw_dlv_liq=6;
  break;
//-----------------------------
   case  6:
    // �������� �����襭�� ������� ���㫥��� totalizers

    if( MVD_t_rslt[0]>0)
    {
     //01.10.20 YN -\\//- was: = 2 noW:
     sw_dlv_liq=666;
     //-------- YN -//\\-
     flag_ZT=0;
     flag_dlv_fst=1; // Mass Total ���㫥��

     VolI_beg=s_MVD[0].VolI;
     s_MVD[0].VolT=0.;
     s_MVD[0].MassT=0.;

     Sim_VolT=0.;
     Sim_MassT=0.;

     f_init_DNSA();

     vol2=0;
     VolT_int=0;
     VolT_id=0;
     break;
    }
//  if(key==ESC)    // ���室 � ����
//       return ESC;
m_wait:
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // �६� ��諮
       MmiGotoxy(0,6);  MmiPuts(list_avt[7]); //"������� �裡 � ��室���஬ "); //01.10.20 YN was:(0,1)
       f_icp_errS(MVD_com);
       goto m_err;
    }
    break;
//-----------------------------

//01.10.20 YN -\\//-

   case 666:

   // ��⠭���� ���祭�� �१� ���ᮢ��� ��室� ��� ࠡ�祣� ०���
   MVD_t_rslt[0]=0;
   time_t_snd=TimeStamp;
   MmiGotoxy(0,4);    MmiPuts("���� �१� ���ᮢ��� ��室�");

   // Cutoff mass
   if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,cutoff_on_M) == 0)
   { // �訡�� �� ��ࠢ�� ���뫪� MVD
      goto m_err_mvd;
   }

   //20.05.2021 YN was: sw_dlv_liq=6661; now:
   sw_dlv_liq=6660;

   break;

//------------

   //20.05.2021 YN 
   case 6660:
    // �������� �����襭�� ������� ��⠭���� cutoff for Mass Flow
    if( MVD_t_rslt[0]>0)
    {
      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;
      // ��⠭���� ���祭�� �१� ��ꥬ���� ��室� ��� ࠡ�祣� ०���
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 197,(int)0,(long int) 0,cutoff_on_V) == 0)
      { // �訡�� �� ��ࠢ�� ���뫪� MVD
         goto m_err_mvd;
      }
      sw_dlv_liq=6661;
      break;
    }
    else goto m_wait;
   //------------ -//\\-

   case 6661:

   if( MVD_t_rslt[0]>0)
   {
      time_t_snd=TimeStamp;
      //13.10.20 YN -\\//-
      if(State_SLV == en_cmpr ) 
      {
         MmiGotoxy(0,4);    MmiPuts("�-� �����⮢��� ���� ࠧ�襭");
         start_time = s_frd.t_old =  TimeStamp;
         s_frd.mass_old = s_MVD[0].MassT;
         s_frd.vol_old = s_MVD[0].VolT;
      }
      //-------- YN -//\\-
      else 
      {
         MmiGotoxy(0,4);    MmiPuts("   ���� ࠧ�襭 => ���।   ");
         start_time = s_frd.t_old =  TimeStamp;
         s_frd.mass_old = s_MVD[0].MassT;
         //02.07.2021 YN
         newMassTotal = 0.0;
         newFlagCount = 0;
         newTimeNew = 0.0;
         newTimeOld = 0.0;
      }

      //���� �⠫�����
      if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float)0)== 0)
      { // �訡�� �� ��ࠢ�� ���뫪� MVD
          goto m_err_mvd;
      }
      if(State_SLV == en_cmpr ) 
      {
         sw_dlv_liq=999;
         State_SLV = en_cmpr_strt; //991 ॣ���� I8 enable ���� ࠧ�襭
      }
      else
      {
         sw_dlv_liq=6662;
         State_SLV = en_start; //662 ॣ���� I8 enable ���� ࠧ�襭 �������� ���।
      }
   }
   else goto m_wait;

   break;

//------------

   case 6662:

   /*08.04.2021 YN 
   if(key==ESC)
   {
      MmiGotoxy(0,4);   MmiPuts(list_avt[31]);  //" ����� ������   ESC          ",//31
      result_dlv=1; //  ����� ������   ESC
      State_SLV=Cmd_brk;
      sw_dlv_liq=-1;
      f_reg_cmn(10);
   }*/
   finish:
   if( MVD_t_rslt[0]>0)
   {
      /*08.04.2021 YN 
      MmiGotoxy(0,2);  MmiPrintf("     Di1 = %d  |  Di2 = %d",di_1,di_2);

      if(State_SLV == en_start) 
      {
         MmiGotoxy(0,4);    MmiPuts("   ���� ࠧ�襭 => ���।   ");
      }
      else if(State_SLV == en_start_back)
      {
         MmiGotoxy(0,4);    MmiPuts("   ���� ࠧ�襭 => �����    ");
      }
      else */
      if(State_SLV == finished)
      {
         MmiGotoxy(0,4);    MmiPuts("    ����७�� => �����祭�    ");
         State_SLV = Cmd_brk;
      }

      /*08.04.2021 YN 
      MmiGotoxy(0,5);  
      MmiPrintf("���� �⠫:  %8f   ",s_MVD[0].MassT);

      MmiGotoxy(0,6);  MmiPuts("     ���।    |    �����     ");
      MmiGotoxy(0,7);  MmiPuts(" ------------- | ------------ ");
      MmiGotoxy(0,8);  
      MmiPrintf("T2: %8ld   | %8ld ",s_frd.t_new,s_back.t_new);

      MmiGotoxy(0,9);  
      MmiPrintf("Tx: %8ld   | %8ld ",s_frd.t_x,s_back.t_x);

      MmiGotoxy(0,10);  
      MmiPrintf("T1: %8ld   | %8ld ",s_frd.t_old,s_back.t_old);

      MmiGotoxy(0,11);  
      MmiPrintf("M2: %8.5f   | %8.5f ",s_frd.mass_new,s_back.mass_new);

      MmiGotoxy(0,12);  
      MmiPrintf("Mx: %8.5f   | %8.5f ",s_frd.mass_x,s_back.mass_x);

      MmiGotoxy(0,13);  
      MmiPrintf("M1: %8.5f   | %8.5f ",s_frd.mass_old,s_back.mass_old);

      MmiGotoxy(0,15); MmiPuts("                 ESC - ��室  ");*/

   }
   else goto m_wait;

   break;

   //------------

   case 6663:

   MVD_t_rslt[0]=0;
   time_t_snd=TimeStamp;
   MmiGotoxy(0,4);    MmiPuts(" ��⠭���� ��� ��室����  ");
   // Stop totalizers
   if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,(float)0)== 0)
   { // �訡�� �� ��ࠢ�� ���뫪� MVD
      goto m_err_mvd;
   }
   sw_dlv_liq = 6664;
   break;

   //------------

   case 6664:
   /*08.04.2021 YN 
   if(key==ESC)
   {
      MmiGotoxy(0,4);   MmiPuts(list_avt[31]);  //" ����� ������   ESC          ",//31
      result_dlv=1; //  ����� ������   ESC
      State_SLV=Cmd_brk;
      sw_dlv_liq=-1;
      f_reg_cmn(10);
   }*/
   if(choice == 2) goto finish;              //ch_weigher
   else if(choice == 3) goto cmpr_finish;    //ch_compare
//-------- YN -//\\-
//-----------------------------

//13.10.20 YN -\\//-
   case 999:

   /* //09.04.2021 YN if(key==ESC)
   {
      MmiGotoxy(0,4);   MmiPuts(list_avt[31]);  //" ����� ������   ESC          ",//31
      result_dlv=1; //  ����� ������   ESC
      State_SLV=Cmd_brk;
      sw_dlv_liq=-1;
      f_reg_cmn(10);
   }*/
   cmpr_finish:
   if( MVD_t_rslt[0]>0)
   {
      /*//09.04.2021 YN
      MmiGotoxy(0,2);  MmiPrintf("            Di2 = %d          ",di_2);

      if(State_SLV == en_cmpr_strt) 
      {
         MmiGotoxy(0,4);    MmiPuts("�-� �����⮢��� ���� ࠧ�襭");
      }
      else if(State_SLV == en_cmpr_cnt)
      {
         MmiGotoxy(0,4);    MmiPuts("        ����� ����          ");
      }
      else */
      if (State_SLV == cmpr_end)
      {
         MmiGotoxy(0,4);    MmiPuts("      ����७�� �����祭�     ");
         State_SLV = Cmd_brk;
      }

/* //09.04.2021 YN
      MmiGotoxy(0,5);  
      MmiPrintf("���� �⠫:  %8f      ",s_MVD[0].MassT);

      MmiGotoxy(0,6);  
      MmiPrintf("��ꥬ �⠫:  %8f     ",s_MVD[0].VolT);

      MmiGotoxy(0,7);
      MmiPrintf("T2: %8ld   | %8ld ",s_frd.t_new,s_back.t_new);

      MmiGotoxy(0,8);  
      MmiPrintf("Tx: %8ld   | %8ld ",s_frd.t_x,s_back.t_x);

      MmiGotoxy(0,9);  
      MmiPrintf("T1: %8ld   | %8ld ",s_frd.t_old,s_back.t_old);

      MmiGotoxy(0,10);  
      MmiPrintf("M2: %8.5f   | %8.5f ",s_frd.mass_new,s_back.mass_new);

      MmiGotoxy(0,11);  
      MmiPrintf("Mx: %8.5f   | %8.5f ",s_frd.mass_x,s_back.mass_x);

      MmiGotoxy(0,12);  
      MmiPrintf("M1: %8.5f   | %8.5f ",s_frd.mass_old,s_back.mass_old);

      MmiGotoxy(0,13);  
      MmiPrintf("V2: %8.5f   | %8.5f ",s_frd.vol_new,s_back.vol_new);

      MmiGotoxy(0,14);  
      MmiPrintf("Vx: %8.5f   | %8.5f ",s_frd.vol_x,s_back.vol_x);

      MmiGotoxy(0,15);  
      MmiPrintf("V1: %8.5f   | %8.5f    ",s_frd.vol_old,s_back.vol_old);*/
   }
   else goto m_wait;

   break;
//-------- YN -//\\-

//-----------------------------

   case 2:  // ��砫� ���᪠ � ������ 䠧�
m1:

f_tst(1);
f_tst1(1);
f_tst2(1);

#if (AIR_SW != 0)
   Out_off(OUT4);  // Air switch off
#endif

#if (CUT_SW != 0)
   Out_on(OUT4);  // CUT off switch on
#endif


 if( Flag_Low == 0)
 {

#if defined(BIO_1)
    if(OUT_or == 0)
    {

       f_icp_errS(No_Src);
       MmiGotoxy(0,1);    MmiPuts(" !�� ����� ���筨� �த�� ");
       goto m_err;
    }
#endif

   if( ( ES_IN)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !����� ���਩��� ������   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);
m_err:
//     MmiGotoxy(0,0);    MmiPuts("  ���� ����������.         ");
       MmiGotoxy(0,0);    MmiPuts(list_avt[3]);
       State_SLV=Cmd_brk;

    if(sw_dlv_liq==3)
      f_reg_cmn(9);
    else if(sw_dlv_liq==1)
       f_reg_cmn(7);
    else
       f_reg_cmn(7);

       sw_dlv_liq=-1;
       return 0;
    }
   if( ( ES_IN_L)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !����� ���਩��� ������   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);
       goto m_err;
    }
   if( ( UZA_IN)==0  )
    {
       flagE_UZA=UZA_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("  !��� ᨣ���� ���           ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[4]);
       goto m_err;
    }
    if( id_ok==0)
    {
       flagE_UZA=ID_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("     �� ���४�� ID         ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[34]);
       goto m_err;
    }
   if( (LVL_IN)==0 )
    {
       flagE_UZA=LVL_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts(" !�஢��� ��� �����⨬���");
       MmiGotoxy(0,1);    MmiPuts(list_avt[9]);
       goto m_err;
    }
   if( ( TRAP_IN)==0 )
    {
       flagE_UZA=TRAP_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts(" �࠯ �� � ࠡ�祬 ��������� ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[11]);
       goto m_err;
    }
   if( ( CONS_IN)==0 )
    {
       flagE_UZA=CONS_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("���᮫� �� � ࠡ�祬 ���������");
       MmiGotoxy(0,1);    MmiPuts(list_avt[14]);
       goto m_err;
    }
  }
 else
 {  // ������ �����

   if( ( ES_IN)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !����� ���਩��� ������   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);
       goto m_err;
    }
   if( ( ES_IN_L)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !����� ���਩��� ������   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);
       goto m_err;
    }

   if( ( UZA_IN_L)==0  )
    {
       flagE_UZA=UZA_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("  !��� ᨣ���� ���           ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[4]);
       goto m_err;
    }
    if( id_ok==0)
    {
       flagE_UZA=ID_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("     �� ���४�� ID         ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[34]);
       goto m_err;
    }
   if( (LVL_IN_L)==0 )
    {
       flagE_UZA=LVL_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts(" !�஢��� ��� �����⨬���");
       MmiGotoxy(0,1);    MmiPuts(list_avt[9]);
       goto m_err;
    }
///uuu///////////////////////////////////////////////////////////////
   if( (CONS_IN_L)==0 )
    {
       flagE_UZA=CONS_L_E;
       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("���᮫� ����. �� � ࠡ. �����.");
       MmiGotoxy(0,1);    MmiPuts(list_avt[36]);
       goto m_err;
    }
/////////////////////////////////////////////////////////////////////
 }

    sw_dlv_liq=3;
    time_t_swtch=TimeStamp;
    flag_continue=0;

    MmiGotoxy(0,1);    MmiPuts(list_avt[16]);
    break;
//-----------------------------
   case  3:
   // �������� ������ ������ "Start"


   f_reg_cmn(8);


   if((STRT_IN && ( Flag_Low == 0) ) || (STRT_IN_L && ( Flag_Low != 0) ) ||(key==Sht_F1) )
   {

     flag_prn_mass=1;
     MVD_t_rslt[0]=0;
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
  // if(flag_dlv_fst==0)
  //   sw_dlv_liq=5;
  // else
       sw_dlv_liq=7;
     time_t_swtch=TimeStamp;

//     f_reg_cmn(12);
//   if((Flag_Low != 0) && ( Flag_mass==0 )) f_reg_cmn( 12 );
     if((Flag_Low != 0) && ( Flag_mass!=0 )) f_reg_cmn( 22 );
else if((Flag_Low == 0) && ( Flag_mass==0 )) f_reg_cmn( 23 );
else if((Flag_Low == 0) && ( Flag_mass!=0 )) f_reg_cmn( 24 );
else
     f_reg_cmn( 12 );
   }
   else if( ( STOP_IN)==0)
   {
       MmiGotoxy(0,1);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
       MmiGotoxy(0,2);   MmiPuts(list_avt[33]);  //"     ����� ������ =STOP=     ",//31
       State_SLV=Cmd_brk;
       result_dlv=1; //  ����� ������   ESC
       sw_dlv_liq=-1;
     f_reg_cmn(10);
   }
   else if(key==ESC)
   {
       MmiGotoxy(0,1);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
       MmiGotoxy(0,2);   MmiPuts(list_avt[31]);  //" ����� ������   ESC          ",//31
       result_dlv=1; //  ����� ������   ESC
       State_SLV=Cmd_brk;
       sw_dlv_liq=-1;
     f_reg_cmn(10);
   }
   else goto m1;
   break;
//-----------------------------

   case  7:
  // ࠧ�襭�� ��室� ��室���� ��� ���


 MVD_t_rslt[0]=0;
 time_t_snd=TimeStamp;
  MmiGotoxy(0,1);    MmiPuts("����襭�� ��� ��室����");

       // Stop totalizers
 if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,(float)0)== 0)
 { // �訡�� �� ��ࠢ�� ���뫪� MVD

m_err_mvd:
            f_icp_errS(MVD_com);
      //  "!��� �裡 � ��室���஬    "
         MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
            goto m_err;
 }
    sw_dlv_liq=71;
  break;

//-----------------------------
   case  71:


    if( MVD_t_rslt[0]>0)
    {
      MVD_t_rslt[0]=0;
      //
      time_t_snd=TimeStamp;

    // ��⠭���� ���祭�� �१� ���ᮢ��� ��室� ��� ࠡ�祣� ०���
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,cutoff_on_M) == 0)
      { // �訡�� �� ��ࠢ�� ���뫪� MVD
          goto m_err_mvd;
      }


      sw_dlv_liq=8;
    }
    else goto m_wait;
  break;

//-----------------------------
   case 8:

    // �������� �����襭�� ������� ��⠭���� cutoff for Mass Flow
    if( MVD_t_rslt[0]>0)
    {

      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;


   // ��⠭���� ���祭�� �१� ��ꥬ���� ��室� ��� ࠡ�祣� ०���
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 197,(int)0,(long int) 0,cutoff_on_V) == 0)
      { // �訡�� �� ��ࠢ�� ���뫪� MVD
       goto m_err_mvd;
      }

    sw_dlv_liq=9;

      break;
    }
    else goto m_wait;
//-----------------------------
   case  9:
    // �������� �����襭�� ������� ��⠭���� cutoff for Vol Flow

    if( MVD_t_rslt[0]>0)
    {
       sw_dlv_liq=11;
//     MmiGotoxy(0,1);  MmiPuts("����祭�� ��⮪� �������    ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[10]);
       break;
    }
    else goto m_wait;
//-----------------------------
   case  11:

       //  ����祭�� ��⮪� �������
      volume_f=dose_dlvr;
      vol_f=dose_dlvr;
      Dens0=s_MVD[0].Dens;

      f_enable_cnt();
    // ������� ���뢠��� ��������
      Out_en =  ~(OUT1 | OUT2);
//  time_beg_fill=TimeStamp;
//  beg_flch=0;
//  flag_flch=0;
      time_t_swtch=TimeStamp;
      MmiGotoxy(0,0);
       if(dose_dlvr != vBIG_P)
        {
         if ( Flag_mass != 0 )
           MmiPrintf("���%d.��.���� %g ��         ",n_ASN,dose_dlvr);
         else
           MmiPrintf("���%d.��.���� %g �          ",n_ASN,dose_dlvr);

        }
       else
         MmiPrintf("���%d.���� ��� ����஢��      ",n_ASN);

       f_prn_mode();

//    MmiGotoxy(0,1);      MmiPuts("                              ");
      MmiGotoxy(0,1);      MmiPuts(list_avt[12]);
//    MmiGotoxy(0,2);      MmiPuts("                              ");
      MmiGotoxy(0,2);      MmiPuts(list_avt[12]);

        sw_dlv_liq=110;
        t_prep_MVD=TimeStamp;
        t_prep_MVD1=TimeStamp;

        Flag_dns_flow=0;
   break;
//-----------------------------

   case 110:
      // ���� ࠡ�⠥�,�� ������� �������
      // �஢�ઠ ���ﭨ�
  time_beg_fill=TimeStamp;
  beg_flch=0;
  flag_flch=0;
      if(key==ESC)
      {
          key__1=key;
          sw_dlv_liq=30;
          f_reg_cmn(14);
      }
      if( ( ( STOP_IN==0) && ( Flag_Low == 0) ) || ( ( STOP_IN_L==0) && ( Flag_Low != 0) )  ) // ���室 � ��楤�� �⪫�祭��
      {
      // ����� ������ "STOP"
          key__1=STOP_E;
          sw_dlv_liq=30;
          f_reg_cmn(14);
      }

      if( f_timer(t_prep_MVD, Tim_Prep1 ) == 0 )
       {

         if(( s_MVD[0].Press > P_beg_valve) || (flag_prok != 0)  );
         else
         {
          Flag_dns_flow=0;
          t_prep_MVD1=TimeStamp;
         }

         if(( fabs(s_MVD[0].FlowM) < F_Dns_off) || (flag_prok != 0)  ) ;
         else
         {
             Flag_dns_flow=1;
             t_prep_MVD1=TimeStamp;
         }

         if( f_timer(t_prep_MVD1, Tim_Prep_ND ) != 0 )
         { // ��⨤ॡ��� ��襫

           t_prep_MVD=TimeStamp;
           sw_dlv_liq=111;

             // Start totalizers


          if(flag_prok == 0)
           {
             MVD_t_rslt[0]=0;
             time_t_snd=TimeStamp;
             if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float)0)== 0) //���� �⠫�����
             { // �訡�� �� ��ࠢ�� ���뫪� MVD
                   goto m_err_mvd;
             }
           }
          else
             MVD_t_rslt[0]=1;
         }


       }
      else
       {  // �६� ��砫쭮� �஢�ન ��諮, ���� ��窠 ��� ��� ��������

         if(Flag_dns_flow != 0)
           f_icp_errS(DNS_not_off);
         else
           f_icp_errS(No_Press);

         break;
       }


       break;

//-----------------------------
  case 111:
    // �������� �����襭�� �������  Start totalizers

  time_beg_fill=TimeStamp;
  beg_flch=0;
  flag_flch=0;
    if( MVD_t_rslt[0]>0)
    {
      Out_en =  0xffff;
      sw_dlv_liq=12;

///ccc/////////////////////////////////////////////////
  #if (CLP_SW != 0)
  if( Flag_Low == 0) 
  {
      Out_on(OUT9);  // ���筮� ������ ���孨�
  }
  else 
      Out_on(OUT10);  // ���筮� ������ ������
#endif
////////////////////////////////////////////////////////

      result_dlv=0;
      break;
    }
    else goto m_wait;
//-----------------------------
   case  12:

       //  ����
    if(FL_err)    // ���室 � ��楤�� �⪫�祭��
    {
        key__1=ESC;
        result_dlv=0; //  �訡��
        sw_dlv_liq=30;
        f_reg_cmn(13);

    }
    else if(key==ESC)       // ���室 � ��楤�� �⪫�祭��
    {
        key__1=key;
       result_dlv=1; //  ����� ������   ESC
        sw_dlv_liq=30;
        f_reg_cmn(14);
    }
    if( ( ( STOP_IN==0) && ( Flag_Low == 0) ) || ( ( STOP_IN_L==0) && ( Flag_Low != 0) )  ) // ���室 � ��楤�� �⪫�祭��
    {
    // ����� ������ "STOP"
        result_dlv=1; //  ����� ������   STOP
        key__1=STOP_E;
        sw_dlv_liq=30;
        f_reg_cmn(14);
    }
    else if(fl_GO==0 ) // ���室 � �����襭�� �� �४�饭�� ���᪠
    {
      key__1=-1;
      MmiGotoxy(0,1);   MmiPuts(list_avt[25]);
//    MmiGotoxy(0,1);   MmiPuts(list_avt[25]);
      sw_dlv_liq=30;
      f_reg_cmn(13);
    }
    break;
//-----------------------------
   case  30:

      // �몫�祭�� �������� ॣ㫨����� ��室
      // ����।�� � ����প�� TimDensWt0
/*
      Out_en=~CLP0;
      time_t_snd=TimeStamp;
      sw_dlv_liq=31;
      break;
//-----------------------------
   case  31:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // �६� ��諮
*/

if( Flag_Low == 0)
{
  if(valve_mode==1)
  {
      Out_en=~CLP0;
      Out_en &= ~(OUT1);
  }
  else if(valve_mode==2)
  {
      Out_en =  ~(OUT1 );
      Out_en &= ~(OUT2 );
  }
  else if(valve_mode==3)
  {
      Out_en =  ~(OUT1 );
  }

}
else
{
  if(valve_modeL==1)
  {
      Out_en = ~(OUT5);
  }
  else if(valve_modeL==2)
  {
      Out_en =  ~( OUT5);
      Out_en &= ~( OUT6);
  }
  else if(valve_modeL==3)
  {
      Out_en =  ~(OUT5);
  }
}

      time_t_snd=TimeStamp;
      sw_dlv_liq=32;

//    }
      break;
//-----------------------------
   case  32:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // �६� ��諮
      if(valve_mode==1)
      {
        Out_en &= ~(OUT2 | OUT6);
      }
/*
      else if(valve_mode==2)
      {
      }
      else if(valve_mode==3)
      {
      }
 */
      time_t_snd=TimeStamp;
      sw_dlv_liq=33;
    }
      break;
//-----------------------------
   case  33:

    if( f_timer(time_t_snd,TimDensWt0 ) )
    {  // �६� ��諮
      sw_dlv_liq=40;
    }
      break;
//-----------------------------
//-----------------------------
   case  40:
      // ��⠭�� ��⮪�

       time_t_swtch=TimeStamp;
       Temperature=s_MVD[0].Temp;
       Density=s_MVD[0].Dens;
       f_stop_cnt();
       sw_dlv_liq=41;
//     MmiGotoxy(0,1);  MmiPuts(" �몫�祭�� ��⮪� �������   ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[13]);
       time_t_snd=TimeStamp;

    break;
//-----------------------------
   case  41:
      // �������� ��⠭��� �����⥫� ����

     if( f_timer(time_t_snd,T_Mot_Stop ) )
     {  // �६� ��諮
m_mot_not:
       f_icp_errS(MotNotStop);
       Temperature=s_MVD[0].Temp;
       Density=s_MVD[0].Dens;
       key__1=0;
       f_alarm();
           f_reg_cmn(13);
//     f_wr_evt(evt_est_f+flag_rcv);
//    "      ���� ��⠭�����       ", //30
       MmiGotoxy(0,1);  MmiPuts(list_avt[30]);
   // " ����� ���� �� �ମ����� ",//32
       MmiGotoxy(0,2);  MmiPuts(list_avt[32]);
   // " ESC - ����                   ",//28
       MmiGotoxy(0,15);  MmiPuts(list_avt[28]);
       sw_dlv_liq=-1;
     }
     else
     {
//     if(Delta[0].status==0)
       if( *DriveStatus ==0)
       {
         sw_dlv_liq=42;
         time_t_snd=TimeStamp;
         break ;
       }
//     if((Delta_State[0] & MSK_RUN_DELTA ) == STP_DELTA )
       if(f_Drive_St_chk() == 1)
       {
         sw_dlv_liq=42;
         time_t_snd=TimeStamp;
       }
     }
      break;
//-----------------------------
//-----------------------------
   case  42:
    // ����প� �� �६� ����� ��⠭���� ��� � �몫�祭��� �������� ������樨
    // time_cnt_cl_off
//  if(OUT_VAR & OUT1) time_t_snd=TimeStamp;
//  if(OUT_VAR & OUT2) time_t_snd=TimeStamp;
//  if(OUT_VAR & OUT3) time_t_snd=TimeStamp;
    if( f_timer(time_t_snd,time_cnt_cl_off ) )
    {  // �६� ��諮
//     MmiGotoxy(0,1);    MmiPuts("�몫�祭�� ����-� ������樨 ");
//    MmiGotoxy(0,1);    MmiPuts(list_avt[14]);
//    Out_off(GAS1);
//    Out_off(GAS2);
//    Out_off(LIQ2);
      time_t_snd=TimeStamp;
      sw_dlv_liq=44;
    }
    break;
//-----------------------------
   case  44:

    if(ff_serv_N== NULL)
    {
       result_dlv=0;

       f_reg_cmn(17);
       sw_dlv_liq=-1;

       if (FL_err)
       {

         f_reg_cmn(17);
         f_clr_scr_MMI();
         f_disp_error();
//       MmiGotoxy(0,6);       MmiPuts("���� ��ࢠ�.ESC - ����    ");
         MmiGotoxy(0,15);       MmiPuts(list_avt[15]);
         break;
       }
       else if(key__1== ESC)
       {
m_esc:

       f_reg_cmn(18);

       result_dlv=1; //  ����� ������   ESC

        MmiGotoxy(0,1);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
        MmiGotoxy(0,2);   MmiPuts(list_avt[31]);  //" ����� ������   ESC          ",//31
        MmiGotoxy(0,15);   MmiPuts(list_avt[28]);  //" ESC - ����                   ",//28
        break;
       }
       else if(key__1== STOP_E)
       {
       f_reg_cmn(18);
       result_dlv=1; //  ����� ������   STOP
        MmiGotoxy(0,1);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
        MmiGotoxy(0,2);   MmiPuts(list_avt[33]);  //"     ����� ������ =STOP=     ",//31
        MmiGotoxy(0,15);   MmiPuts(list_avt[28]);  //" ESC - ����                   ",//28
        break;
       }
       else if(key__1== STOP_H)
       {
       result_dlv=2; //  ������� Host
       f_reg_cmn(19);
        MmiGotoxy(0,1);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
        MmiGotoxy(0,2);   MmiPuts(list_avt[35]);  //" �� ������� Host        ",//31
        MmiGotoxy(0,15);   MmiPuts(list_avt[28]);  //" ESC - ����                   ",//28
        break;
       }

//          MmiGotoxy(0,0);   MmiPuts(" ���� ��⠭�����            "  );
            MmiGotoxy(0,1);   MmiPuts(list_avt[30]);
//          MmiGotoxy(0,6);       MmiPuts(" ESC - ����    ");
            MmiGotoxy(0,15);       MmiPuts(list_avt[28]);
       if((flag_fill_ok!=0)&&(flag_gas ==0) )
          {
//          MmiGotoxy(0,1);       MmiPuts(" ���� ���饭�     ");
            MmiGotoxy(6,2);

         if ( Flag_mass != 0 )
              MmiPrintf("���� %g �� ���饭�            ",dose_dlvr);
         else
              MmiPrintf("���� %g � ���饭�             ",dose_dlvr);


        //    dose_dlvr=vBIG_P;
                           dose_dlvr=-1;
                //         flag_prn_mass=0;


            result_dlv=3; //  ���� ���饭�

       f_reg_cmn(16);
            break;
          }
          else if(flag_gas !=0)
          {
//          MmiGotoxy(0,1);       MmiPuts(" � ��室���� ��� ������ 䠧�");
            MmiGotoxy(0,2);       MmiPuts(list_avt[27]);
            break;
          }
          else if(flag_flch !=0)
          {


       f_reg_cmn(20);
       result_dlv=4; //   ���室 ᭨����� �� �।.����.
//          MmiGotoxy(0,1);       MmiPuts(" ���室 ᭨����� �� �।.����.");
            MmiGotoxy(0,2);       MmiPuts(list_avt[29]);
            break;
          }
          else break;
    }
    else
     if( f_timer(time_t_snd,(t_mvd_cor*3) ) )
     {  // �६� ��諮
       ff_serv_N = NULL;
       f_icp_errS(MVD_com);
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
       f_wr_evt(evt_est_f+flag_rcv);
//     MmiGotoxy(0,1);  MmiPuts("!��� �裡 � ��室���஬    ");
       MmiGotoxy(0,2);  MmiPuts(list_avt[6]);
//     MmiGotoxy(0,0);    MmiPuts("  ���� ����������.         ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[3]);
       State_SLV=Cmd_brk;

       f_reg_cmn(21);

       sw_dlv_liq=-1;
       return 0;
     }
    break;
//-----------------------------
//-----------------------------
    case -1:
       if((key==ESC)||(key==ENTER)  )    // ���室 � ����
       {
#if defined(BIO_1)
      flag_O3=0;
#endif
        return ESC;
       }
       else if ((key==Sht_ESC) && (mode_hst == 0 ))
        {  // ���⪠ �訡��
          f_clr_scr_MMI();

#if defined(MMI_ICP)
          SetDisplayPage(23);
#endif

#if defined(MMI_NEW)
          SetDisplayPage(2);
#endif


                  f_cl_error();
//        MmiGotoxy(0,2);    MmiPuts("        �訡�� ��饭�       ");
//        MmiGotoxy(0,4);    MmiPuts(" ESC - �த������            ");
          MmiGotoxy(0,14);    MmiPuts(list_avt[22]);
          MmiGotoxy(0,15);    MmiPuts(list_avt[23]);
          return ESC;
        }
       else
         return 0;
//-----------------------------
  }
  return 0;
}
//-----------------------------
//-----------------------------
/*
void Out_on(int msk)
{
 OUT_VAR |= msk;
}
//-----------------------------
void Out_off(int msk)
{
 OUT_VAR &= ~msk;
}
*/
//-----------------------------
void f_alarm()
{
   ff_serv_N=f_MVD_cor;
   tm_mvd_p=TimeStamp;
   t_prep_MVD=TimeStamp;
   State_SLV=Stp_cnt;
   f_reg_cmn(13);

           fl_GO=0;
   TimeOut3=TimeStamp-Out3_delay_off;
}

int fl_GO_t=0;

//-----------------------------
void f_sens()
{ // �஢���� ���ﭨ� ������ ES � UZA �� ���᪥/�ਥ�� ���
  // ᨣ���� ��祧���  - ����/�ਥ� ���뢠����
  // inp1 - ES
  // inp2 - UZA


//  i7060_out[0] = itmp;

  if(( fl_GO == 0) && ( fl_GO_t == 0) )
  {
       if( ( IN_CLS_H)==0 )
        {
           f_icp_errS(OPN_H);
           f_reg_cmn(40);
        }
       if( ( IN_CLS_L)==0 )
        {
           f_icp_errS(OPN_L);
           f_reg_cmn(41);
        }
  }
  else if( fl_GO != 0)
  {

   if( Flag_Low == 0)
   {
#if defined(BIO_1)
    if(OUT_or == 0)
    {
       f_icp_errS(No_Src);
       goto m_err1;
    }
#endif
    if( (INP_VARi0  & INP_MSK_OK) != INP_MSK_OK )
    {

       if((  ES_IN)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
       if( ( UZA_IN)==0 )
        {
           flagE_UZA=UZA_E;
m_err:
           flagS_UZA=1;
           f_icp_errS(UZA_off);
m_err1:
           f_alarm();
           f_stop_cnt();
                   f_reg_cmn(13);
           sw_dlv_liq=-1;
           f_clr_scr_MMI();
           f_disp_error();

//         MmiGotoxy(0,5);   MmiPuts("���� ����������.ESC - ����");
//         MmiGotoxy(0,6);   MmiPuts("Sht-ESC ���⪠ �訡��");
           MmiGotoxy(0,14);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,15);   MmiPuts(list_avt[1]);
           goto m1;
        }
       if( ( LVL_IN)==0 )
        {
           flagE_UZA=LVL_E;
           goto m_err;
        }
       if( (TRAP_IN)==0 )
        {
           flagE_UZA=TRAP_E;
           goto m_err;
        }
       if( ( CONS_IN)==0 )
        {
           flagE_UZA=CONS_E;
           goto m_err;
        }
       if((  ES_IN_L)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
    }
   }
   else
   { // ������ �����

    if( (INP_VARi0  & INP_MSK_OK_L) != INP_MSK_OK_L )
     {
       if( ( UZA_IN_L)==0 )
        {
          flagE_UZA=UZA_E;
          goto m_err;
        }
       if((  ES_IN_L)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
       if((  ES_IN)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
       if( ( LVL_IN_L)==0 )
        {
           flagE_UZA=LVL_E;
           goto m_err;
        }
///uuu///////////////////////////////////////////
       if( (CONS_IN_L)==0 )
        {
           flagE_UZA=CONS_L_E;
           goto m_err;
        }
/////////////////////////////////////////////////
     }
   }
  }
m1:
  if(flag_O3 != 0)
   if( (( Flag_Low == 0) && ( OUT_VAR & (CLP0|OUT1|OUT2) )) ||
       (( Flag_Low != 0) && ( OUT_VAR & (CLP0|OUT5|OUT6) ))     )
  {
    if( *DriveStatus != 0)
    {
       if(f_Drive_Rn_chk() != 1)
       {
         flagS_DLT=1;
         f_icp_errS(DLT_off);
         f_alarm();
         f_stop_cnt();
                 f_reg_cmn(13);
       }
    }
  }
  return;
}
//-----------------------------
unsigned int INP_7188=0;

int do1_t=-1, do2_t=-1;

void f_inp7188()
{
// ������ �室�� ᨣ����  I7188 � �����뢠�� �� �
// D8,D9 INP_VAR
 int do_tmp;
 INP_7188 = 0;
 INP_7188 |= GetDi1();
 INP_7188 |= GetDi2();

   do_tmp=OUT_VAR & 0x0100;

  if(do1_t != do_tmp)
  {
   do1_t = do_tmp;
   if(do1_t  )  SetDo1(1);
   else   SetDo1(0);
  }


  do_tmp=OUT_VAR & 0x0200;

  if(do2_t != do_tmp)
  {
   do2_t = do_tmp;
   if(do2_t  )  SetDo2(1);
   else   SetDo2(0);
  }


}

//-------------------------------
void f_tst(int ii)
{
WriteNVRAM((int) nr_flg_n  ,ii );
}
//-------------------------------
void f_tst1(int ii)
{
WriteNVRAM((int) (nr_flg_n+1)  ,ii );
}
//-------------------------------
void f_tst2(int ii)
{
WriteNVRAM((int) (nr_flg_n+2)  ,ii );
}
//-------------------------------
