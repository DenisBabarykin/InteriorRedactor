#include "CommandDraw.h"

CommandDraw::CommandDraw()
{
}

CommandDraw::Execute()
{
    SingletonFacade::GetFacade()->DrawCommand();
}

CommandDraw::~CommandRotate()
{

}
