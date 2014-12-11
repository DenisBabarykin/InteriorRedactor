#include "CommandDraw.h"

CommandDraw::CommandDraw()
{
}

void CommandDraw::Execute()
{
    SingletonFacade::GetFacade()->DrawCommand();
}

CommandDraw::~CommandDraw()
{

}
