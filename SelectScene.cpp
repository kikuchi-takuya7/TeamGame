#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"

//�R���X�g���N�^
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1), hExit_(-1), hPlay_(-1), hStore_(-1), hVolume_(-1)
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
	
	//exit�̉摜�f�[�^�̃��[�h
	hExit_ = Image::Load("Exit.png");
	assert(hExit_ >= 0);

	exit_Transform_.position_.x = -0.43f;

	//volume�̉摜�f�[�^�̃��[�h
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	play_ = Instantiate<Button>(this);
	play_->SetImage("Play");
	play_->SetPosition(600, 350);
	play_->SetNextScene(MAIN);
	play_->SetIsFlash(false);

	store_ = Instantiate<Button>(this);
	store_->SetImage("Store");
	store_->SetPosition(600, 380);
	store_->SetNextScene(STORE);
	store_->SetIsFlash(false);
}

//�X�V
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 pos = Input::GetMousePosition();
	// Play�{�^�����N���b�N���ꂽ�ꍇ�̏���
	if (play_->MouseInArea(pos)) {
		play_->Push(true);
		pSceneManager->ChangeScene(SCENE_ID_MAIN);
	}
	else {
		play_->Push(false);
	}

	// Store�{�^�����N���b�N���ꂽ�ꍇ�̏���
	if (store_->MouseInArea(pos)) {
		store_->Push(true);
		//pSceneManager->ChangeScene(SCENE_ID_STORE);
	}
	else {
		store_->Push(false);
	}
}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hExit_, exit_Transform_);
	Image::Draw(hExit_);

	Image::SetTransform(hVolume_, volume_Transform_);
	Image::Draw(hVolume_);
}

//�J��
void SelectScene::Release()
{
}

BOOL SelectScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//�{�^���̏����l
		SendMessage(GetDlgItem(hDlg, IDC_YES), BM_SETCHECK, BST_CHECKED, 0);
		
		return 0;
	case WM_COMMAND:
		return 0;
	}
	return 0;
}
