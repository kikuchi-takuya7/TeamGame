#include "SelectScene.h"
#include "Engine/Image.h"

//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1)
{
}

//デストラクタ
SelectScene::~SelectScene()
{
}

//初期化
void SelectScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);
	
}

//更新
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);
}

//描画
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void SelectScene::Release()
{
}