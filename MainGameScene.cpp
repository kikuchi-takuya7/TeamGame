#include "MainGameScene.h"
#include "Engine/Image.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), hPict_(-1)
{
}

//デストラクタ
MainGameScene::~MainGameScene()
{
}

//初期化
void MainGameScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Title.png");
	assert(hPict_ >= 0);
}

//更新
void MainGameScene::Update()
{
}

//描画
void MainGameScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void MainGameScene::Release()
{
}