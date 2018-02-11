#include "operation.h"

Operation::Operation(QVector<int> arguments, QObject *parent) : QObject(parent)
{
    isCompleted = false;
    isStarted = false;
    argList = arguments;
}

void Operation::run(byte olddvg0, byte olddvg1, URTKPort* port)
{
    //blank, superclass
}

void Operation::checkCompletion(byte olddvg0, byte olddvg1, URTKPort* port)
{
    //blank, superclass
}
