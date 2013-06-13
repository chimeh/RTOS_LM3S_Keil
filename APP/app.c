/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                              (c) Copyright 2009; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                             LUMINARY MICRO LM3S1968 on the EK-LM3S1968
*
* Filename      : app.c
* Version       : V1.02
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_LCD_ROW0_Y             0x00u
#define  APP_LCD_ROW0_5_Y           0x08u
#define  APP_LCD_ROW1_Y             0x10u
#define  APP_LCD_ROW1_5_Y           0x18u
#define  APP_LCD_ROW2_Y             0x20u
#define  APP_LCD_ROW2_5_Y           0x28u
#define  APP_LCD_ROW3_Y             0x30u
#define  APP_LCD_ROW3_5_Y           0x38u
#define  APP_LCD_ROW4_Y             0x40u
#define  APP_LCD_ROW4_5_Y           0x48u
#define  APP_LCD_ROW5_Y             0x50u
#define  APP_LCD_ROW5_5_Y           0x58u

#define  APP_USER_IF_MAX               4u


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK        App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK        App_TaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
static  OS_STK        App_TaskKbdStk[APP_TASK_KBD_STK_SIZE];

static  OS_EVENT     *App_UserIFMbox;
static  CPU_CHAR      App_UserIFLine1[30];
static  CPU_CHAR      App_UserIFLine2[30];
static  CPU_CHAR      App_UserIFLine3[30];
static  CPU_CHAR      App_UserIFLine4[30];
static  CPU_CHAR      App_UserIFLine5[30];
static  CPU_CHAR      App_UserIFLine6[30];

static  CPU_BOOLEAN   App_B1;
static  CPU_BOOLEAN   App_B2;
static  CPU_BOOLEAN   App_B3;
static  CPU_BOOLEAN   App_B4;
static  CPU_BOOLEAN   App_B5;

static  CPU_INT32U    App_B1Counts;
static  CPU_INT32U    App_B2Counts;
static  CPU_INT32U    App_B3Counts;
static  CPU_INT32U    App_B4Counts;
static  CPU_INT32U    App_B5Counts;


/*
*********************************************************************************************************
*                                            LOCAL MACRO'S
*********************************************************************************************************
*/

#define  APP_TASK_STOP();                         { while (DEF_ON) { \
                                                        ;            \
                                                    }                \
                                                  }


#define  APP_TEST_ERR(err_var, err_code)          { if ((err_var) != (err_code)) {                                                                \
                                                        APP_TRACE_DBG(("    %s() error #%05d @ line #%05d\n\r", __func__, (err_var), __LINE__)); \
                                                    }                                                                                             \
                                                  }

#define  APP_TEST_FAULT(err_var, err_code)        { APP_TEST_ERR(err_var, err_code); \
                                                    if ((err_var) != (err_code)) {   \
                                                        APP_TASK_STOP();             \
                                                    }                                \
                                                  }


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  App_TaskStart                 (void  *p_arg);
static  void  App_TaskCreate                (void);
static  void  App_EventCreate               (void);

static  void  App_TaskKbd                   (void  *p_arg);
static  void  App_TaskUserIF                (void  *p_arg);

