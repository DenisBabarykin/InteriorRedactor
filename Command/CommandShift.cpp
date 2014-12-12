#include "CommandShift.h"

CommandShift::CommandShift(qreal dx, qreal dy, qreal dz)
{
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
}

void CommandShift::Execute()
{
    SingletonFacade::GetFacade()->ShiftSceneCommand(dx, dy, dz);
}

CommandShift::~CommandShift()
{

}
