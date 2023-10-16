#include "GameClearScene.h"
#include "Engine/SceneManager.h"

//コンストラクタ
GameClearScene::GameClearScene(GameObject* parent)
	: GameObject(parent, "GameClearScene")
{
}

//デストラクタ
GameClearScene::~GameClearScene()
{
}

//初期化
void GameClearScene::Initialize()
{
}

//更新
void GameClearScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT);
}

//描画
void GameClearScene::Draw()
{
}

//開放
void GameClearScene::Release()
{
}