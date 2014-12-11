#ifndef COMMANDSAVESCENE_H
#define COMMANDSAVESCENE_H

#include "Command.h"
#include <QString>
#include "./Facade/SingletonFacade.h"

class CommandSaveScene : public Command
{
private:
    QString fileName;

public:
    CommandSaveScene(QString fileName);
    void Execute();
    ~CommandSaveScene();
};

#endif // COMMANDSAVESCENE_H
