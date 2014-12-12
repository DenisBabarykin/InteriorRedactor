#include "CommandRotate.h"

CommandRotate::CommandRotate(qreal angleOX, qreal angleOY)
{
    this->angleOX = angleOX;
    this->angleOY = angleOY;
}

void CommandRotate::Execute()
{
    SingletonFacade::GetFacade()->RotateSceneCommand(angleOX, angleOY);
}

CommandRotate::~CommandRotate()
{

}
