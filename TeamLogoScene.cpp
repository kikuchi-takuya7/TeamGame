#include "TeamLogoScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TeamLogoScene::TeamLogoScene(GameObject* parent)
	: GameObject(parent, "TeamLogoScene")
    ,hNetWork_a1_(-1),hNetWork_aR_(-1), hNetWork_aG_(-1), hNetWork_aB_(-1), hNetWork_b_(-1)
{
}

//初期化
void TeamLogoScene::Initialize()
{   
    //画像データのロード
    hNetWork_a1_ = Image::Load("./tdlogo/network_a.png");
    assert(hNetWork_a1_ >= 0);

    hNetWork_aR_ = hNetWork_a1_;
    assert(hNetWork_aR_ >= 0);

    hNetWork_aG_ = hNetWork_a1_;
    assert(hNetWork_aG_ >= 0);

    hNetWork_aB_ = hNetWork_a1_;
    assert(hNetWork_aB_ >= 0);

    hNetWork_b_ = Image::Load("./tdlogo/network_b.png");
    assert(hNetWork_b_ >= 0);

    netA1.position_.x = 0.045f;
    netAR.position_.x = 0.2f;
    netAG.position_.x = -0.2;
    netAB.position_.x = -0.6;

  
}

//更新
void TeamLogoScene::Update()
{ 

    // タイミングや条件に応じて透明度を変更する
    alphaValue += alphaIncrement;

    // 透明度が一定の範囲を超えた場合、変化量を反転させる
    if (alphaValue <= 0 || alphaValue >= 255) {
        alphaIncrement *= -1;
    }

    // 透明度を変更した後、SetAlpha 関数を呼び出して実際の透明度を設定する
    Image::SetAlpha(hNetWork_b_, alphaValue);
}

//描画
void TeamLogoScene::Draw()
{
    Image::SetTransform(hNetWork_b_, transform_);
    Image::Draw(hNetWork_b_);
   
    //Image::SetTransform(hNetWork_a1_, netA1);
   // Image::Draw(hNetWork_a1_);
   

    
    
    
   /* Image::SetTransform(hNetWork_aR_, netAR);
    Image::Draw(hNetWork_aR_);
    
    
    Image::SetTransform(hNetWork_aG_, netAG);
    Image::Draw(hNetWork_aG_);
    
    
    Image::SetTransform(hNetWork_aB_, netAB);
    Image::Draw(hNetWork_aB_);
    */
    
   
}

//開放
void TeamLogoScene::Release()
{
}