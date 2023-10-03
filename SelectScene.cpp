#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"
#include <DirectXMath.h>

using namespace DirectX;

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
	
	hPlay_ = Image::Load("Play.png");
	assert(hPlay_ >= 0);

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

	XMFLOAT3 mousePos = Input::GetMousePosition();

	// Play�{�^�����N���b�N���ꂽ�ꍇ�̏���
	if (hPlay_) {
		// Play�{�^���̍��W�ƃT�C�Y���擾
		float playButtonLeft = play_Transform_.position_.x - (Image::GetWidth(hPlay_) / 2);
		float playButtonRight = play_Transform_.position_.x + (Image::GetWidth(hPlay_) / 2);
		float playButtonTop = play_Transform_.position_.y - (Image::GetHeight(hPlay_) / 2);
		float playButtonBottom = play_Transform_.position_.y + (Image::GetHeight(hPlay_) / 2);

		// �}�E�X��Play�{�^���͈͓̔����`�F�b�N
		if (mousePos.x >= playButtonLeft && mousePos.x <= playButtonRight &&
			mousePos.y >= playButtonTop && mousePos.y <= playButtonBottom) {
			if (Input::IsMouseButtonDown(0)) {
				pSceneManager->ChangeScene(SCENE_ID_MAIN);
				//return; // �{�^���������ꂽ�瑼�̃{�^���̃`�F�b�N���X�L�b�v����
			}
		}
	}

	// Store�{�^�����N���b�N���ꂽ�ꍇ�̏���
	if (hStore_) {
		// Store�{�^���̍��W�ƃT�C�Y���擾
		float storeButtonLeft = store_Transform_.position_.x - (Image::GetWidth(hStore_) / 2);
		float storeButtonRight = store_Transform_.position_.x + (Image::GetWidth(hStore_) / 2);
		float storeButtonTop = store_Transform_.position_.y - (Image::GetHeight(hStore_) / 2);
		float storeButtonBottom = store_Transform_.position_.y + (Image::GetHeight(hStore_) / 2);

		// �}�E�X��Store�{�^���͈͓̔����`�F�b�N
		if (mousePos.x >= storeButtonLeft && mousePos.x <= storeButtonRight &&
			mousePos.y >= storeButtonTop && mousePos.y <= storeButtonBottom) {
			if (Input::IsMouseButtonDown(0)) {
				pSceneManager->ChangeScene(SCENE_ID_STORE);
				//return; // �{�^���������ꂽ�瑼�̃{�^���̃`�F�b�N���X�L�b�v����
			}
		}
	}
}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hPlay_, play_Transform_);
	Image::Draw(hPlay_);

	Image::SetTransform(hStore_, store_Transform_);
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
		return 0;
	}
	return 0;
}
