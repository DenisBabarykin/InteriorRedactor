#ifndef COMMANDROTATE_H
#define COMMANDROTATE_H

#include "Command.h"
#include "./Facade/SingletonFacade.h"

class CommandRotate : public Command
{
private:
    qreal angleOX;
    qreal angleOY;

public:
    CommandRotate(qreal angleOX, qreal angleOY);
    void Execute();
    ~CommandRotate();
};

#endif // COMMANDROTATE_H
