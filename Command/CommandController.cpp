#include "CommandController.h"

CommandController::CommandController(QObject *parent)
{
    isExecute = true;
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
    commandQueue.push_back(command);
}

bool CommandController::IsExecute()
{
    return isExecute;
}

void CommandController::ExecuteNext()
{
    if (!commandQueue.empty())
    {
        isExecute = true;
        commandQueue[0]->Execute();
        delete commandQueue[0];
        commandQueue.pop_front();
    }
    else
        isExecute = false;
    emit ExecutionStatusSignal(isExecute);
}
