#include "ResultScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_(-1), pText(nullptr)
{
}

//初期化
void ResultScene::Initialize()
{
    //画像データのロード
    hPict_ = Image::Load("ReBack.png");
    assert(hPict_ >= 0);

    //Text::Initialize("char_kodomo.png", 64, 64, 16);
    pText = new Text;
    pText->Initialize("char_kodomo.png", 64, 64, 16);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
    pText->Draw(30, 30, "!1AQaq");
}

//開放
void ResultScene::Release()
{
    pText->Release();
}