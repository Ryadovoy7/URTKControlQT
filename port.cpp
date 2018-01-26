//---------------------------------------------------------------------------
#include "port.h"

URTKPort::URTKPort()
{
	LptData = 0xE800;
	LptStatus = 0xE801;
	LptConfig = 0xE802;
}

URTKPort::URTKPort(std::string pathToSettings)
{

}

URTKPort::~URTKPort()
{
}

void URTKPort::LoadSettings(std::string pathToSettings)
{
	//load from file "settings.txt"
}

//////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: TestBit()
// Desc: Метод возвращает значение бита BitNum в байте DataByte
// ---------------------------------------------------------------------------
byte URTKPort::TestBit ( byte * DataByte,  byte BitNum)
{
   return ((*DataByte >> BitNum) & 0x01);
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: ClrBit()
// Desc: Метод устанавливает значение бита BitNum в байте DataByte в 0
// ---------------------------------------------------------------------------
void URTKPort::ClrBit ( byte * DataByte,  byte BitNum)
{
   *DataByte &= (~(1 << BitNum));
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: SetBit()
// Desc: Метод устанавливает значение бита BitNum в байте DataByte в 1
// ---------------------------------------------------------------------------
void URTKPort::SetBit (byte * DataByte,  byte BitNum)
{
   *DataByte |= (1 << BitNum);
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: delay()
// Desc: Задержка выполнения на timedelay мс
// ---------------------------------------------------------------------------
void URTKPort::delay ( double timedelay)
{
   if(timedelay == 0) return;

   LARGE_INTEGER a,b,f;

   double ElapsedTime;

   QueryPerformanceFrequency(&f);
   QueryPerformanceCounter(&a);

   while (true)
   {

    QueryPerformanceCounter(&b);

    ElapsedTime = (double)(b.QuadPart - a.QuadPart)/f.QuadPart;

    if (ElapsedTime >= timedelay) return;
   }
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: WriteReg()
// Desc: Метод записывает байт в регистр СУ
// ---------------------------------------------------------------------------
void URTKPort::WriteReg (byte reg, byte value)
{

   byte ConfigByte = cPassiveState;

   Out32(LptConfig, ConfigByte);

   switch (reg)
   {
    case PA: SetBit(&ConfigByte, A0); SetBit(&ConfigByte, A1); break;
    case PB: SetBit(&ConfigByte, A0); break;
    case PC: SetBit(&ConfigByte, A1); break;
    case RC: break;
   }
   ClrBit(&ConfigByte, WR);
   ClrBit(&ConfigByte, DIR);

   Out32(LptData, value);
   delay(0.000147);

   Out32(LptConfig, ConfigByte);
   delay(0.000441);

   ConfigByte = cPassiveState;

   Out32(LptConfig, ConfigByte);
   delay(0.000441);


}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: ReadReg()
// Desc: Метод читает байт из регистра СУ
// ---------------------------------------------------------------------------
byte URTKPort::ReadReg (byte reg)
{
   DWORD a;

   byte ConfigByte = cPassiveState;

   Out32 (LptConfig, ConfigByte);

   Out32 (LptData, 0xFF);

   switch (reg)
   {
    case PA: SetBit(&ConfigByte, A0); SetBit(&ConfigByte, A1); break;
    case PB: SetBit(&ConfigByte, A0); break;
    case PC: SetBit(&ConfigByte, A1); break;
    case RC: break;
   }

   SetBit(&ConfigByte, RD);
   SetBit(&ConfigByte, DIR);

   Out32(LptConfig, ConfigByte);
   delay(0.000441);

   a = Inp32 (LptData);

   ConfigByte = cPassiveState;

   delay(0.000441);

   Out32(LptConfig, ConfigByte);


   return a;
}
///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: CheckOnline()
// Desc: Метод проверяет включена ли СУ.
//       В случае, если СУ включена метод возвратит 1.
// ---------------------------------------------------------------------------
int URTKPort::CheckOnline(void)
{
   //delay(0.000147)

   if (ReadReg (RC) == cOnline)  return 1;

   else  return 0;

}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name:    CountDvg0()
// Desc:	Формирование значения регистра DVG0 СУ УРТК, управляющего
//			двигателями первых четырех степеней, по требуемым
//			направлениям движения каждой из этих степеней.
// Input:	x, y, z, w - задают требуемое направление движения
//			соответствующих степеней УРТК: +1 соответствует направлению
//			движения от начального концевого датчика к конечному,
//			-1 - направлению движения от конечного к начальному,
//			0 - остановке степени, любое другое значение - соответствует
//			сохранению прежнего направления движения.
//			dvg0old - предыдущее значение, загруженное в соответствующий
//			регистр СУ: требуется при необходимости не изменять
//			движение степени.
// Output:	сформированное значение, которое может быть
//			использовано в функции SetDvgRegs()
// ---------------------------------------------------------------------------
byte URTKPort::CountDvg0(int x, int y, int z, int w, byte dvg0old)
{
   byte res = 0;
   switch (x) {
    case -1:	SetBit(&res, aXmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aXpBit); break;
    default:	if (TestBit(&dvg0old, aXmBit)) SetBit(&res, aXmBit);
    if (TestBit(&dvg0old, aXpBit)) SetBit(&res, aXpBit);
   }
   switch (y) {
    case -1:	SetBit(&res, aYmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aYpBit); break;
    default:	if (TestBit(&dvg0old, aYmBit)) SetBit(&res, aYmBit);
    if (TestBit(&dvg0old, aYpBit)) SetBit(&res, aYpBit);
   }
   switch (z) {
    case -1:	SetBit(&res, aZmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aZpBit); break;
    default:	if (TestBit(&dvg0old, aZmBit)) SetBit(&res, aZmBit);
    if (TestBit(&dvg0old, aZpBit)) SetBit(&res, aZpBit);
   }
   switch (w) {
    case -1:	SetBit(&res, aWmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aWpBit); break;
    default:	if (TestBit(&dvg0old, aWmBit)) SetBit(&res, aWmBit);
    if (TestBit(&dvg0old, aWpBit)) SetBit(&res, aWpBit);
   }
   return res;
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name:    CountDvg1()
// Desc:	Формирование значения регистра DVG0 СУ УРТК, управляющего
//			двигателями первых четырех степеней, по требуемым
//			направлениям движения каждой из этих степеней.
// Input:	f, r - задают требуемое направление движения
//			соответствующих степеней УРТК: +1 соответствует направлению
//			движения от начального концевого датчика к конечному,
//			-1 - направлению движения от конечного к начальному,
//			0 - остановке степени, любое другое значение - соответствует
//			сохранению прежнего движения.
//			d0, d1, d2, ew - задают режим работы соответствующих
//			однополярных двигателей УРТК: 1 - двигатель включен,
//			0 - двигатель выключен, любое другое значение - сохранение
//			предыдущего состояния.
//			dvg1old - предыдущее значение, загруженное в соответствующий
//			регистр УРТК: требуется при необходимости не изменять
//			движение степени.
// Output:	сформированное значение, которое может быть
//			использовано в функции SetDvgRegs().
// ---------------------------------------------------------------------------
  byte URTKPort::CountDvg1(int f, int r, int d0, int d1, int d2, int ew, byte dvg1old)
{
   byte res = 0;
   switch (f) {
    case -1:	SetBit(&res, aFmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aFpBit); break;
    default:	if (TestBit(&dvg1old, aFmBit)) SetBit(&res, aFmBit);
    if (TestBit(&dvg1old, aFpBit)) SetBit(&res, aFpBit);
   }
   switch (r) {
    case -1:	SetBit(&res, aRmBit); break;
    case 0:	break;
    case 1:	SetBit(&res, aRpBit); break;
    default:	if (TestBit(&dvg1old, aRmBit)) SetBit(&res, aRmBit);
    if (TestBit(&dvg1old, aRpBit)) SetBit(&res, aRpBit);
   }
   switch (d0) {
    case 0:	break;
    case 1:	SetBit(&res, aD0Bit); break;
    default:	if (TestBit(&dvg1old, aD0Bit)) SetBit(&res, aD0Bit);
   }
   switch (d1) {
    case 0:	break;
    case 1:	SetBit(&res, aD1Bit); break;
    default:	if (TestBit(&dvg1old, aD1Bit)) SetBit(&res, aD1Bit);
   }
   switch (d2) {
    case 0:	break;
    case 1:	SetBit(&res, aD2Bit); break;
    default:	if (TestBit(&dvg1old, aD2Bit)) SetBit(&res, aD2Bit);
   }
   switch (ew) {
    case 0:	break;
    case 1:	SetBit(&res, aEWBit); break;
    default:	if (TestBit(&dvg1old, aEWBit)) SetBit(&res, aEWBit);
   }
   return res;
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name:   SetDvgRegs()
// Desc:   Установка регистров СУ УРТК, управляющих
//		   двигателями
// Input:  dvg0, dvg1 - содержимое этих переменных будет
//		   записано в регистры двигателей.
// ---------------------------------------------------------------------------
int URTKPort::SetDvgRegs(byte dvg0, byte dvg1)
{
    WriteReg(RC, cSetDvgRegs);

   // принудительное включение обмотки возбуждения
   if ((dvg0 != 0) || ((dvg1 & 0x0F) != 0)) dvg1 |= 0x80;

   WriteReg(PA, dvg1);
   delay(0.000147);
   WriteReg(PA, dvg0);

   return 1;
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: SetLedRegs()
// Desc: Метод записывает байт в регистр, управляющий состоянием
//		 восьми светодиодов
// Example:
//       led = 0x8fh (1000 1111) загорятся 1-й, 5-й, 6-й, 7-й, 8-й;
//       led = 0x04h (0100 0000) загорится 2-й;
//       led = 0x00h (0000 0000) не горит ни один;
// ---------------------------------------------------------------------------
 int URTKPort::SetLedRegs(byte led)
{
   WriteReg(RC, cSetLedRegs);
   WriteReg(PA, led);

   return 1;
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name:  GetSnsRegs()
// Desc: Метод предназначен для чтения состояния
//       датчиков ММ, подключенных к системе управления.
//       После выполнения метода байты, переданные в параметрах будут содержать
//       значения регистров
// ---------------------------------------------------------------------------
int URTKPort::GetSnsRegs ( byte * sns0,  byte * sns1,  byte * sns2)
{
   WriteReg(RC, cGetSnsRegs);

   delay(0.000147);

   *sns0 = ReadReg(PA) ^ 0xFF;

   delay(0.000147);

   *sns1 = ReadReg(PA) ^ 0xFF;

   delay(0.000147);


   *sns2 = ReadReg(PA) ^ 0xFF;

   return 1;
}

///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: WriteReg()
// Desc: Метод предназначен для чтения из СУ значений двух регистров клавиатуры
// ---------------------------------------------------------------------------
int URTKPort::GetKbdRegs (byte * kbd0, byte * kbd1)
{
  // if(!prog)return 0;
   WriteReg(RC, cGetKbdRegs);
   delay(0.000147);
   *kbd0 = ReadReg(PA) ^ 0xFF;
   delay(0.000147);
   *kbd1 = ReadReg(PA) ^ 0xFF ;
   return 1;
}


///////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// Name: ClrBit()
// Desc: Применение операции xor над битом BitNum в байте DataByte
// Example:
//			0 xor 0 = 0;
//          0 xor 1 = 1;
//          1 xor 0 = 1;
//          1 xor 1 = 0;
// ---------------------------------------------------------------------------
void URTKPort::XorBit ( byte * DataByte,  byte BitNum)
{
   *DataByte ^= (1 << BitNum);
}



byte URTKPort::ReadR()
{
   DWORD a;
   delay (0.000147);

   a = Inp32(LptStatus);

   return a;
}
