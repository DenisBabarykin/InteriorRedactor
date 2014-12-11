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

CommandController::~CommandController()
{
    if (!commandQueue.empty())
    {
        for (int i = 0; i < commandQueue.size(); ++i)
            delete commandQueue[i];
        commandQueue.clear();
    }
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
