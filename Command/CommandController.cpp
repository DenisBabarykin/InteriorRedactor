#include "CommandController.h"

CommandController::CommandController()
{
    isExecute = true;
}

void CommandController::Execute()
{
    if (!isExecute())
        ExecuteNext();
}

void CommandController::ExecuteNext()
{
    if (!commandQueue.empty())
    {
        isExecute = true;
        commandQueue[0]->Execute();
        commandQueue.pop_front();
    }
    else
        isExecute = false;
    emit ExecutionStatusSignal(isExecute);
}
