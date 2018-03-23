#include "operation.h"

Operation::Operation(QVector<int> arguments, QObject *parent) : QObject(parent)
{
    isCompleted = false;
    isStarted = false;
    argList = arguments;
}

void Operation::run(byte& dvg0, byte& dvg1, URTKPort* port)
{
    //blank, superclass
}

void Operation::checkCompletion(byte& dvg0, byte& dvg1, URTKPort* port)
{
    //blank, superclass
}

void Operation::resetOperation()
{
    //blank, superclass
}
