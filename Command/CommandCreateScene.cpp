#include "CommandCreateScene.h"

CommandCreateScene::CommandCreateScene(SceneMetaData sceneMetaData)
{
    this->sceneMetaData = sceneMetaData;
}

void CommandCreateScene::Execute()
{
    SingletonFacade::GetFacade()->CreateSceneCommand(sceneMetaData);
}

CommandCreateScene::~CommandCreateScene()
{
}