static  void  App_DispScr_SignOn            (void);
static  void  App_DispScr_VersionTickRateCPU(void);
static  void  App_DispScr_CtxSw             (void);
static  void  App_DispScr_Inputs            (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    INT8U    os_err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR  cpu_err;
#endif


    BSP_IntDisAll();                                            /* Disable all ints until we are ready to accept them.  */

    BSP_Init();                                                 /* Initialize BSP.                                      */
    CPU_Init();                                                 /* Initialize CPU.                                      */
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet("LM3S1968", &cpu_err);
#endif

    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */

    os_err = OSTaskCreateExt((void (*)(void *)) App_TaskStart,  /* Create the start task.                               */
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_START_PRIO,
                             (INT16U          ) APP_TASK_START_PRIO,
                             (OS_STK        * )&App_TaskStartStk[0],
                             (INT32U          ) APP_TASK_START_STK_SIZE,
                             (void          * )0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    APP_TEST_FAULT(os_err, OS_ERR_NONE);

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(APP_TASK_START_PRIO, (INT8U *)"Start Task", &os_err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */

    return (0);
}


/*
*********************************************************************************************************
*                                           App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskStart (void *p_arg)
{
    CPU_INT32U  cnts;


    (void)p_arg;                                                /* Prevent compiler warning.                            */


                                                                /* ------------------- INIT MODULES ------------------- */
    cnts = BSP_CPU_ClkFreq() / (CPU_INT32U)OS_TICKS_PER_SEC;
    OS_CPU_SysTickInit(cnts);                                   /* Initialize the SysTick.                              */

    Mem_Init();                                                 /* Initialize mem mgmt module.                          */
    Math_Init();                                                /* Initialize math     module.                          */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity.                              */
#endif

    BSP_SerInit(BSP_SER_ID_UART0, 115200u);



                                                                /* --------------------- INIT APP --------------------- */
    App_EventCreate();                                          /* Create application events.                           */
    App_TaskCreate();                                           /* Create application tasks.                            */



                                                                /* -------------------- START TASK -------------------- */
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        BSP_LED_Toggle(1);
        OSTimeDly(OS_TICKS_PER_SEC / 4);
    }
}


/*
*********************************************************************************************************
*                                          App_EventCreate()
*
* Description : Create the application events.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_EventCreate (void)
{
#if (OS_EVENT_NAME_EN > 0)
    INT8U  os_err;
#endif


    App_UserIFMbox = OSMboxCreate((void *)0);                   /* Create MBOX for communication between Kbd and UserIF.*/

    if (App_UserIFMbox == (OS_EVENT *)0) {
        APP_TASK_STOP();
    }

#if (OS_EVENT_NAME_EN > 0)
    OSEventNameSet(App_UserIFMbox, "User IF Mbox", &os_err);
#endif
}


