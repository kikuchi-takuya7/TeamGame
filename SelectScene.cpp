#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"
#include "Engine/Audio.h"
#include <DirectXMath.h>

using namespace DirectX;

//�R���X�g���N�^
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1), hVolume_(-1), hSound_(-1)
{
}

//�f�X�g���N�^
SelectScene::~SelectScene()
{
}

//������
void SelectScene::Initialize()
{
	//�T�E���h�f�[�^�̃��[�h
	hSound_ = Audio::Load("A1_01001.WAV");
	assert(hSound_ >= 0);

	currentVolume = 1.0f;

	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);

	//volume�̉摜�f�[�^�̃��[�h
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	play_ = Instantiate<Button>(this);
	play_->SetImage("Play");
	play_->SetPosition(100, 500);//�E�B���h�E�̉���1280,�c720
	play_->SetNextScene(MAIN);
	play_->SetIsFlash(false);

	playz_ = Instantiate<Button>(this);
	playz_->SetPosition(100, 500);

	store_ = Instantiate<Button>(this);
	store_->SetImage("Store");
	store_->SetPosition(1100, 230);
	store_->SetNextScene(STORE);
	store_->SetIsFlash(false);

	storez_ = Instantiate<Button>(this);
	storez_->SetPosition(1100, 230);

	exit_ = Instantiate<Button>(this);
	exit_->SetImage("Exit");
	exit_->SetPosition(100, 350);

	exitz_ = Instantiate<Button>(this);
	exitz_->SetPosition(100, 350);
}

//�X�V
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 pos = Input::GetMousePosition();
	if (play_->MouseInArea(pos)) {
		playz_->SetImage("Play_zoom");
		play_->Push(true);
		return;
	}
	else {
		playz_->SetImage("Play");
		play_->Push(false);
	}

	if (store_->MouseInArea(pos)) {
		storez_->SetImage("Store_zoom");
		store_->Push(true);
		return;
	}
	else {
		storez_->SetImage("Store");
		store_->Push(false);
	}

	if (exit_->MouseInArea(pos)) {
		exitz_->SetImage("Exit_zoom");
		if (Input::IsMouseButtonDown(0))
			Dlog_ = true;
	}
	else {
		exitz_->SetImage("Exit");
		exit_->Push(false);
		Dlog_ = false;
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		Audio::Play(hSound_);
	}

	if (Input::IsKeyDown(DIK_UP)) {
		// ��L�[�������ꂽ�Ƃ��A���ʂ�0.1���グ��
		currentVolume += 0.1f;
		Audio::SetVolume(hSound_, currentVolume);
	}
}

//�`��
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hVolume_, volume_Transform_);
	Image::Draw(hVolume_);

}

//�J��
void SelectScene::Release()
{
}

bool SelectScene::GetDlog() const
{
	return Dlog_;
}

void SelectScene::SetDlog(bool log)
{
	Dlog_ = log;
}

BOOL SelectScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return 0;
	case WM_COMMAND:
		buttonId = LOWORD(wp);
		if (buttonId == IDC_YES) {
			PostQuitMessage(0);  //�v���O�����I��
			return TRUE;
		}
		else if (buttonId == IDC_NO) {
			EndDialog(hDlg, IDC_NO);
			return TRUE;
		}
		return 0;
	}
	return 0;
}
