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

	//playの画像データのロード
	hPlay_ = Image::Load("Play.png");
	assert(hPlay_ >= 0);

	//storeの画像データのロード
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

	//Main画面に遷移
	if (hPlay_) {
		if (Input::IsMouseButtonDown(0)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_MAIN);
		}
	}

	//Store画面に遷移
	if (hStore_) {
		if (Input::IsMouseButtonDown(0)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_STORE);
		}
	}
	

}

//描画
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
		
	}
	return 0;
}
