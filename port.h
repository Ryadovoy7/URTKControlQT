
#pragma once

#include "Const.h"
#include <Windows.h>
#include <string>
#include <inpout32.h>


struct URTKPort
{

	URTKPort();
	URTKPort(std::string pathToSettings);
	~URTKPort();

	byte LptData = 0xE800;
	byte LptStatus = 0xE801;
	byte LptConfig = 0xE802;

	void LoadSettings(std::string pathToSettings);

	int SetLedRegs(byte led);
	int CheckOnline(void);
	byte CountDvg0(int x, int y, int z, int w, byte dvg0old);
	byte CountDvg1(int f, int r, int d0, int d1, int d2, int ew, byte dvg1old);
	int SetDvgRegs(byte dvg0, byte dvg1);
	byte TestBit(byte * DataByte, byte BitNum);
	int GetSnsRegs(byte * sns0, byte * sns1, byte * sns2);

private:
	void ClrBit(byte * DataByte, byte BitNum);
	void SetBit(byte * DataByte, byte BitNum);
	void delay(double timedelay);
	void WriteReg(byte reg, byte value);
	byte ReadReg(byte reg);
	int GetKbdRegs(byte * kbd0, byte * kbd1);
	void XorBit(byte * DataByte, byte BitNum);
	byte ReadR();
};







