#include "GameClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GameClearScene::GameClearScene(GameObject* parent)
	: GameObject(parent, "GameClearScene"), hPict_(-1)
{
}

//�f�X�g���N�^
GameClearScene::~GameClearScene()
{
}

//������
void GameClearScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("ClearImage.jpg");
	assert(hPict_ >= 0);

	transform_.scale_ = XMFLOAT3(1.3f, 1.53f, 1.0f);
}

//�X�V
void GameClearScene::Update()
{
	//�X�y�[�X�L�[��������Ă�����
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}


	
}

//�`��
void GameClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameClearScene::Release()
{
}