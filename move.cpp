#include "move.h"

Move::Move(QVector<int> arguments, QObject *parent) : Operation(arguments, parent)
{
    runVar.resize(3);
}

void Move::run(byte olddvg0, byte olddvg1, URTKPort* port)
{
    if ((argList.size() >= 3) && (argList[0] >= 0) && (argList[0] <= 5) && (argList[1] >= -1) && (argList[1] <= 1) && (argList[2] >= 0) && (argList[2] <= 500))
    {
        int dvgbyte[6];
        for (int i = 0; i < 6; i++)
        {
            dvgbyte[i] = 3;
        }
        
        dvgbyte[argList[0]] = argList[1];
        
        port->SetDvgRegs(dvg0 = port->CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], olddvg0), dvg1 = port->CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, olddvg1));
        
        byte s0, s1, s2;
        port->GetSnsRegs(&s0, &s1, &s2);
        
        int sensors[6];
        
        sensors[0] = port->TestBit(&s0, 2);
        sensors[1] = port->TestBit(&s0, 5);
        sensors[2] = port->TestBit(&s1, 2);
        sensors[3] = port->TestBit(&s1, 5);
        sensors[4] = port->TestBit(&s2, 2);
        sensors[5] = port->TestBit(&s2, 5);
        
        runVar[0] = 30;
        runVar[1] = sensors[argList[0]];
        runVar[2] = argList[1];
        
        isStarted = 1;
        
    }
    else
    {
        isStarted = 1;
        isCompleted = 1;
    }
}

void Move::checkCompletion(byte olddvg0, byte olddvg1, URTKPort* port)
{
    byte s0, s1, s2;
    port->GetSnsRegs(&s0, &s1, &s2);

    int sensors[6];
    int m[6][2];

    m[0][0] = port->TestBit(&s0, 0);
    m[0][1] = port->TestBit(&s0, 1);
    m[1][0] = port->TestBit(&s0, 3);
    m[1][1] = port->TestBit(&s0, 4);
    m[2][0] = port->TestBit(&s1, 0);
    m[2][1] = port->TestBit(&s1, 1);
    m[3][0] = port->TestBit(&s1, 3);
    m[3][1] = port->TestBit(&s1, 4);
    m[4][0] = port->TestBit(&s2, 0);
    m[4][1] = port->TestBit(&s2, 1);
    m[5][0] = port->TestBit(&s2, 3);
    m[5][1] = port->TestBit(&s2, 4);

    sensors[0] = port->TestBit(&s0, 2);
    sensors[1] = port->TestBit(&s0, 5);
    sensors[2] = port->TestBit(&s1, 2);
    sensors[3] = port->TestBit(&s1, 5);
    sensors[4] = port->TestBit(&s2, 2);
    sensors[5] = port->TestBit(&s2, 5);

    if (runVar[0] > 0)
    {
        runVar[0]--;
    }
    else
    {

        if ((m[argList[0]][0] == 1) || (m[argList[0]][1] == 1))
        {
            runVar[2] = 0;
        }
    }

    if ((runVar[2] > 0) && (runVar[1] != sensors[argList[0]]))
    {
        runVar[2]--;
        runVar[1] = sensors[argList[0]];
    }
    else if (runVar[2] <= 0)
    {
        int dvgbyte[6];
        for (int i = 0; i < 6; i++)
        {
            dvgbyte[i] = 3;
        }

        dvgbyte[argList[0]] = 0;

        port->SetDvgRegs(dvg0 = port->CountDvg0(dvgbyte[0], dvgbyte[1], dvgbyte[2], dvgbyte[3], olddvg0), dvg1 = port->CountDvg1(dvgbyte[4], dvgbyte[5], 3, 3, 3, 3, olddvg1));

        isCompleted = 1;
    }
}