/*
*********************************************************************************************************
*                                          App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskCreate (void)
{
    INT8U  os_err;


                                                                /* ---------------- CREATE USER IF TASK --------------- */
    os_err = OSTaskCreateExt((void (*)(void *)) App_TaskUserIF,
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskUserIFStk[APP_TASK_USER_IF_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_USER_IF_PRIO,
                             (INT16U          ) APP_TASK_USER_IF_PRIO,
                             (OS_STK        * )&App_TaskUserIFStk[0],
                             (INT32U          ) APP_TASK_USER_IF_STK_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    APP_TEST_FAULT(os_err, OS_ERR_NONE); 

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(APP_TASK_USER_IF_PRIO, (INT8U *)"User IF", &os_err);
#endif



                                                                /* ------------------ CREATE KBD TASK ----------------- */
    os_err = OSTaskCreateExt((void (*)(void *)) App_TaskKbd,
                             (void          * ) 0,
                             (OS_STK        * )&App_TaskKbdStk[APP_TASK_KBD_STK_SIZE - 1],
                             (INT8U           ) APP_TASK_KBD_PRIO,
                             (INT16U          ) APP_TASK_KBD_PRIO,
                             (OS_STK        * )&App_TaskKbdStk[0],
                             (INT32U          ) APP_TASK_KBD_STK_SIZE,
                             (void          * ) 0,
                             (INT16U          )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

    APP_TEST_FAULT(os_err, OS_ERR_NONE);  

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(APP_TASK_KBD_PRIO, (INT8U *)"Kbd", &os_err);
#endif
}


/*
*********************************************************************************************************
*                                            App_TaskKbd()
*
* Description : Monitor the state of the push buttons and passes messages to AppTaskUserIF()
*
* Argument(s) : p_arg       Argument passed to 'AppTaskKbd()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/
static  void  App_TaskKbd (void *p_arg)
{
    CPU_BOOLEAN  b1_prev;
    CPU_BOOLEAN  b2_prev;
    CPU_BOOLEAN  b3_prev;
    CPU_BOOLEAN  b4_prev;
    CPU_BOOLEAN  b5_prev;
    CPU_INT08U   key;


    (void)p_arg;

    key     = 2u;

    b1_prev = DEF_FALSE;
    b2_prev = DEF_FALSE;
    b3_prev = DEF_FALSE;
    b4_prev = DEF_FALSE;
    b5_prev = DEF_FALSE;

    App_B1  = DEF_FALSE;
    App_B2  = DEF_FALSE;
    App_B3  = DEF_FALSE;
    App_B4  = DEF_FALSE;
    App_B5  = DEF_FALSE;

    while (DEF_TRUE) {
        App_B1 = BSP_PB_GetStatus(1);
        App_B2 = BSP_PB_GetStatus(2);
        App_B3 = BSP_PB_GetStatus(3);
        App_B4 = BSP_PB_GetStatus(4);
        App_B5 = BSP_PB_GetStatus(5);

        if ((App_B1 == DEF_TRUE) && (b1_prev == DEF_FALSE)) {
            App_B1Counts++;

            if (key == APP_USER_IF_MAX) {
                key = 1;
            } else {
                key++;
            }
            OSMboxPost(App_UserIFMbox, (void *)key);
        }

        if ((App_B2 == DEF_TRUE) && (b2_prev == DEF_FALSE)) {
            App_B2Counts++;
        }

        if ((App_B3 == DEF_TRUE) && (b3_prev == DEF_FALSE)) {
            App_B3Counts++;
        }

        if ((App_B4 == DEF_TRUE) && (b4_prev == DEF_FALSE)) {
            App_B4Counts++;
        }

        if ((App_B5 == DEF_TRUE) && (b5_prev == DEF_FALSE)) {
            App_B5Counts++;
        }

        b1_prev = App_B1;
        b2_prev = App_B2;
        b3_prev = App_B3;
        b4_prev = App_B4;
        b5_prev = App_B5;
        OSTimeDly(OS_TICKS_PER_SEC / 20);
    }
}


/*
*********************************************************************************************************
*                                          App_TaskUserIF()
*
* Description : Updates LCD.
*
* Argument(s) : p_arg       Argument passed to 'AppTaskUserIF()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskUserIF (void *p_arg)
{
    CPU_INT08U  *msg;
    CPU_INT08U   err;
    CPU_INT32U   nstate;
    CPU_INT32U   pstate;


    (void)p_arg;

    App_DispScr_SignOn();
    OSTimeDly(OS_TICKS_PER_SEC * 2);
    pstate = 1;
    nstate = 2;


    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.           */
        msg = (CPU_INT08U *)(OSMboxPend(App_UserIFMbox, OS_TICKS_PER_SEC / 10, &err));
        if (err == OS_ERR_NONE) {
            nstate = (CPU_INT32U)msg;
        }

        if (nstate != pstate) {
            RIT128x96x4Clear();
            pstate  = nstate;
        }

        switch (nstate) {
            case 2:
                 App_DispScr_VersionTickRateCPU();
                 break;

            case 3:
                 App_DispScr_CtxSw();
                 break;

            case 4:
                 App_DispScr_Inputs();
                 break;

            case 1:
            default:
                 App_DispScr_SignOn();
                 break;
        }
    }
}


