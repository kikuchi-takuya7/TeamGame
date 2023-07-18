#include "TitleScene.h"
#include "Engine/Image.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Test.png");
	assert(hPict_ >= 0);
}

//更新
void TitleScene::Update()
{
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void TitleScene::Release()
{
}