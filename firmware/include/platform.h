#pragma once

#include <stdint.h>

/**
 * Definations of STC8H4K64TL-40I-LQFP32
 *
 * IRC      : 35 MHz
 * Timer0   : System clock.
 * Timer1   : 1-wire bus timer.
 * Timer2   : UART0.
 * Timer3   : Fan pwm.
 * Timer4   : Display.
 * UART0    : Debug console.
 */
#define IRC_FEQ 35000000

#if defined EDITOR_AUTO_COMPLETE
    // Auto-complete.
    #define __data
    #define __idata
    #define __xdata
    #define __at(addr)
    #define __sfr  uint8_t
    #define __sbit uint8_t
    #define __interrupt(v)
    #define INT_INT0
    #define INT_TIMER0
    #define INT_INT1
    #define INT_TIMER1
    #define INT_UART1
    #define INT_ADC
    #define INT_TIMER2
    #define INT_TIMER3
    #define INT_TIMER4

#else
    #define INT_INT0   0
    #define INT_TIMER0 1
    #define INT_INT1   2
    #define INT_TIMER1 3
    #define INT_UART1  4
    #define INT_ADC    5
    #define INT_TIMER2 12
    #define INT_TIMER3 19
    #define INT_TIMER4 20

#endif

#if ! defined(NAN)
    #define NAN (0.0f / 0.0f)
#endif

// Memory
__sfr __at(0xBA) P_SW2;

// I/O ports.
// P0
__sfr  __at(0x80) P0;
__sbit __at(0x80) P0_0;
__sbit __at(0x81) P0_1;
__sbit __at(0x82) P0_2;
__sbit __at(0x83) P0_3;
__sbit __at(0x84) P0_4;
__sbit __at(0x85) P0_5;
__sbit __at(0x86) P0_6;
__sbit __at(0x87) P0_7;

__sfr __at(0x93) P0M1;
__sfr __at(0x94) P0M0;

#define P0PU (*((volatile uint8_t *)0xFE10))

// P1
__sfr  __at(0x90) P1;
__sbit __at(0x90) P1_0;
__sbit __at(0x91) P1_1;
__sbit __at(0x92) P1_2;
__sbit __at(0x93) P1_3;
__sbit __at(0x94) P1_4;
__sbit __at(0x95) P1_5;
__sbit __at(0x96) P1_6;
__sbit __at(0x97) P1_7;

__sfr __at(0x91) P1M1;
__sfr __at(0x92) P1M0;

#define P1PU (*((volatile uint8_t *)0xFE11))

// P2
__sfr  __at(0xA0) P2;
__sbit __at(0xA0) P2_0;
__sbit __at(0xA1) P2_1;
__sbit __at(0xA2) P2_2;
__sbit __at(0xA3) P2_3;
__sbit __at(0xA4) P2_4;
__sbit __at(0xA5) P2_5;
__sbit __at(0xA6) P2_6;
__sbit __at(0xA7) P2_7;

__sfr __at(0x95) P2M1;
__sfr __at(0x96) P2M0;

#define P2PU (*((volatile uint8_t *)0xFE12))

// P3
__sfr  __at(0xB0) P3;
__sbit __at(0xB0) P3_0;
__sbit __at(0xB1) P3_1;
__sbit __at(0xB2) P3_2;
__sbit __at(0xB3) P3_3;
__sbit __at(0xB4) P3_4;
__sbit __at(0xB5) P3_5;
__sbit __at(0xB6) P3_6;
__sbit __at(0xB7) P3_7;

__sfr __at(0xB1) P3M1;
__sfr __at(0xB2) P3M0;

#define P3PU (*((volatile uint8_t *)0xFE13))

// P4
__sfr  __at(0xC0) P4;
__sbit __at(0xC0) P4_0;
__sbit __at(0xC1) P4_1;
__sbit __at(0xC2) P4_2;
__sbit __at(0xC3) P4_3;
__sbit __at(0xC4) P4_4;
__sbit __at(0xC5) P4_5;
__sbit __at(0xC6) P4_6;
__sbit __at(0xC7) P4_7;

__sfr __at(0xB3) P4M1;
__sfr __at(0xB4) P4M0;

#define P4PU (*((volatile uint8_t *)0xFE14))

// P5
__sfr  __at(0xC8) P5;
__sbit __at(0xC8) P5_0;
__sbit __at(0xC9) P5_1;
__sbit __at(0xCA) P5_2;
__sbit __at(0xCB) P5_3;
__sbit __at(0xCC) P5_4;
__sbit __at(0xCD) P5_5;
__sbit __at(0xCE) P5_6;
__sbit __at(0xCF) P5_7;

__sfr __at(0xC9) P5M1;
__sfr __at(0xCA) P5M0;

#define P5PU (*((volatile uint8_t *)0xFE15))