/*
*********************************************************************************************************
*                                             DISPLAY SCREENS
*
* Descrition  : Display one of the screens used in the demonstration.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskUserIF().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_DispScr_SignOn (void)
{
    static  CPU_INT08U  count = 0;


    Str_Copy(App_UserIFLine1, "      Micrium       ");
    Str_Copy(App_UserIFLine2, "uC/OS-II    uC-Probe");
    Str_Copy(App_UserIFLine3, "                    ");
    Str_Copy(App_UserIFLine4, "                    ");
    Str_Copy(App_UserIFLine5, "on the LuminaryMicro");
    Str_Copy(App_UserIFLine6, "     EK-LM3S1968    ");

    RIT128x96x4StringDraw((char *)App_UserIFLine1, 0, APP_LCD_ROW0_5_Y, 15);
    if (count < 5) {
        RIT128x96x4StringDraw("uC/OS-II",             0, APP_LCD_ROW1_5_Y, 15);
        RIT128x96x4StringDraw("uC/Probe",            72, APP_LCD_ROW1_5_Y, 10);
    } else if (count < 10) {
        RIT128x96x4StringDraw("uC/OS-II",             0, APP_LCD_ROW1_5_Y, 10);
        RIT128x96x4StringDraw("uC/Probe",            72, APP_LCD_ROW1_5_Y, 15);
    }

    count++;

    if (count >= 10) {
        count = 0;
    }

    RIT128x96x4StringDraw((char *)App_UserIFLine5, 0, APP_LCD_ROW3_5_Y,    5);
    RIT128x96x4StringDraw((char *)App_UserIFLine6, 0, APP_LCD_ROW4_5_Y,    5);
    RIT128x96x4LineDraw(0, 0x00, 128, 15, DEF_TRUE);
    RIT128x96x4LineDraw(0, 0x26, 128, 15, DEF_TRUE);
}

static  void  App_DispScr_VersionTickRateCPU (void)
{
    CPU_INT32U  value;


    Str_Copy(App_UserIFLine1, "      uC/OS-II      ");
    Str_Copy(App_UserIFLine2, "                    ");

    Str_Copy(App_UserIFLine3, "  uC/OS-II:  Vx.yy  ");
    value               = (CPU_INT32U)OSVersion();
    App_UserIFLine3[14] = ((value % 1000) / 100) + '0';
    App_UserIFLine3[16] = ((value %  100) /  10) + '0';
    App_UserIFLine3[17] = ((value %   10) /   1) + '0';

    Str_Copy(App_UserIFLine4, "  TickRate:  xxxx Hz");
    value               = (CPU_INT32U)OS_TICKS_PER_SEC;
    Str_FmtNbr_Int32U(value, 4, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine4[13]);

    Str_Copy(App_UserIFLine5, "  CPU Usage: xxx %  ");
    value               = (CPU_INT32U)OSCPUUsage;
    App_UserIFLine5[13] = ((value % 1000) / 100) + '0';
    App_UserIFLine5[14] = ((value %  100) /  10) + '0';
    App_UserIFLine5[15] = ((value %   10) /   1) + '0';

    Str_Copy(App_UserIFLine6, "  CPU Speed: xx MHz ");
    value               = (CPU_INT32U)SysCtlClockGet() / 1000000L;
    App_UserIFLine6[13] = (value / 10) + '0';
    App_UserIFLine6[14] = (value % 10) + '0';

    RIT128x96x4StringDraw((char *)App_UserIFLine1, 0, APP_LCD_ROW0_5_Y, 15);
    RIT128x96x4StringDraw((char *)App_UserIFLine3, 0, APP_LCD_ROW2_Y,    5);
    RIT128x96x4StringDraw((char *)App_UserIFLine4, 0, APP_LCD_ROW3_Y,    8);
    RIT128x96x4StringDraw((char *)App_UserIFLine5, 0, APP_LCD_ROW4_Y,    5);
    RIT128x96x4StringDraw((char *)App_UserIFLine6, 0, APP_LCD_ROW5_Y,    8);

    RIT128x96x4LineDraw(0, 0x00, 128, 15, DEF_TRUE);
    RIT128x96x4LineDraw(0, 0x16, 128, 15, DEF_TRUE);
}


static  void  App_DispScr_CtxSw (void)
{
    CPU_INT32U  value;


    Str_Copy(App_UserIFLine1, "      uC/OS-II      ");
    Str_Copy(App_UserIFLine2, "                    ");

    Str_Copy(App_UserIFLine3, "  Number of Ticks:  ");

    Str_Copy(App_UserIFLine4, "      xxxxxxxx      ");
    value = (CPU_INT32U)OSTime;
    Str_FmtNbr_Int32U(value, 8, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine4[6]);

    Str_Copy(App_UserIFLine5, "Num. of Context Sw.:");

    Str_Copy(App_UserIFLine6, "      xxxxxxxx      ");
    value = (CPU_INT32U)OSCtxSwCtr;
    Str_FmtNbr_Int32U(value, 8, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine6[6]);

    RIT128x96x4StringDraw((char *)App_UserIFLine1, 0, APP_LCD_ROW0_5_Y, 15);
    RIT128x96x4StringDraw((char *)App_UserIFLine3, 0, APP_LCD_ROW2_Y,    8);
    RIT128x96x4StringDraw((char *)App_UserIFLine4, 0, APP_LCD_ROW3_Y,    5);
    RIT128x96x4StringDraw((char *)App_UserIFLine5, 0, APP_LCD_ROW4_Y,    8);
    RIT128x96x4StringDraw((char *)App_UserIFLine6, 0, APP_LCD_ROW5_Y,    5);

    RIT128x96x4LineDraw(0, 0x00, 128, 15, DEF_TRUE);
    RIT128x96x4LineDraw(0, 0x16, 128, 15, DEF_TRUE);
}


static  void  App_DispScr_Inputs (void)
{
    CPU_INT32U  value;
    CPU_CHAR    str[4];


    Str_Copy(App_UserIFLine1, "    Board Inputs    ");
    Str_Copy(App_UserIFLine2, "                    ");

    Str_Copy(App_UserIFLine3, "    Button Status:  ");

    Str_Copy(App_UserIFLine4, "         xxx        ");
    value = (CPU_INT32U)App_B2Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine4[9]);

    Str_Copy(App_UserIFLine5, "   yyy   xxx   zzz  ");
    value = (CPU_INT32U)App_B4Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine5[3]);
    value = (CPU_INT32U)App_B1Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine5[9]);
    value = (CPU_INT32U)App_B5Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine5[15]);

    Str_Copy(App_UserIFLine6, "         xxx        ");
    value = (CPU_INT32U)App_B3Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &App_UserIFLine6[9]);

    RIT128x96x4StringDraw((char *)App_UserIFLine1, 0, APP_LCD_ROW0_5_Y, 15);
    RIT128x96x4StringDraw((char *)App_UserIFLine3, 0, APP_LCD_ROW2_Y,    8);

    if (App_B2 == DEF_TRUE) {
        RIT128x96x4StringDraw((char *)App_UserIFLine4, 0, APP_LCD_ROW3_Y, 8);
    } else {
        RIT128x96x4StringDraw((char *)App_UserIFLine4, 0, APP_LCD_ROW3_Y, 2);
    }

    Str_Copy(str, "   ");
    value = (CPU_INT32U)App_B4Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &str[0]);

    if (App_B4 == DEF_TRUE) {
        RIT128x96x4StringDraw((char *)str, 6 * 3, APP_LCD_ROW4_Y, 8);
    } else {
        RIT128x96x4StringDraw((char *)str, 6 * 3, APP_LCD_ROW4_Y, 2);
    }

    Str_Copy(str, "   ");
    value = (CPU_INT32U)App_B1Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &str[0]);

    if (App_B1 == DEF_TRUE) {
        RIT128x96x4StringDraw((char *)str, 6 * 9, APP_LCD_ROW4_Y, 8);
    } else {
        RIT128x96x4StringDraw((char *)str, 6 * 9, APP_LCD_ROW4_Y, 2);
    }

    Str_Copy(str, "   ");
    value = (CPU_INT32U)App_B5Counts;
    Str_FmtNbr_Int32U(value, 3, 10, ASCII_CHAR_SPACE, DEF_FALSE, DEF_FALSE, &str[0]);

    if (App_B5 == DEF_TRUE) {
        RIT128x96x4StringDraw((char *)str, 6 * 15, APP_LCD_ROW4_Y, 8);
    } else {
        RIT128x96x4StringDraw((char *)str, 6 * 15, APP_LCD_ROW4_Y, 2);
    }

    if (App_B3 == DEF_TRUE) {
        RIT128x96x4StringDraw((char *)App_UserIFLine6, 0, APP_LCD_ROW5_Y, 8);
    } else {
        RIT128x96x4StringDraw((char *)App_UserIFLine6, 0, APP_LCD_ROW5_Y, 2);
    }

    RIT128x96x4LineDraw(0, 0x00, 128, 15, DEF_TRUE);
    RIT128x96x4LineDraw(0, 0x16, 128, 15, DEF_TRUE);
}
