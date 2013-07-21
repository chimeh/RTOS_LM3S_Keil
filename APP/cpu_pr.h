#ifndef  CPU_PR
#define  CPU_PR

/*********************************************************************************************************/
typedef            void        CPU_VOID;
typedef            char        CPU_CHAR;                        /*  8-bit character                                     */
typedef  unsigned  char        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
typedef  unsigned  char        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef    signed  char        CPU_INT08S;                      /*  8-bit   signed integer                              */
typedef  unsigned  short       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef    signed  short       CPU_INT16S;                      /* 16-bit   signed integer                              */
typedef  unsigned  int         CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef    signed  int         CPU_INT32S;                      /* 32-bit   signed integer                              */
typedef  unsigned  long  long  CPU_INT64U;                      /* 64-bit unsigned integer                              */
typedef    signed  long  long  CPU_INT64S;                      /* 64-bit   signed integer                              */

typedef            float       CPU_FP32;                        /* 32-bit floating point                                */
typedef            double      CPU_FP64;                        /* 64-bit floating point                                */


typedef  volatile  CPU_INT08U  CPU_REG08;                       /*  8-bit register                                      */
typedef  volatile  CPU_INT16U  CPU_REG16;                       /* 16-bit register                                      */
typedef  volatile  CPU_INT32U  CPU_REG32;                       /* 32-bit register                                      */
typedef  volatile  CPU_INT64U  CPU_REG64;                       /* 64-bit register                                      */


typedef            void      (*CPU_FNCT_VOID)(void);            /* See Note #2a.                                        */
typedef            void      (*CPU_FNCT_PTR )(void *);          /* See Note #2b.                                        */


typedef  CPU_INT32U  CPU_DATA;
typedef  CPU_INT32U  CPU_ADDR;
typedef  CPU_ADDR    CPU_SIZE_T;                                /* Defines CPU standard 'size_t'   size.                */
typedef  CPU_INT16U  CPU_ERR;



/*
*********************************************************************************************************
*                                          STANDARD DEFINES
*********************************************************************************************************
*/

                                                                /* ----------------- BOOLEAN DEFINES ------------------ */
#define  DEF_FALSE                                         0u
#define  DEF_TRUE                                          1u

#define  DEF_NO                                            0u
#define  DEF_YES                                           1u

#define  DEF_DISABLED                                      0u
#define  DEF_ENABLED                                       1u

#define  DEF_INACTIVE                                      0u
#define  DEF_ACTIVE                                        1u

#define  DEF_OFF                                           0u
#define  DEF_ON                                            1u

#define  DEF_CLR                                           0u
#define  DEF_SET                                           1u

#define  DEF_FAIL                                          0u
#define  DEF_OK                                            1u

                                                                /* ------------------- BIT DEFINES -------------------- */
#define  DEF_BIT_NONE                                   0x00u

#define  DEF_BIT_00                                     0x01u
#define  DEF_BIT_01                                     0x02u
#define  DEF_BIT_02                                     0x04u
#define  DEF_BIT_03                                     0x08u
#define  DEF_BIT_04                                     0x10u
#define  DEF_BIT_05                                     0x20u
#define  DEF_BIT_06                                     0x40u
#define  DEF_BIT_07                                     0x80u

#define  DEF_BIT_08                                   0x0100u
#define  DEF_BIT_09                                   0x0200u
#define  DEF_BIT_10                                   0x0400u
#define  DEF_BIT_11                                   0x0800u
#define  DEF_BIT_12                                   0x1000u
#define  DEF_BIT_13                                   0x2000u
#define  DEF_BIT_14                                   0x4000u
#define  DEF_BIT_15                                   0x8000u

#define  DEF_BIT_16                               0x00010000u
#define  DEF_BIT_17                               0x00020000u
#define  DEF_BIT_18                               0x00040000u
#define  DEF_BIT_19                               0x00080000u
#define  DEF_BIT_20                               0x00100000u
#define  DEF_BIT_21                               0x00200000u
#define  DEF_BIT_22                               0x00400000u
#define  DEF_BIT_23                               0x00800000u

