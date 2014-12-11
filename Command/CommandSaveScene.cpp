#include "CommandSaveScene.h"

CommandSaveScene::CommandSaveScene(QString fileName)
{
    this->fileName = fileName;
}

void CommandSaveScene::Execute()
{
    SingletonFacade::GetFacade()->SaveSceneCommand(fileName);
}

CommandSaveScene::~CommandRotate()
{
}
