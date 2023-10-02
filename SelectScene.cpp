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

	//play�̉摜�f�[�^�̃��[�h
	hPlay_ = Image::Load("Play.png");
	assert(hPlay_ >= 0);

	//store�̉摜�f�[�^�̃��[�h
	hStore_ = Image::Load("Store.png");
	assert(hStore_ >= 0);
	
	//exit�̉摜�f�[�^�̃��[�h
	hExit_ = Image::Load("Exit.png");
	assert(hExit_ >= 0);

	exit_Transform_.position_.x = -0.43f;

	//volume�̉摜�f�[�^�̃��[�h
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	
}

//�X�V
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	//Main��ʂɑJ��
	if (hPlay_) {
		if (Input::IsMouseButtonDown(0)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_MAIN);
		}
	}

	//Store��ʂɑJ��
	if (hStore_) {
		if (Input::IsMouseButtonDown(0)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STORE);
		}
	}
	

}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hPlay_, transform_);
	Image::Draw(hPlay_);

	Image::SetTransform(hStore_, transform_);
	Image::Draw(hStore_);

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
		
	}
	return 0;
}
