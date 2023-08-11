#include "TitleScene.h"
#include "Engine/Image.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1)
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
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);
}

//更新
void TitleScene::Update()
{
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);
}

//開放
void TitleScene::Release()
{
}