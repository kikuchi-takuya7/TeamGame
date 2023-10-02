#include "MainGameScene.h"
#include "Engine/Image.h"

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), hPict_(-1)
{
}

//�f�X�g���N�^
MainGameScene::~MainGameScene()
{
}

//������
void MainGameScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Title.png");
	assert(hPict_ >= 0);
}

//�X�V
void MainGameScene::Update()
{
}

//�`��
void MainGameScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void MainGameScene::Release()
{
}