#define  DEF_BIT_24                               0x01000000u
#define  DEF_BIT_25                               0x02000000u
#define  DEF_BIT_26                               0x04000000u
#define  DEF_BIT_27                               0x08000000u
#define  DEF_BIT_28                               0x10000000u
#define  DEF_BIT_29                               0x20000000u
#define  DEF_BIT_30                               0x40000000u
#define  DEF_BIT_31                               0x80000000u



#define  DEF_TIME_NBR_mS_PER_SEC                        1000uL
#define  DEF_TIME_NBR_uS_PER_SEC                     1000000uL
#define  DEF_TIME_NBR_nS_PER_SEC                  1000000000uL

/*
*********************************************************************************************************
*                                         ASCII CHARACTER DEFINES
*********************************************************************************************************
*/

                                                                /* -------------------- C0 CONTROLS ------------------- */
#define  ASCII_CHAR_NULL                                0x00    /* '\0'                                                 */
#define  ASCII_CHAR_START_OF_HEADING                    0x01
#define  ASCII_CHAR_START_OF_TEXT                       0x02
#define  ASCII_CHAR_END_OF_TEXT                         0x03
#define  ASCII_CHAR_END_OF_TRANSMISSION                 0x04
#define  ASCII_CHAR_ENQUIRY                             0x05
#define  ASCII_CHAR_ACKNOWLEDGE                         0x06
#define  ASCII_CHAR_BELL                                0x07    /* '\a'                                                 */
#define  ASCII_CHAR_BACKSPACE                           0x08    /* '\b'                                                 */
#define  ASCII_CHAR_CHARACTER_TABULATION                0x09    /* '\t'                                                 */
#define  ASCII_CHAR_LINE_FEED                           0x0A    /* '\n'                                                 */
#define  ASCII_CHAR_LINE_TABULATION                     0x0B    /* '\v'                                                 */
#define  ASCII_CHAR_FORM_FEED                           0x0C    /* '\f'                                                 */
#define  ASCII_CHAR_CARRIAGE_RETURN                     0x0D    /* '\r'                                                 */
#define  ASCII_CHAR_SHIFT_OUT                           0x0E
#define  ASCII_CHAR_SHIFT_IN                            0x0F
#define  ASCII_CHAR_DATA_LINK_ESCAPE                    0x10
#define  ASCII_CHAR_DEVICE_CONTROL_ONE                  0x11
#define  ASCII_CHAR_DEVICE_CONTROL_TWO                  0x12
#define  ASCII_CHAR_DEVICE_CONTROL_THREE                0x13
#define  ASCII_CHAR_DEVICE_CONTROL_FOUR                 0x14
#define  ASCII_CHAR_NEGATIVE_ACKNOWLEDGE                0x15
#define  ASCII_CHAR_SYNCHRONOUS_IDLE                    0x16
#define  ASCII_CHAR_END_OF_TRANSMISSION_BLOCK           0x17
#define  ASCII_CHAR_CANCEL                              0x18
#define  ASCII_CHAR_END_OF_MEDIUM                       0x19
#define  ASCII_CHAR_SUBSITUTE                           0x1A
#define  ASCII_CHAR_ESCAPE                              0x1B
#define  ASCII_CHAR_INFO_SEPARATOR_FOUR                 0x1C
#define  ASCII_CHAR_INFO_SEPARATOR_THREE                0x1D
#define  ASCII_CHAR_INFO_SEPARATOR_TWO                  0x1E
#define  ASCII_CHAR_INFO_SEPARATOR_ONE                  0x1F

