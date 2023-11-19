#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"
#include <DirectXMath.h>

using namespace DirectX;

//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1), hVolume_(-1), hExit_(-1)
{
}

//デストラクタ
SelectScene::~SelectScene()
{
}

//初期化
void SelectScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("haikei.png");
	assert(hPict_ >= 0);

	//volumeの画像データのロード
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	hExit_ = Image::Load("Exit_zoom.png");
	assert(hExit_ >= 0);

	play_ = Instantiate<Button>(this);
	play_->SetImage("Play");
	play_->SetPosition(100, 500);//ウィンドウの横幅1280,縦720
	play_->SetNextScene(MAIN);
	play_->SetIsFlash(false);

	store_ = Instantiate<Button>(this);
	store_->SetImage("Store");
	store_->SetPosition(1100, 230);
	store_->SetNextScene(STORE);
	store_->SetIsFlash(false);

	exit_ = Instantiate<Button>(this);
	exit_->SetImage("Exit");
	exit_->SetPosition(100, 350);
}

//更新
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 pos = Input::GetMousePosition();
	if (play_->MouseInArea(pos)) {
		play_->Push(true);
		return;
	}
	else {
		play_->Push(false);

	}

	if (store_->MouseInArea(pos)) {
		store_->Push(true);
		return;
	}
	else {
		store_->Push(false);
	}

	if (exit_->MouseInArea(pos)) {
		if (Input::IsMouseButtonDown(0))
			Dlog_ = true;
	}
	else {
		exit_->Push(false);
		Dlog_ = false;
	}

	
}

//描画
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hVolume_, volume_Transform_);
	Image::Draw(hVolume_);

	XMFLOAT3 pos = Input::GetMousePosition();
	if (exit_->MouseInArea(pos)) {
		Image::SetTransform(hExit_, exit_Transform_);
		Image::Draw(hExit_);
	}
}

//開放
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
			PostQuitMessage(0);  //プログラム終了
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
