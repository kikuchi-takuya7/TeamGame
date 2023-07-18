#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hPict_(-1), alpha_(0), alphaFlag_(false)
{
}

//�f�X�g���N�^
SplashScene::~SplashScene()
{
}

//������
void SplashScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Test.png");
	assert(hPict_ >= 0);
}

//�X�V
void SplashScene::Update()
{

	if (alpha_ >= 300)//������Ƃ��������c��
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

//�`��
void SplashScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	
}

//�J��
void SplashScene::Release()
{
}