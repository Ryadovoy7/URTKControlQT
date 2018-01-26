////---------------------------------------------------------------------------
#pragma once

// Нумерация эмулируемых регистров 8255
#define	PA		0x00
#define	PB		0x01
#define	PC		0x02
#define	RC		0x03

// LptConfig:   xx, xx, DIR, xx, A1, WR, A0, RD
#define RD		0
#define A0			1
#define WR		2
#define A1			3
#define DIR		5

// Управляющие константы протокола
#define cSetDvgRegs	0x11
#define cSetLedRegs	0x12
#define cGetSnsRegs	0x13
#define cGetKbdRegs	0x14

// Расположение битов в регистрах управления двигателями
#define aXmBit		0
#define aXpBit		1
#define aYmBit		2
#define aYpBit		3
#define aZmBit		4
#define aZpBit		5
#define aWmBit		6
#define aWpBit		7
#define aFmBit		0
#define aFpBit		1
#define aRmBit		2
#define aRpBit		3
#define aD0Bit		4
#define aD1Bit		5
#define aD2Bit		6
#define aEWBit		7

// Расположение битов в регистрах датчиков
#define aXsBit		0
#define aXeBit		1
#define aXiBit		2

#define aYsBit		3
#define aYeBit		4
#define aYiBit		5

#define aZsBit		0
#define aZeBit		1
#define aZiBit		2

#define aWsBit		3
#define aWeBit		4
#define aWiBit		5

#define aFsBit		0
#define aFeBit		1
#define aFiBit		2

#define aRsBit		3
#define aReBit		4
#define aRiBit		5

// Прочие константы
#define cNull		0x00
#define cD1Null		0x80
#define	cPassiveState	0x04
#define	cOnline		0x83
