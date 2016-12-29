#ifndef __REGS_H__
#define __REGS_H__

typedef union
{
	uint8_t bytes[64];
	uint16_t words[32];
} Regs;

#define AL 0
#define AH 1
#define BL 2
#define BH 3
#define CL 4
#define CH 5
#define DL 6
#define DH 7

#define AX 0
#define BX 1
#define CX 2
#define DX 3
#define SS 4
#define DS 5
#define ES 6
#define CS 7
#define SP 8
#define SI 9
#define DI 10
#define BP 11
#define FLAGS 12

#define FLAGS_RES4 0x8000
#define FLAGS_NT 0x4000
#define FLAGS_IOPL1 0x2000
#define FLAGS_IOPL0 0x1000
#define FLAGS_OF 0x0800
#define FLAGS_DF 0x0400
#define FLAGS_IF 0x0200
#define FLAGS_TF 0x0100
#define FLAGS_SF 0x0080
#define FLAGS_ZF 0x0040
#define FLAGS_RES3 0x0020
#define FLAGS_AF 0x0010
#define FLAGS_RES2 0x0008
#define FLAGS_PF 0x0004
#define FLAGS_RES1 0x0002
#define FLAGS_CF 0x0001

#endif
