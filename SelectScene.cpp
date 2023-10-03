#include "SelectScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include  "resource.h"
#include <DirectXMath.h>

using namespace DirectX;

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
	
	hPlay_ = Image::Load("Play.png");
	assert(hPlay_ >= 0);

	hStore_ = Image::Load("Store.png");
	assert(hStore_ >= 0);

	//exitの画像データのロード
	hExit_ = Image::Load("Exit.png");
	assert(hExit_ >= 0);

	exit_Transform_.position_.x = -0.43f;

	//volumeの画像データのロード
	hVolume_ = Image::Load("Volume.png");
	assert(hVolume_ >= 0);

	volume_Transform_.position_.y = 0.1f;

	
}

//更新
void SelectScene::Update()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_SELECT);

	XMFLOAT3 mousePos = Input::GetMousePosition();

	// Playボタンがクリックされた場合の処理
	if (hPlay_) {
		// Playボタンの座標とサイズを取得
		float playButtonLeft = play_Transform_.position_.x - (Image::GetWidth(hPlay_) / 2);
		float playButtonRight = play_Transform_.position_.x + (Image::GetWidth(hPlay_) / 2);
		float playButtonTop = play_Transform_.position_.y - (Image::GetHeight(hPlay_) / 2);
		float playButtonBottom = play_Transform_.position_.y + (Image::GetHeight(hPlay_) / 2);

		// マウスがPlayボタンの範囲内かチェック
		if (mousePos.x >= playButtonLeft && mousePos.x <= playButtonRight &&
			mousePos.y >= playButtonTop && mousePos.y <= playButtonBottom) {
			if (Input::IsMouseButtonDown(0)) {
				pSceneManager->ChangeScene(SCENE_ID_MAIN);
				//return; // ボタンが押されたら他のボタンのチェックをスキップする
			}
		}
	}

	// Storeボタンがクリックされた場合の処理
	if (hStore_) {
		// Storeボタンの座標とサイズを取得
		float storeButtonLeft = store_Transform_.position_.x - (Image::GetWidth(hStore_) / 2);
		float storeButtonRight = store_Transform_.position_.x + (Image::GetWidth(hStore_) / 2);
		float storeButtonTop = store_Transform_.position_.y - (Image::GetHeight(hStore_) / 2);
		float storeButtonBottom = store_Transform_.position_.y + (Image::GetHeight(hStore_) / 2);

		// マウスがStoreボタンの範囲内かチェック
		if (mousePos.x >= storeButtonLeft && mousePos.x <= storeButtonRight &&
			mousePos.y >= storeButtonTop && mousePos.y <= storeButtonBottom) {
			if (Input::IsMouseButtonDown(0)) {
				pSceneManager->ChangeScene(SCENE_ID_STORE);
				//return; // ボタンが押されたら他のボタンのチェックをスキップする
			}
		}
	}
}

//描画
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
