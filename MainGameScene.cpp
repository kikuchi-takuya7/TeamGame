#include "MainGameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//デストラクタ
MainGameScene::~MainGameScene()
{
}

//初期化
void MainGameScene::Initialize()
{
}

//更新
void MainGameScene::Update()
{
	if(Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

//描画
void MainGameScene::Draw()
{
}

//開放
void MainGameScene::Release()
{
}