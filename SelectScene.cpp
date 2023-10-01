#include "SelectScene.h"
#include "Engine/Image.h"

//�R���X�g���N�^
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1)
{
}

//�f�X�g���N�^
SelectScene::~SelectScene()
{
}

//������
void SelectScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);
	
}

//�X�V
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);
}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void SelectScene::Release()
{
}