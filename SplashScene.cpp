#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

const LPCSTR fileName = "SaveFile\\SplashSaveData";

//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hdenshi_logo_(-1), hsos_logo_(-1), alpha_(255), alphaFlag_(false)
{
}

//デストラクタ
SplashScene::~SplashScene()
{
}

//初期化
void SplashScene::Initialize()
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
				transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				transform_.scale_.x = std::stof(tmp);
				transform_.scale_.y = std::stof(tmp);
				transform_.scale_.z = std::stof(tmp);
				break;
			case 7:
				alpha_ = std::stoi(tmp);
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

	//クラス変数に宣言 
	Transform rogTransform_;

	//Setting_Transform(rogTransform_, );//-0.413,0,0,0,1.0f,255
	
	//sos画像データのロード
	hsos_logo_ = Image::Load("sos_logo.png");
	assert(hsos_logo_ >= 0);
	//東北電子画像データのロード
	hdenshi_logo_ = Image::Load("Tohokudenshi_logo.png");
	assert(hdenshi_logo_ >= 0);
}

//更新
void SplashScene::Update()
{

#if 0
	if (alpha_ >= 300)//ちょっとだけ長く残る
		alphaFlag_ = true;

	if(alphaFlag_ == false)
		alpha_ += 3;

	if (alphaFlag_ == true)
		alpha_ -= 3;

	if (alpha_ < 0) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
#endif

	Image::SetAlpha(hsos_logo_, alpha_);
	Image::SetAlpha(hdenshi_logo_, alpha_);


}

//描画
void SplashScene::Draw()
{
	Image::SetTransform(hsos_logo_, transform_);
	Image::Draw(hsos_logo_);

	Image::SetTransform(hdenshi_logo_, transform_);
	Image::Draw(hdenshi_logo_);

	

	
}

//開放
void SplashScene::Release()
{
}

void SplashScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Splash"))
	{

		Setting_Transform(transform_, -1.0f, 1.0f, 365.0f, 5.0f, "Splash");
		ImGui::SliderInt("alpha", &alpha_, 0, 255);
	}
	ImGui::End();


	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT) ) {

		//Save_Transform_File(hFile_, fileName);
		
		hFile_ = CreateFile(
			fileName,                 //ファイル名
			GENERIC_WRITE,           //アクセスモード（書き込み用）
			0,                      //共有（なし）
			NULL,                   //セキュリティ属性（継承しない）
			CREATE_ALWAYS,           //作成方法
			FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
			NULL);                  //拡張属性（なし

		float tmp = alpha_;

		//新しく変数をセーブしたい場合はここの後ろに変数を＆を付けて入れるだけ。ロードも忘れずに
		float* save[] = { &transform_.position_.x, &transform_.position_.y, &transform_.position_.z,
						  &transform_.rotate_.x, &transform_.rotate_.y, &transform_.rotate_.z,
						  &transform_.scale_.x , &tmp};
		
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
