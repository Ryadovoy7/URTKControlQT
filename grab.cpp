#include "grab.h"

Grab::Grab(QVector<int> arguments, QObject *parent) : Operation(arguments, parent)
{

}

void Grab::run(byte olddvg0, byte olddvg1)
{
    // Проверям аргументы
    if ((argList.size() >= 2) && (argList[0] >= 0) && (argList[0] <= 3) && (argList[1] >= 0) && (argList[1] <= 1))
    {
        // Формируем байт управления
        int dvgbyte[4];
        for (int i = 0; i < 4; i++)
        {
            dvgbyte[i] = 3;
        }
        // Активируем или деактивируем захват нужной степени
        dvgbyte[argList[0]] = argList[1];

        SetDvgRegs(dvg0 = CountDvg0(3, 3, 3, 3, dvg0), dvg1 = CountDvg1(3, 3, dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], dvg1));

        // Мы закончили операцию захвата, проверять нечего
        isStarted = 1;
        isCompleted = 1;
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Grab::checkCompletion(byte olddvg0, byte olddvg1)
{
    // Захват заканчивается на функции run(), поэтому здесь пусто
}
