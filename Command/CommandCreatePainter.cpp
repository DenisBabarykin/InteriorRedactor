#include "CommandCreatePainter.h"

CommandCreatePainter::CommandCreatePainter(PainterType painterType, int width, int height)
{
    this->painterType = painterType;
    this->width = width;
    this->height = height;
}

void CommandCreatePainter::Execute()
{
    SingletonFacade::GetFacade()->CreatePainterCommand(painterType, width, height);
}

CommandCreatePainter::~CommandCreatePainter()
{
}