// P6
__sfr  __at(0xE8) P6;
__sbit __at(0xE8) P6_0;
__sbit __at(0xE9) P6_1;
__sbit __at(0xEA) P6_2;
__sbit __at(0xEB) P6_3;
__sbit __at(0xEC) P6_4;
__sbit __at(0xED) P6_5;
__sbit __at(0xEE) P6_6;
__sbit __at(0xEF) P6_7;

__sfr __at(0xCB) P6M1;
__sfr __at(0xCC) P6M0;

#define P6PU (*((volatile uint8_t *)0xFE16))

// P7
__sfr  __at(0xF8) P7;
__sbit __at(0xF8) P7_0;
__sbit __at(0xF9) P7_1;
__sbit __at(0xFA) P7_2;
__sbit __at(0xFB) P7_3;
__sbit __at(0xFC) P7_4;
__sbit __at(0xFD) P7_5;
__sbit __at(0xFE) P7_6;
__sbit __at(0xFF) P7_7;

__sfr __at(0xE1) P7M1;
__sfr __at(0xE2) P7M0;

#define P7PU (*((volatile uint8_t *)0xFE17))

// Serial
__sfr __at(0x98) SCON;
__sfr __at(0x99) SBUF;
__sfr __at(0x87) PCON;

// Timer
__sfr  __at(0x88) TCON;
__sbit __at(0x88) IT0;
__sbit __at(0x89) IE0;
__sbit __at(0x8A) IT1;
__sbit __at(0x8B) IE1;
__sbit __at(0x8C) TR0;
__sbit __at(0x8D) TF0;
__sbit __at(0x8E) TR1;
__sbit __at(0x8F) TF1;

__sfr __at(0x89) TMOD;
__sfr __at(0x8A) TL0;
__sfr __at(0x8B) TL1;
__sfr __at(0x8C) TH0;
__sfr __at(0x8D) TH1;
__sfr __at(0x8E) AUXR;
__sfr __at(0x8F) INTCLKO;
__sfr __at(0xAA) WKTCL;
__sfr __at(0xAB) WKTCH;
__sfr __at(0xD1) T4T3M;
__sfr __at(0xD2) T4H;
__sfr __at(0xD3) T4L;
__sfr __at(0xD4) T3H;
__sfr __at(0xD5) T3L;
__sfr __at(0xD6) T2H;
__sfr __at(0xD7) T2L;
#define TM2PS (*((volatile uint8_t *)0xFEA2))
#define TM3PS (*((volatile uint8_t *)0xFEA3))
#define TM4PS (*((volatile uint8_t *)0xFEA4))

// Interrupt
__sfr  __at(0xA8) IE;
__sbit __at(0xA8) EX0;
__sbit __at(0xA9) ET0;
__sbit __at(0xAA) EX1;
__sbit __at(0xAB) ET1;
__sbit __at(0xAC) ES;
__sbit __at(0xAD) EADC;
__sbit __at(0xAE) ELVD;
__sbit __at(0xAF) EA;

__sfr  __at(0xAF) IE2;
__sfr  __at(0x8F) INTCLKO;
__sfr  __at(0xB8) IP;
__sbit __at(0xB8) PX0;
__sbit __at(0xB9) PT0;
__sbit __at(0xBA) PX1;
__sbit __at(0xBB) PT1;
__sbit __at(0xBC) PS;
__sbit __at(0xBD) PADC;
__sbit __at(0xBE) PLVD;

__sfr __at(0xB7) IPH;
__sfr __at(0xB5) IP2;
__sfr __at(0xB6) IP2H;
__sfr __at(0xDF) IP3;
__sfr __at(0xEE) IP3H;

// EEPROM
#define EEPROM_SIZE      4096
#define EEPROM_PAGE_SIZE 512

__sfr __at(0xC2) IAP_DATA;
__sfr __at(0xC3) IAP_ADDRH;
__sfr __at(0xC4) IAP_ADDRL;
__sfr __at(0xC5) IAP_CMD;
__sfr __at(0xC6) IAP_TRIG;
__sfr __at(0xC7) IAP_CONTR;
__sfr __at(0xF5) IAP_TPS;

// RST
__sfr __at(0xFF) RST_CFG;

// Math.
#define MD3 (*((volatile uint8_t *)0xFCF0))
#define MD2 (*((volatile uint8_t *)0xFCF1))
#define MD1 (*((volatile uint8_t *)0xFCF2))
#define MD0 (*((volatile uint8_t *)0xFCF3))

#define MD5 (*((volatile uint8_t *)0xFCF4))
#define MD4 (*((volatile uint8_t *)0xFCF5))

#define ARCON (*((volatile uint8_t *)0xFCF6))

#define OPCON (*((volatile uint8_t *)0xFCF7))

/**
 * @brief       Initialize platform.
 */
extern void initPlatform(void);
