/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
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
*                                        BOARD SUPPORT PACKAGE
*
*                             LUMINARY MICRO LM3S1968 on the EK-LM3S1968
*
* Filename      : bsp.c
* Version       : V1.02
* Programmer(s) : BAN
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define   BSP_MODULE
#include <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* -------------------- GPIOA PINS -------------------- */
#define  BSP_GPIOA_U0RX                         DEF_BIT_00      /* UART0 Receive.                                       */
#define  BSP_GPIOA_U0TX                         DEF_BIT_01      /* UART1 Transmit.                                      */
#define  BSP_GPIOA_SSI0CLK                      DEF_BIT_02      /* OLED.                                                */
#define  BSP_GPIOA_OLEDCSN                      DEF_BIT_03      /* OLED Chip Select.                                    */
#define  BSP_GPIOA_SSI0RX                       DEF_BIT_04      /* OLED.                                                */

                                                                /* -------------------- GPIOC PINS -------------------- */
#define  BSP_GPIOC_OLEDDC                       DEF_BIT_07      /* OLED.                                                */

                                                                /* -------------------- GPIOG PINS -------------------- */
#define  BSP_GPIOG_PWM0                         DEF_BIT_02      /* User LED.                                            */
#define  BSP_GPIOG_SW_UP                        DEF_BIT_03      /* User Button: Up.                                     */
#define  BSP_GPIOG_SW_DOWN                      DEF_BIT_04      /* User Button: Down.                                   */
#define  BSP_GPIOG_SW_LEFT                      DEF_BIT_05      /* User Button: Left.                                   */
#define  BSP_GPIOG_SW_RIGHT                     DEF_BIT_06      /* User Button: Right.                                  */
#define  BSP_GPIOG_SW_SELECT                    DEF_BIT_07      /* User Button: Select.                                 */

                                                                /* -------------------- GPIOH PINS -------------------- */
#define  BSP_GPIOH_PWM2                         DEF_BIT_00      /* Sound.                                               */
#define  BSP_GPIOH_PWM3                         DEF_BIT_01      /* Sound.                                               */


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_LED_Init(void);

static  void  BSP_PB_Init (void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
    BSP_IntInit();

    RIT128x96x4Init(3500000);

    BSP_LED_Init();                                             /* Initialize the I/Os for the LED controls.            */
    BSP_PB_Init();                                              /* Initialize the I/Os for the PB  controls.            */
}


/*
*********************************************************************************************************
*                                          BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    CPU_INT32U  freq;


    freq = SysCtlClockGet();
    return (freq);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           BSP_LED_Init()
*
* Description : Initialize the I/O for the LEDs
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_LED_Init (void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    GPIODirModeSet(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, GPIO_DIR_MODE_OUT);
    GPIOPadConfigSet(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    BSP_LED_Off(0);                                             /* Turn OFF all the LEDs.                               */
}


/*
*********************************************************************************************************
*                                            BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn ON all LEDs on the board
*                       1    turn ON LED
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0:
        case 1:
             GPIOPinWrite(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, 0);
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn OFF all LEDs on the board
*                       1    turn OFF LED
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0:
        case 1:
             GPIOPinWrite(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, BSP_GPIOG_PWM0);
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                          BSP_LED_Toggle()
*
* Description : TOGGLE any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    TOGGLE all LEDs on the board
*                       1    TOGGLE LED
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U led)
{
    CPU_INT32U  pins;


    switch (led) {
        case 0:
        case 1:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_PWM0);
             if (DEF_BIT_IS_CLR(pins, BSP_GPIOG_PWM0) == DEF_YES) {
                 GPIOPinWrite(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, BSP_GPIOG_PWM0);
             } else {
                 GPIOPinWrite(GPIO_PORTG_BASE, BSP_GPIOG_PWM0, 0);
             }
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            PB FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            BSP_PB_Init()
*
* Description : Initialize the board's PB.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_PB_Init (void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

    GPIODirModeSet(  GPIO_PORTG_BASE, BSP_GPIOG_SW_SELECT | BSP_GPIOG_SW_UP | BSP_GPIOG_SW_DOWN | BSP_GPIOG_SW_LEFT | BSP_GPIOG_SW_RIGHT, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTG_BASE, BSP_GPIOG_SW_SELECT | BSP_GPIOG_SW_UP | BSP_GPIOG_SW_DOWN | BSP_GPIOG_SW_LEFT | BSP_GPIOG_SW_RIGHT, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}


/*
*********************************************************************************************************
*                                         BSP_PB_GetStatus()
*
* Description : Get the status of a push button on the board.
*
* Argument(s) : pb      The ID of the push button to probe
*
*                       1    probe the SELECT push button
*                       2    probe the UP     push button
*                       3    probe the DOWN   push button
*                       4    probe the LEFT   push button
*                       5    probe the RIGHT  push button
*
* Return(s)   : DEF_FALSE   if the push button is pressed.
*               DEF_TRUE    if the push button is not pressed.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_GetStatus (CPU_INT08U pb)
{
    CPU_BOOLEAN  status;
    CPU_INT32U   pins;


    status = DEF_FALSE;

    switch (pb) {
        case 1:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_SW_SELECT);
             if (pins == 0) {
                 status = DEF_TRUE;
             }
             break;

        case 2:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_SW_UP);
             if (pins == 0) {
                 status = DEF_TRUE;
             }
             break;

        case 3:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_SW_DOWN);
             if (pins == 0) {
                 status = DEF_TRUE;
             }
             break;

        case 4:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_SW_LEFT);
             if (pins == 0) {
                 status = DEF_TRUE;
             }
             break;

        case 5:
             pins = GPIOPinRead(GPIO_PORTG_BASE, BSP_GPIOG_SW_RIGHT);
             if (pins == 0) {
                 status = DEF_TRUE;
             }
             break;

        default:
             break;
    }

    return (status);
}
