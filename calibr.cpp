#include "calibr.h"

Calibr::Calibr(QVector<int> arguments, QObject *parent) : Operation(arguments, parent)
{

}

void Calibr::run(byte& dvg0, byte& dvg1, URTKPort* port)
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
        port->SetDvgRegs(dvg0 = port->CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], dvg0), dvg1 = port->CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, dvg1));

        // Мы начали выполнение команды
        isStarted = 1;
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Calibr::checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port)
{
    // Проверим концевые датчики
    byte s0, s1, s2;
    // Считываем байт состояния датчиков
    port->GetSnsRegs(&s0, &s1, &s2);
    int m[6];

    // Каждый бит - датчик
    m[0] = port->TestBit(&s0, 0);
    m[1] = port->TestBit(&s0, 3);
    m[2] = port->TestBit(&s1, 0);
    m[3] = port->TestBit(&s1, 3);
    m[4] = port->TestBit(&s2, 0);
    m[5] = port->TestBit(&s2, 3);

    // Если нужный нам датчик показывает, что степень откалибровалась
    if (m[argList[0]])
    {
        int dvgbyte[6];
        for (int i = 0; i < 6; i++)
        {
            dvgbyte[i] = 3;
        }

        // то мы прекращаем движение
        dvgbyte[argList[1]] = 0;

        port->SetDvgRegs(dvg0 = port->CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], dvg0), dvg1 = port->CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, dvg1));

        // Операция калибровки выполнена
        isCompleted = 1;
     }

}
