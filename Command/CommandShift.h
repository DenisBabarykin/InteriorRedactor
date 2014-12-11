#ifndef COMMANDSHIFT_H
#define COMMANDSHIFT_H

#include "Command.h"
#include "./Facade/SingletonFacade.h"

class CommandShift : public Command
{
    qreal dx, dy, dz;

public:
    CommandShift(qreal dx, qreal dy, qreal dz);
    Execute();
    ~CommandRotate();
};

#endif // COMMANDSHIFT_H
