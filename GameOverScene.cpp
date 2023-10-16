#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1), hButton_(-1)
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
	hPict_ = Image::Load("game_over_scene.png");
	assert(hPict_ >= 0);
	hk.scale_ = XMFLOAT3(1.3f, 1.5f, 1.0f);

	hButton_ = Image::Load("Test.png");
	assert(hButton_ >= 0);
	ht.position_ = XMFLOAT3(0.8f, -0.8, 0);
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
	Image::SetTransform(hPict_, hk);
	Image::Draw(hPict_);
	Image::SetTransform(hButton_, ht);
	Image::Draw(hButton_);
}

//�J��
void GameOverScene::Release()
{
}