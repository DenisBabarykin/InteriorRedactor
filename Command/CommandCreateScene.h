#ifndef COMMANDCREATESCENE_H
#define COMMANDCREATESCENE_H

#include "Command.h"
#include "./Scene/SceneMetaData.h"
#include "./Facade/SingletonFacade.h"

class CommandCreateScene : public Command
{
    SceneMetaData sceneMetaData;
public:
    CommandCreateScene(SceneMetaData sceneMetaData);
    Execute();
    ~CommandRotate();
};

#endif // COMMANDCREATESCENE_H
