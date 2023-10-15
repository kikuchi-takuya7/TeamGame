#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)
{
}

//デストラクタ
GameOverScene::~GameOverScene()
{
}

//初期化
void GameOverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);
}

//更新
void GameOverScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画
void GameOverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameOverScene::Release()
{
}