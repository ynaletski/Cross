//01.10.20 YN -\\//- используется в State_SLV
//#define Cmd_brk       0
#define en_cross        660 //положение перекидки устроило после I7=666 => начинаем обнуление расходомера
#define dis_cross       661 //неверное положение перекидки после установки I7=666 
#define en_start        662 //расх-р подготовлен можно начинать считать первый проход
#define en_start_pause  663 //первый проход пройден ждем пока перекидка дойдет до второго концевика
#define en_start_back   664 //перекидка в правильном положении можно начинать считать обратный проход
#define finished        665 //измерение закончено запуск останова счета //после останова счета установится в 0
                            //State_SLV установится в 0
    //10.10.20 YN -\\//- используется в State_SLV
    #define en_time         880 //положение перекидки не изветно
    #define bak             881 //положение перекидки в бак
    #define calc_bak        882 //можно произвести расчет полета в бак
    #define vesbl           883 //положение перекидки на весы
    #define calc_vesbl      884 //можно произвести расчет полета на весы
    //YN -//\\-
        //13.10.20 YN -\\//- используется в State_SLV
        #define en_cmpr        990 //включен режим сличения
        #define dis_cmpr       991 //неверное положение di_1
        #define en_cmpr_strt   992 //расх-р подготовлен можно начинать
        #define en_cmpr_cnt    993 //идет процесс сличения
        #define cmpr_end       994 //измерение закончено запуск останова счета //после останова счета установится в 0
        //YN -//\\-

//flag_motion: часть для массового метода и сличения:
#define fl_frd_x    1 //время сдвига перекидки вперед записано можно расчитывать интерполированную массу
#define fl_back_x   2 //время сдвига перекидки назад записано можно расчитывать интерполированную массу 
//flag_motion: часть для измерения времени:
#define fl_frd_first    10 //первая точка пролета вперед записана
#define fl_frd_second   11 //вторая точка пролета вперед записана
#define fl_bck_first    12 //первая точка пролета назад записана
#define fl_bck_second   13 //вторая точка пролета назад записана

//-------- YN -//\\-

#define CL1_SRC      (1)
#define CL2_SRC    (0x2)
#define Pump_MDB   (0x1)

#define Addr2Slot1  2000
#define Addr2Slot2  3000
#define Addr2Slot3  4000
#define Addr2Slot4  5000

#define Slv_deb  0
#define Slv_deb_rtu  0

#define Cmd_reg    7

#define i_cfm    (19)
#define Strt_cmd  (0x55)

#define Cmd_brk    0
#define Cmd_err   -1
#define Cmd_rcv    1
#define Beg_cnt    2
#define Stp_cnt    5
#define End_DLV    10
#define Zer_p      30
#define Zer_end    31
#define Zer_err    32
#define n_buf_RTU_s 200

#define Zer_p_cmn    30
#define Zer_end_cmn  31
#define Zer_err_cmn  32


#define Mod_flow_s   27
#define Mod_flow_a   28
#define Mod_flow_e   29

#define Mod_flow_s_cmn   27
#define Mod_flow_a_cmn   28
#define Mod_flow_e_cmn   29

 // функция не распознана
#define  RTU_err_fn  1

 // недопустимый адрес
#define  RTU_Addr  2

// недопустимые данные
#define  RTU_Val   3

// ошибка в Slave
#define  RTU_Slv_err  4


#define Slv_b_lgth  2048
#define Slv_b_lgth_1 2047

#define M_RD   0
#define M_WR   0x80
#define mess_lgth 26

#define i_fl_cd  9   // индекс в Slv_int ячейки с кодом кодировки float
                     // аналог регистра 521 в MVD

//#define cod_float (Slv_int[i_fl_cd] )
//#define n_sl_int  20
//#define n_sl_flt  20

#define AddrLowInt 0
#define AddrHighInt (AddrLowInt+n_sl_int-1)

#define AddrLowFloat  1000
#define AddrHighFloat (AddrLowFloat + n_sl_flt0 + n_sl_flt0 + n_sl_lng + n_sl_lng -  2 )

#define AddrLowLong (AddrLowFloat + n_sl_flt0 + n_sl_flt0 )


struct stor_buf
{
long int time;
char type_n;
char messg[mess_lgth];
};

//01.10.20 YN -\\//-
extern int intrpt_nb; // 0 or 1  очередь в прерывании 
extern int di_1;
extern int di_2;

extern int flag_motion;

extern long int start_time;

extern int choice;
//-------- YN -//\\-

extern int flag_Slv;
extern int ComPortSlv;
extern int AddrSlv;

extern unsigned long ComBaudSlv;
extern int Com_lgthSlv;
extern int Com_paritySlv;
extern int Com_stopSlv;
extern struct stor_buf *bf_Slv;
extern int uk_beg_Slv;
extern int uk_fin_Slv;
extern int Slv_int[];
extern float Slv_float[];

extern int cod_float;

extern void *list_Slv_int[];
extern float *list_Slv_flt[];
extern int n_sl_int ;
extern int n_sl_int1;
extern int n_sl_flt;
extern int n_sl_flt1;

extern int State_SLV;
extern int sw_mmi_slv;
extern int sw_dlv_slv;
extern int Last_evt;

extern int  WD_PMP_flag;
extern int  WD_PMP_Fl;
extern long int WD_PMP_time;
extern long int WD_PMP_Per;
extern float Com_Baud_Slave;


void f_SlaveRTU();
void f_get_SlvBuf();
void f_free_SlvBuf();
void f_stor_Slv( char type,char *buf,int buf_n);
int ffgets_SlvRTU(int ComPort);
void  f_intr_SlvRTU();
int f_get_numRTU2(int ComPort);
int f_get_numRTU7(int ComPort);

int f_is_int(int addr);
int f_is_float(int addr);

void f_prn_slv1();

int  f_int_fnc(int Addr);
int f_stop_dlv();
int f_alm_stop();
int f_rst_slv();
int f_CE_slv();
int f_start_dlv();
int f_cmd_prn();
int f_WE_slv();
void ff_we_slv();
int f_Zero_slv();

int f_set_slv( struct eee_dat *LIn_D, int Slv_nmbO );

extern int    CMD_IN   ;
extern int    CMD_OUT_p;

extern int flag_ZT;

extern long int Tim_set_out;
extern long int time_set_out;
extern int flag_set_out;

extern int n_sl_flt0;

extern int flag_slvrtu;
extern int nn_comb;

void fun_tim_u(void);

extern long int byte_timout_slv ;
extern long int out_delay_slv   ;

extern int fl_slv_out;
extern int flag_wd_err;

extern void (*ff_Slv)();

#if defined(BIO_1)
extern int OUT_or;
extern int OUT_Pmp;
extern float T_Pmp_delay;
#endif

#if defined(PMP_LG)
extern int T_Pmp_LG;
extern int OUT_Pmp;
#endif


extern float n_id_af;
void f_send_slv();
int f_acces_page();
int f_dsp_16();

extern int reg_cmn;

void f_reg_cmn_clk( );
void f_reg_cmn( int val);
void f_reg_cmn_h( int val);

extern int Flag_sl3;
extern int Slot3_dat[];
extern long int Sl3_time_l;

extern int Sl3_addr;
extern int Sl3_lgth;
extern int Sl3_time;
extern int Sl3_time_mul;
extern int Sl3_nn;

#define max_lgth_sl3 20

extern int Flag_sl31;

extern  float SLT3_N;
extern  float SLT3_A;

void f_mirr();

