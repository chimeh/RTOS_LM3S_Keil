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
*                                      APPLICATION CONFIGURATION
*
*                             LUMINARY MICRO LM3S1968 on the EK-LM3S1968
*
* Filename      : app_cfg.h
* Version       : V1.02
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  APP_CFG_PRESENT
#define  APP_CFG_PRESENT

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             TASK NAMES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_START_PRIO                               3
#define  APP_TASK_USER_IF_PRIO                             4
#define  APP_TASK_KBD_PRIO                                 5
//comment by jim 2013_06_13
//the os task configure, i think it should be in os_cfg,  i move it to os _cfg.
//#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                         256
#define  APP_TASK_USER_IF_STK_SIZE                       256
#define  APP_TASK_KBD_STK_SIZE                           256

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  LIB_STR_CFG_FP_EN                       DEF_DISABLED

#define  LIB_MEM_CFG_ARG_CHK_EXT_EN              DEF_ENABLED
#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN             DEF_ENABLED
#define  LIB_MEM_CFG_ALLOC_EN                    DEF_ENABLED
#define  LIB_MEM_CFG_HEAP_SIZE                          800u

/*
*********************************************************************************************************
*                                               TRACING
*********************************************************************************************************
*/

extern  int  BSP_Print(const char *fmt, ...);
#define  TRACE_LEVEL_OFF                                   0
#define  TRACE_LEVEL_INFO                                  1
#define  TRACE_LEVEL_DBG                                   2

#define  APP_TRACE_LEVEL                        TRACE_LEVEL_OFF
#define  APP_TRACE                              BSP_Print

#define  APP_TRACE_INFO(x)                    ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO) ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                     ((APP_TRACE_LEVEL >= TRACE_LEVEL_DBG)  ? (void)(APP_TRACE x) : (void)0)


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
