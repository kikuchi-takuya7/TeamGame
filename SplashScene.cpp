#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hPict_(-1), alpha_(0), alphaFlag_(false)
{
}

//デストラクタ
SplashScene::~SplashScene()
{
}

//初期化
void SplashScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Test.png");
	assert(hPict_ >= 0);
}

//更新
void SplashScene::Update()
{

	if (alpha_ >= 300)//ちょっとだけ長く残る
		alphaFlag_ = true;

	if(alphaFlag_ == false)
		alpha_ += 3;

	if (alphaFlag_ == true)
		alpha_ -= 3;

	if (alpha_ < 0) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}


	Image::SetAlpha(hPict_, alpha_);


}

//描画
void SplashScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	
}

//開放
void SplashScene::Release()
{
}