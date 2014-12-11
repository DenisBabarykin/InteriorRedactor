#ifndef COMMANDDRAW_H
#define COMMANDDRAW_H

#include "Command.h"
#include "./Facade/SingletonFacade.h"

class CommandDraw : public Command
{
public:
    CommandDraw();
    void Execute();
    ~CommandDraw();
};

#endif // COMMANDDRAW_H
