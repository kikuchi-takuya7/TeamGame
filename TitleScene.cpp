#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

const LPCSTR fileName = "SaveFile\\TitleSaveData";

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1), hTitle_(-1),  hStart_(-1), hBrackStart_(-1), alpha_(0), changeLimit_(0),tmpLimit_(0), alphaFlag_(false), startFlag_(false)
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//初期化
void TitleScene::Initialize()
{
	hFile_ = CreateFile(
		fileName,                 //ファイル名
		GENERIC_READ,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);

	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile_, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile_,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）


	char* tmp = new char[fileSize];
	int c = 0, sw = 0;

	//新しくロードするデータを増やしたい場合はcaseを一つ増やしてその変数にtmpの内容をstofなりで入れればいい
	for (DWORD i = 0; i < fileSize; i++) {

		if (data[i] == ' ') {
			switch (sw)
			{
			case 0:
				start_Transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				start_Transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				start_Transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				start_Transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				start_Transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				start_Transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				start_Transform_.scale_.x = std::stof(tmp);
				start_Transform_.scale_.y = std::stof(tmp);
				start_Transform_.scale_.z = std::stof(tmp);
				break;
			default:
				break;
			}
			sw++;
			c = 0;
			continue;
		}
		tmp[c] = data[i];
		c++;
	}
	delete[] tmp;
	delete[] data;

	CloseHandle(hFile_);

	

	//背景画像のロード
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);

	hTitle_ = Image::Load("Title.png");
	assert(hTitle_ >= 0);

	title_Transform_.position_.y = 0.1f;

	titleMovingUp_ = true;       //最初は上に移動
	titleMoveSpeed_ = 0.001f;    //移動速度

	hStart_ = Image::Load("Start.png");
	assert(hStart_ >= 0);

	hBrackStart_ = Image::Load("BrackStart.png");
	assert(hBrackStart_ >= 0);
}

//更新
void TitleScene::Update()
{
	//titleの位置を更新
	if (titleMovingUp_) {
		title_Transform_.position_.y += titleMoveSpeed_;
	}
	else {
		title_Transform_.position_.y -= titleMoveSpeed_;
	}
	
	//一定の範囲で反転させる
	if (title_Transform_.position_.y > 0.1f) {
		titleMovingUp_ = false;
	}
	else if (title_Transform_.position_.y < -0.1f) {
		titleMovingUp_ = true;
	}

	//STARTの点滅を管理
	if (!startFlag_) {
		ChangeAlpha();
	}
	else {
		ChangeScene();
	}

	//マウスカーソルの位置
	XMFLOAT3 mouse;
	mouse = Input::GetMousePosition();
	mouse.x -= 480;
	mouse.y -= 570;

	//マウスの初期位置が左上で色々ややこしかったので、クリック処理はごり押しで追加
	if (mouse.x > 0 && mouse.y > 0 && mouse.x < 300 && mouse.y < 200 && startFlag_ == false) {
		alpha_ = 255;
		if (Input::IsMouseButtonDown(0)) {
			startFlag_ = true;
			alphaFlag_ = false;
		}
	}

	

	Image::SetAlpha(hStart_, alpha_);

}

//描画
void TitleScene::Draw()
{

	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);

	Image::SetTransform(hTitle_, title_Transform_);
	Image::Draw(hTitle_);

	Image::SetTransform(hStart_, start_Transform_);
	Image::Draw(hStart_);

	Image::SetTransform(hBrackStart_, start_Transform_);
	//Image::Draw(hBrackStart_);

}

//開放
void TitleScene::Release()
{
}

void TitleScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Title"))
	{
		//Setting_Transform(start_Transform_, -1, 1, 0, 10, "Title");
		
	}
	ImGui::End();

	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT)) {

		//Save_Transform_File(hFile_, fileName);

		hFile_ = CreateFile(
			fileName,                 //ファイル名
			GENERIC_WRITE,           //アクセスモード（書き込み用）
			0,                      //共有（なし）
			NULL,                   //セキュリティ属性（継承しない）
			CREATE_ALWAYS,           //作成方法
			FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
			NULL);                  //拡張属性（なし


		float* save[] = { &start_Transform_.position_.x, &start_Transform_.position_.y, &start_Transform_.position_.z,
						  &start_Transform_.rotate_.x, &start_Transform_.rotate_.y, &start_Transform_.rotate_.z,
						  &start_Transform_.scale_.x };

		const int size = sizeof(save) / sizeof(save[0]);

		std::string s[size];


		for (int i = 0; i < size; i++) {
			s[i] = std::to_string(*save[i]) + " ";
		}


		DWORD dwBytes = 0;  //書き込み位置

		for (int i = 0; i < size; i++) {

			WriteFile(
				hFile_,                   //ファイルハンドル
				s[i].c_str(),                  //保存するデータ（文字列）
				(DWORD)strlen(s[i].c_str()),   //書き込む文字数
				&dwBytes,                //書き込んだサイズを入れる変数
				NULL);                   //オーバーラップド構造体（今回は使わない）

		}



		CloseHandle(hFile_);

	}
}

void TitleScene::ChangeAlpha()
{
	if (!alphaFlag_) {
		alpha_ += 3;
	}
	else {
		alpha_ -= 3;
	}

	if (alpha_ >= 255)
		alphaFlag_ = true;

	if (alpha_ <= 0)
		alphaFlag_ = false;
}

void TitleScene::ChangeScene()
{
	changeLimit_++;

	if (changeLimit_ % 30 == 1) {
		alphaFlag_ = false;
	}

	if (tmpLimit_ > 15)
		alphaFlag_ = true;

	if (alphaFlag_) {
		alpha_ = 255;
		tmpLimit_ = 0;
	}
	else {
		alpha_ = 0;
		tmpLimit_++;
	}
		
	if (changeLimit_ > 120) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
