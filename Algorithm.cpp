#include "Algorithm.h"
#include "ui_scriptwindow.h"


Algorithm::Algorithm(QObject *parent) : QObject(parent)
{
    opVec.clear();
    opVec.squeeze();
    opVecIterator = 0;
    olddvg0 = 0;
    olddvg1 = 0;

    // Создаем окно для выполняющегося алгоритма
    algWindow = new QWidget();
    Ui::ScriptWindow uiScript;
    uiScript.setupUi(algWindow);

}

Algorithm::~Algorithm()
{
}

void Algorithm::algInit(const QMap<QString, QString> &settings, QString algText)
{
    // Очищаем вектор операций
    clearOpVec();

    // Инициализируем LPTPort
    portInit(settings);

    // Читаем алгоритм из файла и собираем вектор операций
    readAlgorithm(algText, settings);

    // Создаем таймер
    timerID = startTimer(50);
}

void Algorithm::algEnd()
{
    // Останавливаем таймер
    killTimer(timerID);
    timerID = 0;

    // Удаляем инициализированный порт
    delete LPTPort;
    LPTPort = 0;

    // Очищаем вектор операций
    clearOpVec();

    emit algFinished();
}

void Algorithm::timerEvent(QTimerEvent *event)
{
    // Булевская переменная, отражающая выполненность блока команд
    bool blockComplete = true;
    // Пока вектор операций не закончился
    if(opVecIterator < opVec.size())
    {
        // Для каждой операции в данном блоке вектора операций
        for(Operation* op : *opVec[opVecIterator])
        {
            // В зависимости от того, началось ли выполнение
            // Данное условие поставлено для того, чтобы не перегружать запросами СУ
            if(!op->isStarted)
            {
                // Запускаем выполнение
                op->run(olddvg0, olddvg1, LPTPort);
            }
            else
            {
                // Проверяем законченность
                op->checkCompletion(olddvg0, olddvg1, LPTPort);
            }
            // Выполнен ли блок?
            blockComplete *= op->isCompleted;
        }
        // Если блок команд выполнен, переходим к следующему
        if(blockComplete)
        {
            opVecIterator++;
        }
    }
    else
    {
        algEnd();
        qDebug() << "algorithm completed!";
    }
}


