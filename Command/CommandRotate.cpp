#include "CommandRotate.h"

CommandRotate::CommandRotate(int angleOX, int angleOY)
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
