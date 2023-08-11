#include "TitleScene.h"
#include "Engine/Image.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);
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
}

//�J��
void TitleScene::Release()
{
}