void Algorithm::readAlgorithm(QString algText, const QMap<QString, QString> &settings)
{
    QMetaObject algMeta = this->staticMetaObject;
    QMetaEnum opEnumMeta = algMeta.enumerator(algMeta.indexOfEnumerator("opEnum"));

    // Делим полученный текст по строчкам
    QStringList algTextList = algText.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    // Теперь для каждой строчки
    QStringListIterator algIterator(algTextList);
    // Переменная для удержания группы операций (выполняющихся одновременно)
    bool holdOpGroup = false;

    // Для всех строк выполняем
    while(algIterator.hasNext())
    {
        qDebug() << "alg has next!";
        // Берем следующую строку
        QString bufString = algIterator.next();
        // Регулярное выражение, по которому мы найдем в строке имя операции
        QRegExp opRegExp("[a-zA-Z]{1,20}");
        // Регулярное выражение для аргументов операции
        QRegExp argRegExp("[(]([0-9]+[,])*[0-9]+[)]");

        // Находим их в строке
        int posOp = opRegExp.indexIn(bufString);
        int posArg = argRegExp.indexIn(bufString);

        // Если присутствует регулярное выражение, которое мы задали для имени операции, выполняем следующее
        // Иначе, пропускаем строку
        if (posOp > -1)
        {
            qDebug() << "found regexp!";
            // Записываем в отдельную строку имя операции
            QString opName = opRegExp.cap(0);
            qDebug() << opName;
            // Вектор целых чисел, который мы передадим как аргументы созданной операции
            // Если аргументов нет, он останется пустым
            QVector<int> argVec;
            if (posArg > -1)
            {
                // Находим подстроку с аргументами
                QString argString = argRegExp.cap(0);
                // Удаляем из нее скобочки спереди и сзади
                argString.remove(0,1);
                argString.chop(1);
                qDebug() << "argstring: " << argString;

                // И разделяем оставшуюся строку на числа выбранным делителем
                QStringList argStringList = argString.split(",", QString::SkipEmptyParts);

                // Переводим получившиеся строки в целые числа, записываем их в вектор аргументов
                for (QString s : argStringList)
                {
                    argVec.append(s.toInt()); // вариант получше?
                    qDebug() << "argument: " << s.toInt();
                }
            }

            // В зависимости от имени операции создаем соответствующий подкласс и добавляем к вектору
            switch(opEnumMeta.keysToValue(opName.toUpper().toLatin1()))
            {
            case BEGIN:
                holdOpGroup = true;
                break;
            case END:
                holdOpGroup = false;
                break;
            case CALIBR:
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        opVec[opVec.size()-1]->append(new Calibr(argVec, this));
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        opVec[opVec.size()-1]->append(new Calibr(argVec, this));
                    }
                }
                else
                {
                    opVec.append(new QVector<Operation*>);
                    opVec[opVec.size()-1]->append(new Calibr(argVec, this));
                }
                break;
            case MOVE:
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        opVec[opVec.size()-1]->append(new Move(argVec, this));
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        opVec[opVec.size()-1]->append(new Move(argVec, this));
                    }
                }
                else
                {
                    opVec.append(new QVector<Operation*>);
                    opVec[opVec.size()-1]->append(new Move(argVec, this));
                }
                break;
            case GRAB:
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        opVec[opVec.size()-1]->append(new Grab(argVec, this));
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        opVec[opVec.size()-1]->append(new Grab(argVec, this));
                    }
                }
                else
                {
                    opVec.append(new QVector<Operation*>);
                    opVec[opVec.size()-1]->append(new Grab(argVec, this));
                }
                break;
            case FLAG:
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        Flag* bufOp = new Flag(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }

                        opVec[opVec.size()-1]->append(bufOp);
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        Flag* bufOp = new Flag(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }
                        opVec[opVec.size()-1]->append(bufOp);
                    }
                }
                else
                {
                    {
                        opVec.append(new QVector<Operation*>);
                        Flag* bufOp = new Flag(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }
                        opVec[opVec.size()-1]->append(bufOp);
                    }
                }
                break;
            case CHECK:
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        Check* bufOp = new Check(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }
                        opVec[opVec.size()-1]->append(bufOp);
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        Check* bufOp = new Check(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }
                        opVec[opVec.size()-1]->append(bufOp);
                    }
                }
                else
                {
                    {
                        opVec.append(new QVector<Operation*>);
                        Check* bufOp = new Check(argVec, this);
                        if(settings.contains("ServerIp") && settings.contains("ServerPort"))
                        {
                            bufOp->setServer(settings["ServerIp"], settings["ServerPort"]);
                        }
                        opVec[opVec.size()-1]->append(bufOp);
                    }
                }
                break;
            case TEST:
                qDebug() << "hey, i'm a test op!";
                if(holdOpGroup)
                {
                    if (opVec.size())
                    {
                        opVec[opVec.size()-1]->append(new Test(argVec, this));
                    }
                    else
                    {
                        opVec.append(new QVector<Operation*>);
                        opVec[opVec.size()-1]->append(new Test(argVec, this));
                    }
                }
                else
                {
                    opVec.append(new QVector<Operation*>);
                    opVec[opVec.size()-1]->append(new Test(argVec, this));
                }
                break;
            default:
                qDebug() << "operation name not recognized!";
                break;
            }
        }
    }

}

void Algorithm::portInit(const QMap<QString, QString> &settings)
{
    bool ok;

    if (settings.contains("LptData") && settings.contains("LptStatus") && settings.contains("LptConfig"))
    {
        byte data = (byte)settings["LptData"].toUInt(&ok,0);
        qDebug() << "LptData: " << data;
        byte status = (byte)settings["LptStatus"].toUInt(&ok,0);
        qDebug() << "LptStatus: " << status;
        byte config = (byte)settings["LptConfig"].toUInt(&ok,0);
        qDebug() << "LptConfig: " << config;

        LPTPort = new URTKPort(data, status, config, this);
        qDebug() << "port loaded from settings!";
    }
    else
    {
        LPTPort = new URTKPort(this);
        qDebug() << "port loaded by default";
    }
}

void Algorithm::clearOpVec()
{
    // Сначала удаляем операции из векторов ступеней
    for (QVector<Operation*>* i : opVec)
    {
        for (Operation* j : *i)
        {
            delete j;
        }

        i->clear();
        i->squeeze();

        delete i;
    }

    // Затем удаляем весь вектор алгоритма
    opVec.clear();
    opVec.squeeze();

    opVecIterator = 0;
    olddvg0 = 0;
    olddvg1 = 0;
}
