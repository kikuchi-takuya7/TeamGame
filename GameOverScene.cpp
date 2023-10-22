#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include  "resource.h"
#include <DirectXMath.h>

//�R���X�g���N�^
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)//, hButton_(-1)
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

	//hButton_ = Image::Load("go_backmenu.png");
	//assert(hButton_ >= 0);
	//ht.position_ = XMFLOAT3(0.8f, -0.8, 0);
	//Image::SetAlpha(hButton_, 0);

	backmenu_ = Instantiate<Button>(this);
	backmenu_->SetImage("go_backmenu");
	backmenu_->SetPosition(1655, 680);//�E�B���h�E�̉���1280,�c720
	backmenu_->SetScale(1.3f, 1.5f, 1.0f);
	//backmenu_->SetNextScene(SELECT);
	//backmenu_->SetIsFlash(false);
}

//�X�V
void GameOverScene::Update()
{
	/*XMFLOAT3 pos = Input::GetMousePosition();
	if (backmenu_->MouseInArea(pos)) {
		backmenu_->Push(true);
	}
	else {
		backmenu_->Push(false);

	}*/

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
	/*Image::SetTransform(hButton_, ht);
	Image::Draw(hButton_);*/
}

//�J��
void GameOverScene::Release()
{
}