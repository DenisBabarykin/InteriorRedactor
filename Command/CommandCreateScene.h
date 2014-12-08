#ifndef COMMANDCREATESCENE_H
#define COMMANDCREATESCENE_H

#include "Command.h"
#include "./Scene/SceneMetaData.h"

class CommandCreateScene : public Command
{
public:
    CommandCreateScene(SceneMetaData sceneMetaData);
};

#endif // COMMANDCREATESCENE_H