#define  ASCII_CHAR_NUL                                 ASCII_CHAR_NULL
#define  ASCII_CHAR_SOH                                 ASCII_CHAR_START_OF_HEADING
#define  ASCII_CHAR_START_HEADING                       ASCII_CHAR_START_OF_HEADING
#define  ASCII_CHAR_STX                                 ASCII_CHAR_START_OF_TEXT
#define  ASCII_CHAR_START_TEXT                          ASCII_CHAR_START_OF_TEXT
#define  ASCII_CHAR_ETX                                 ASCII_CHAR_END_OF_TEXT
#define  ASCII_CHAR_END_TEXT                            ASCII_CHAR_END_OF_TEXT
#define  ASCII_CHAR_EOT                                 ASCII_CHAR_END_OF_TRANSMISSION
#define  ASCII_CHAR_END_TRANSMISSION                    ASCII_CHAR_END_OF_TRANSMISSION
#define  ASCII_CHAR_ENQ                                 ASCII_CHAR_ENQUIRY
#define  ASCII_CHAR_ACK                                 ASCII_CHAR_ACKNOWLEDGE
#define  ASCII_CHAR_BEL                                 ASCII_CHAR_BELL
#define  ASCII_CHAR_BS                                  ASCII_CHAR_BACKSPACE
#define  ASCII_CHAR_HT                                  ASCII_CHAR_CHARACTER_TABULATION
#define  ASCII_CHAR_TAB                                 ASCII_CHAR_CHARACTER_TABULATION
#define  ASCII_CHAR_LF                                  ASCII_CHAR_LINE_FEED
#define  ASCII_CHAR_VT                                  ASCII_CHAR_LINE_TABULATION
#define  ASCII_CHAR_FF                                  ASCII_CHAR_FORM_FEED
#define  ASCII_CHAR_CR                                  ASCII_CHAR_CARRIAGE_RETURN
#define  ASCII_CHAR_SO                                  ASCII_CHAR_SHIFT_OUT
#define  ASCII_CHAR_SI                                  ASCII_CHAR_SHIFT_IN
#define  ASCII_CHAR_DLE                                 ASCII_CHAR_DATA_LINK_ESCAPE
#define  ASCII_CHAR_DC1                                 ASCII_CHAR_DEVICE_CONTROL_ONE
#define  ASCII_CHAR_DC2                                 ASCII_CHAR_DEVICE_CONTROL_TWO
#define  ASCII_CHAR_DC3                                 ASCII_CHAR_DEVICE_CONTROL_THREE
#define  ASCII_CHAR_DC4                                 ASCII_CHAR_DEVICE_CONTROL_FOUR
#define  ASCII_CHAR_DEV_CTRL_ONE                        ASCII_CHAR_DEVICE_CONTROL_ONE
#define  ASCII_CHAR_DEV_CTRL_TWO                        ASCII_CHAR_DEVICE_CONTROL_TWO
#define  ASCII_CHAR_DEV_CTRL_THREE                      ASCII_CHAR_DEVICE_CONTROL_THREE
#define  ASCII_CHAR_DEV_CTRL_FOUR                       ASCII_CHAR_DEVICE_CONTROL_FOUR
#define  ASCII_CHAR_NAK                                 ASCII_CHAR_NEGATIVE_ACKNOWLEDGE
#define  ASCII_CHAR_NEG_ACK                             ASCII_CHAR_NEGATIVE_ACKNOWLEDGE
#define  ASCII_CHAR_SYN                                 ASCII_CHAR_SYNCHRONOUS_IDLE
#define  ASCII_CHAR_SYNC_IDLE                           ASCII_CHAR_SYNCHRONOUS_IDLE
#define  ASCII_CHAR_ETB                                 ASCII_CHAR_END_OF_TRANSMISSION_BLOCK
#define  ASCII_CHAR_END_TRANSMISSION_BLK                ASCII_CHAR_END_OF_TRANSMISSION_BLOCK
#define  ASCII_CHAR_CAN                                 ASCII_CHAR_CANCEL
#define  ASCII_CHAR_EM                                  ASCII_CHAR_END_OF_MEDIUM
#define  ASCII_CHAR_END_MEDIUM                          ASCII_CHAR_END_OF_MEDIUM
#define  ASCII_CHAR_SUB                                 ASCII_CHAR_SUBSITUTE
#define  ASCII_CHAR_ESC                                 ASCII_CHAR_ESCAPE
#define  ASCII_CHAR_IS1                                 ASCII_CHAR_INFO_SEPARATOR_ONE
#define  ASCII_CHAR_IS2                                 ASCII_CHAR_INFO_SEPARATOR_TWO
#define  ASCII_CHAR_IS3                                 ASCII_CHAR_INFO_SEPARATOR_THREE
#define  ASCII_CHAR_IS4                                 ASCII_CHAR_INFO_SEPARATOR_FOUR


/*$PAGE*/
                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_SPACE                               0x20    /* ' '                                                  */
