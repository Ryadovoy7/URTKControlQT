#include "calibr.h"

Calibr::Calibr(QVector<int> arguments, QObject *parent) : Operation(arguments, parent)
{

}

void Calibr::run(byte olddvg0, byte olddvg1)
{
    // Проверим правильность предоставленных аргументов
    if ((argList.size() >= 1) && (argList[0] >= 0) && (argList[0] <= 5))
    {
        // Байт, который мы отправим СУ
        int dvgbyte[6];
        for (int i = 0; i < 6; i++)
        {
            // Для всех двигателей указываем продолжать то, что они делают
            dvgbyte[i] = 3;
        }

        // Кроме двигателя, переданного аргументом, он поедет к началу координат
        dvgbyte[argList[0]] = -1;

        // Отправим байт
        SetDvgRegs(dvg0 = CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], olddvg0), dvg1 = CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, olddvg1));

        // Мы начали выполнение команды
        isStarted = 1;
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Calibr::checkCompletion(byte olddvg0, byte olddvg1)
{
    // Проверим концевые датчики
    byte s0, s1, s2;
    // Считываем байт состояния датчиков
    GetSnsRegs(&s0, &s1, &s2);
    int m[6];

    // Каждый бит - датчик
    m[0] = TestBit(&s0, 0);
    m[1] = TestBit(&s0, 3);
    m[2] = TestBit(&s1, 0);
    m[3] = TestBit(&s1, 3);
    m[4] = TestBit(&s2, 0);
    m[5] = TestBit(&s2, 3);

    // Если нужный нам датчик показывает, что степень откалибровалась
    if (m[argList[0]])
    {
        int dvgbyte[6];
        for (int i = 0; i < 6; i++)
        {
            dvgbyte[i] = 3;
        }

        // то мы прекращаем движение
        dvgbyte[arg[1]] = 0;

        SetDvgRegs(dvg0 = CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], olddvg0), dvg1 = CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, olddvg1));

        // Операция калибровки выполнена
        isComplete = 1;
     }

}
