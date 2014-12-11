#include "CommandCreateScene.h"

CommandCreateScene::CommandCreateScene(SceneMetaData sceneMetaData)
{
    this->sceneMetaData = sceneMetaData;
}

CommandCreateScene::Execute()
{
    SingletonFacade::GetFacade()->CreateSceneCommand();
}
