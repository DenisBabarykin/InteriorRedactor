#ifndef COMMANDROTATE_H
#define COMMANDROTATE_H

#include "Command.h"
#include "./Facade/SingletonFacade.h"

class CommandRotate : public Command
{
private:
    int angleOX;
    int angleOY;

public:
    CommandRotate(int angleOX, int angleOY);
    Execute();
    ~CommandRotate();
};

#endif // COMMANDROTATE_H
