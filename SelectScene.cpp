#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"

//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
	: GameObject(parent, "SelectScene"), hPict_(-1), hExit_(-1), hPlay_(-1), hStore_(-1), hVolume_(-1)
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
	
	//exitの画像データのロード
	hExit_ = Image::Load("Exit.png");
	assert(hExit_ >= 0);

	exit_Transform_.position_.x = -0.43f;

	//volumeの画像データのロード
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

//更新
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 pos = Input::GetMousePosition();
	// Playボタンがクリックされた場合の処理
	if (play_->MouseInArea(pos)) {
		play_->Push(true);
		pSceneManager->ChangeScene(SCENE_ID_MAIN);
	}
	else {
		play_->Push(false);
	}

	// Storeボタンがクリックされた場合の処理
	if (store_->MouseInArea(pos)) {
		store_->Push(true);
		//pSceneManager->ChangeScene(SCENE_ID_STORE);
	}
	else {
		store_->Push(false);
	}
}

//描画
void SelectScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Image::SetTransform(hExit_, exit_Transform_);
	Image::Draw(hExit_);

	Image::SetTransform(hVolume_, volume_Transform_);
	Image::Draw(hVolume_);
}

//開放
void SelectScene::Release()
{
}

BOOL SelectScene::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//ボタンの初期値
		SendMessage(GetDlgItem(hDlg, IDC_YES), BM_SETCHECK, BST_CHECKED, 0);
		
		return 0;
	case WM_COMMAND:
		return 0;
	}
	return 0;
}