#define  ASCII_CHAR_EXCLAMATION_MARK                    0x21    /* '!'                                                  */
#define  ASCII_CHAR_QUOTATION_MARK                      0x22    /* '\"'                                                 */
#define  ASCII_CHAR_NUMBER_SIGN                         0x23    /* '#'                                                  */
#define  ASCII_CHAR_DOLLAR_SIGN                         0x24    /* '$'                                                  */
#define  ASCII_CHAR_PERCENTAGE_SIGN                     0x25    /* '%'                                                  */
#define  ASCII_CHAR_AMPERSAND                           0x26    /* '&'                                                  */
#define  ASCII_CHAR_APOSTROPHE                          0x27    /* '\''                                                 */
#define  ASCII_CHAR_LEFT_PARENTHESIS                    0x28    /* '('                                                  */
#define  ASCII_CHAR_RIGHT_PARENTHESIS                   0x29    /* ')'                                                  */
#define  ASCII_CHAR_ASTERISK                            0x2A    /* '*'                                                  */
#define  ASCII_CHAR_PLUS_SIGN                           0x2B    /* '+'                                                  */
#define  ASCII_CHAR_COMMA                               0x2C    /* ','                                                  */
#define  ASCII_CHAR_HYPHEN_MINUS                        0x2D    /* '-'                                                  */
#define  ASCII_CHAR_FULL_STOP                           0x2E    /* '.'                                                  */
#define  ASCII_CHAR_SOLIDUS                             0x2F    /* '/'                                                  */

#define  ASCII_CHAR_PAREN_LEFT                          ASCII_CHAR_LEFT_PARENTHESIS
#define  ASCII_CHAR_PAREN_RIGHT                         ASCII_CHAR_RIGHT_PARENTHESIS


                                                                /* ------------------- ASCII DIGITS ------------------- */
#define  ASCII_CHAR_DIGIT_ZERO                          0x30    /* '0'                                                  */
#define  ASCII_CHAR_DIGIT_ONE                           0x31    /* '1'                                                  */
#define  ASCII_CHAR_DIGIT_TWO                           0x32    /* '2'                                                  */
#define  ASCII_CHAR_DIGIT_THREE                         0x33    /* '3'                                                  */
#define  ASCII_CHAR_DIGIT_FOUR                          0x34    /* '4'                                                  */
#define  ASCII_CHAR_DIGIT_FIVE                          0x35    /* '5'                                                  */
#define  ASCII_CHAR_DIGIT_SIX                           0x36    /* '6'                                                  */
#define  ASCII_CHAR_DIGIT_SEVEN                         0x37    /* '7'                                                  */
#define  ASCII_CHAR_DIGIT_EIGHT                         0x38    /* '8'                                                  */
#define  ASCII_CHAR_DIGIT_NINE                          0x39    /* '9'                                                  */

#define  ASCII_CHAR_DIG_ZERO                            ASCII_CHAR_DIGIT_ZERO
#define  ASCII_CHAR_DIG_ONE                             ASCII_CHAR_DIGIT_ONE
#define  ASCII_CHAR_DIG_TWO                             ASCII_CHAR_DIGIT_TWO
#define  ASCII_CHAR_DIG_THREE                           ASCII_CHAR_DIGIT_THREE
#define  ASCII_CHAR_DIG_FOUR                            ASCII_CHAR_DIGIT_FOUR
#define  ASCII_CHAR_DIG_FIVE                            ASCII_CHAR_DIGIT_FIVE
#define  ASCII_CHAR_DIG_SIX                             ASCII_CHAR_DIGIT_SIX
#define  ASCII_CHAR_DIG_SEVEN                           ASCII_CHAR_DIGIT_SEVEN
#define  ASCII_CHAR_DIG_EIGHT                           ASCII_CHAR_DIGIT_EIGHT
#define  ASCII_CHAR_DIG_NINE                            ASCII_CHAR_DIGIT_NINE


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_COLON                               0x3A    /* ':'                                                  */
#define  ASCII_CHAR_SEMICOLON                           0x3B    /* ';'                                                  */
#define  ASCII_CHAR_LESS_THAN_SIGN                      0x3C    /* '<'                                                  */
#define  ASCII_CHAR_EQUALS_SIGN                         0x3D    /* '='                                                  */
#define  ASCII_CHAR_GREATER_THAN_SIGN                   0x3E    /* '>'                                                  */
#define  ASCII_CHAR_QUESTION_MARK                       0x3F    /* '\?'                                                 */
#define  ASCII_CHAR_COMMERCIAL_AT                       0x40    /* '@'                                                  */

