
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

#ifndef  LIB_CFG_PRESENT
#define  LIB_CFG_PRESENT

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>


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
*                                             MODULE END
*********************************************************************************************************
*/

#endif