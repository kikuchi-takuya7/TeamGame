#include "TitleScene.h"
#include "Engine/Image.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1), hKumo_(-1), hMoji_(-1)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	//�w�i�摜�̃��[�h
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);

	//�摜�̃��[�h
	hMoji_ = Image::Load("kumotomozi.png");
	assert(hMoji_ >= 0);

}

//�X�V
void TitleScene::Update()
{
	
}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);

	Image::SetTransform(hKumo_, transform_);
	Image::Draw(hMoji_);
	
}

//�J��
void TitleScene::Release()
{
}