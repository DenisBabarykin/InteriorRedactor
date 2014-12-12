#ifndef COMMANDCREATEPAINTER_H
#define COMMANDCREATEPAINTER_H

#include "Command.h"
#include "./Facade/SingletonFacade.h"
#include "./Painter/PainterType.h"

class CommandCreatePainter : public Command
{
private:
    PainterType::PainterType painterType;
    int width, height;

public:
    CommandCreatePainter(PainterType::PainterType painterType, int width, int height);
    void Execute();
    ~CommandCreatePainter();
};

#endif // COMMANDCREATEPAINTER_H
