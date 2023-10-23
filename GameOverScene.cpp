#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include  "resource.h"
#include <DirectXMath.h>

//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)//, hButton_(-1)
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
	hPict_ = Image::Load("game_over_scene.png");
	assert(hPict_ >= 0);
	hk.scale_ = XMFLOAT3(1.3f, 1.5f, 1.0f);

	//hButton_ = Image::Load("go_backmenu.png");
	//assert(hButton_ >= 0);
	//ht.position_ = XMFLOAT3(0.8f, -0.8, 0);
	//Image::SetAlpha(hButton_, 0);

	backmenu_ = Instantiate<Button>(this);
	backmenu_->SetImage("go_backmenu");
	backmenu_->SetPosition(1655, 680);//ウィンドウの横幅1280,縦720
	backmenu_->SetScale(1.3f, 1.5f, 1.0f);
	//backmenu_->SetNextScene(SELECT);
	//backmenu_->SetIsFlash(false);
}

//更新
void GameOverScene::Update()
{
	/*XMFLOAT3 pos = Input::GetMousePosition();
	if (backmenu_->MouseInArea(pos)) {
		backmenu_->Push(true);
	}
	else {
		backmenu_->Push(false);

	}*/

	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//描画
void GameOverScene::Draw()
{
	Image::SetTransform(hPict_, hk);
	Image::Draw(hPict_);
	/*Image::SetTransform(hButton_, ht);
	Image::Draw(hButton_);*/
}

//開放
void GameOverScene::Release()
{
}