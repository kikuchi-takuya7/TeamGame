#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)
{
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
}

//������
void GameOverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);
}

//�X�V
void GameOverScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

//�`��
void GameOverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameOverScene::Release()
{
}