#define  ASCII_CHAR_AT_SIGN                             ASCII_CHAR_COMMERCIAL_AT


/*$PAGE*/
                                                                /* ------------- UPPERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_UPPER_A                       0x41    /* 'A'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_B                       0x42    /* 'B'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_C                       0x43    /* 'C'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_D                       0x44    /* 'D'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_E                       0x45    /* 'E'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_F                       0x46    /* 'F'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_G                       0x47    /* 'G'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_H                       0x48    /* 'H'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_I                       0x49    /* 'I'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_J                       0x4A    /* 'J'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_K                       0x4B    /* 'K'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_L                       0x4C    /* 'L'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_M                       0x4D    /* 'M'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_N                       0x4E    /* 'N'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_O                       0x4F    /* 'O'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_P                       0x50    /* 'P'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Q                       0x51    /* 'Q'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_R                       0x52    /* 'R'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_S                       0x53    /* 'S'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_T                       0x54    /* 'T'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_U                       0x55    /* 'U'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_V                       0x56    /* 'V'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_W                       0x57    /* 'W'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_X                       0x58    /* 'X'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Y                       0x59    /* 'Y'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Z                       0x5A    /* 'Z'                                                  */


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_SQUARE_BRACKET                 0x5B    /* '['                                                  */
#define  ASCII_CHAR_REVERSE_SOLIDUS                     0x5C    /* '\\'                                                 */
#define  ASCII_CHAR_RIGHT_SQUARE_BRACKET                0x5D    /* ']'                                                  */
#define  ASCII_CHAR_CIRCUMFLEX_ACCENT                   0x5E    /* '^'                                                  */
#define  ASCII_CHAR_LOW_LINE                            0x5F    /* '_'                                                  */
#define  ASCII_CHAR_GRAVE_ACCENT                        0x60    /* '`'                                                  */

#define  ASCII_CHAR_BRACKET_SQUARE_LEFT                 ASCII_CHAR_LEFT_SQUARE_BRACKET
#define  ASCII_CHAR_BRACKET_SQUARE_RIGHT                ASCII_CHAR_RIGHT_SQUARE_BRACKET


                                                                /* ------------- LOWERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_LOWER_A                       0x61    /* 'a'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_B                       0x62    /* 'b'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_C                       0x63    /* 'c'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_D                       0x64    /* 'd'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_E                       0x65    /* 'e'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_F                       0x66    /* 'f'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_G                       0x67    /* 'g'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_H                       0x68    /* 'h'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_I                       0x69    /* 'i'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_J                       0x6A    /* 'j'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_K                       0x6B    /* 'k'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_L                       0x6C    /* 'l'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_M                       0x6D    /* 'm'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_N                       0x6E    /* 'n'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_O                       0x6F    /* 'o'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_P                       0x70    /* 'p'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Q                       0x71    /* 'q'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_R                       0x72    /* 'r'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_S                       0x73    /* 's'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_T                       0x74    /* 't'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_U                       0x75    /* 'u'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_V                       0x76    /* 'v'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_W                       0x77    /* 'w'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_X                       0x78    /* 'x'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Y                       0x79    /* 'y'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Z                       0x7A    /* 'z'                                                  */


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_CURLY_BRACKET                  0x7B    /* '{'                                                  */
#define  ASCII_CHAR_VERTICAL_LINE                       0x7C    /* '|'                                                  */
#define  ASCII_CHAR_RIGHT_CURLY_BRACKET                 0x7D    /* '}'                                                  */
#define  ASCII_CHAR_TILDE                               0x7E    /* '~'                                                  */

#define  ASCII_CHAR_BRACKET_CURLY_LEFT                  ASCII_CHAR_LEFT_CURLY_BRACKET
#define  ASCII_CHAR_BRACKET_CURLY_RIGHT                 ASCII_CHAR_RIGHT_CURLY_BRACKET


                                                                /* ---------------- CONTROL CHARACTERS ---------------- */
#define  ASCII_CHAR_DELETE                              0x7F

#define  ASCII_CHAR_DEL                                 ASCII_CHAR_DELETE

#endif
