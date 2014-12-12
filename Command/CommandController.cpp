#include "CommandController.h"
#include <QDebug>
#include <typeinfo>

CommandController::CommandController(QObject *parent)
{
    isExecute = false;
    queueMaxLen = 3;
    commandQueue.clear();
}

void CommandController::Execute()
{
    if (!isExecute)
        ExecuteNext();
}

CommandController::~CommandController()
{
    if (!commandQueue.empty())
    {
        for (int i = 0; i < commandQueue.size(); ++i)
            delete commandQueue[i];
        commandQueue.clear();
    }
}

void CommandController::AddCommand(Command *command)
{
    if (commandQueue.size() < queueMaxLen)
        commandQueue.push_back(command);
    else
        delete command;
}

void CommandController::ExecuteNext()
{
    if (!commandQueue.empty())
    {
        isExecute = true;
        commandQueue[0]->Execute();
        qDebug() << typeid(*commandQueue[0]).name();
        delete commandQueue[0];
        commandQueue.pop_front();
        qDebug() << "Size:" << commandQueue.size();
    }
    else
        isExecute = false;
    emit ExecutionStatusSignal(isExecute);
}
