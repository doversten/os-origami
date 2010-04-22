#ifndef __MIPS4KC__
#define __MIPS4KC__

#include "types.h"

/* status register */
typedef union {
  uint32_t reg;
  struct {
    uint32_t ie   : 1; /* Bit 0:     Interrupt Enable */
    uint32_t exl  : 1; /* Bit 1:     Exception Level */
    uint32_t erl  : 1; /* Bit 2:     Error Level */
    uint32_t pad0 : 1; /* Bit 3:     Reserved */
    uint32_t um   : 1; /* Bit 4:     User Mode */
    uint32_t pad1 : 3; /* Bit 5-7:   Reserved */
    uint32_t im   : 8; /* Bit 8-15:  Interrupt Mask */
    uint32_t pad2 : 3; /* Bit 16-18: Reserved */
    uint32_t nmi  : 1; /* Bit 19:    Indicates a Non-Maskable Interrupt */
    uint32_t sr   : 1; /* Bit 20:    Soft Reset */
    uint32_t ts   : 1; /* Bit 21:    TLB Shutdown */
    uint32_t bev  : 1; /* Bit 22:    Bootstrap Exception Vector */
    uint32_t pad3 : 2; /* Bit 23-24: Reserved */
    uint32_t re   : 1; /* Bit 25:    Reverse Endian */
    uint32_t pad4 : 1; /* Bit 26:    Reserved */
    uint32_t rp   : 1; /* Bit 27:    Reduced Power mode */
    uint32_t cu0  : 1; /* Bit 28:    Coprocessor 0 Usable */
    uint32_t cu1  : 1; /* Bit 29:    Coprocessor 1 Usable */
    uint32_t cu2  : 1; /* Bit 30:    Coprocessor 2 Usable */
    uint32_t cu3  : 1; /* Bit 31:    Coprocessor 3 Usable */
  } field;
} status_reg_t;

/* cause register */
typedef union {
  uint32_t reg;
  struct {
    uint32_t pad0 : 2; /* Bit 0-1:   Reserved */
    uint32_t exc  : 5; /* Bit 2-6:   Exception code */
    uint32_t pad1 : 1; /* Bit 7:     Reserved */
    uint32_t ip   : 8; /* Bit 8-15:  Interrupt pending */
    uint32_t pad2 : 6; /* Bit 16-21: Reserved */
    uint32_t wp   : 1; /* Bit 22:    Watch Prevent */
    uint32_t iv   : 1; /* Bit 23:    Interrupt Vector */
    uint32_t pad3 : 4; /* Bit 24-27: Reserved */
    uint32_t ce   : 2; /* Bit 28-29: Coprocessor exception */
    uint32_t pad4 : 1; /* Bit 30:    Reserved */
    uint32_t bd   : 1; /* Bit 31:    Branch Delay */
  } field;
} cause_reg_t;

/* Exception codes for MIPS4KC */
#define EXC4_Int    0  /* Interrupt */
#define EXC4_Mod    1  /* TLB modification exception */
#define EXC4_TLBL   2  /* TLB load/fetch exception */
#define EXC4_TLBS   3  /* TLB store exception */
#define EXC4_AdEL   4  /* Address error (load/fetch) */
#define EXC4_AdES   5  /* Address error (store) */
#define EXC4_IBE    6  /* Bus error (fetch) */
#define EXC4_DBE    7  /* Bus error (data load/store) */
#define EXC4_Sys    8  /* syscall */
#define EXC4_Bp     9  /* Breakpoint exception */
#define EXC4_RI     10 /* Reserved instruction exception */
#define EXC4_CpU    11 /* Coprocessor unusable exception */
#define EXC4_Ov     12 /* Integer overflow exception */
#define EXC4_Tr     13 /* Trap exception */
#define EXC4_WATCH  23 /* Reference to WatchHi/WatchLo address */
#define EXC4_MCheck 24 /* Machine check */

#endif
