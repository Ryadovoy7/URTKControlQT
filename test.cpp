#include "test.h"

Test::Test(QVector<int> arguments, QObject *parent) : Operation(arguments, parent)
{
    runVar.resize(3);
}

void Test::run(byte &dvg0, byte &dvg1, URTKPort *port)
{
    qDebug() << "will now run for " << argList[0] << " ms";
    runVar[0] = startTimer(argList[0]);
    isStarted = 1;
}

void Test::checkCompletion(byte &dvg0, byte &dvg1, URTKPort *port)
{
    if(isCompleted)
    {
        killTimer(runVar[0]);
        qDebug() << "now completed";
    }
}

void Test::timerEvent(QTimerEvent *event)
{
    isCompleted = 1;
}

void Test::resetOperation()
{
    isStarted = 0; isCompleted = 0;
}
