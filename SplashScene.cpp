#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Video.h"





//const LPCSTR fileName = "SaveFile\\SplashSaveData";
Video video;


//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hdenshi_logo_(-1), hsos_logo_(-1), alpha_(0), alphaFlag_(false), countDown_(false), limitTmp_(2.0), limit_(0), time_(0)
{
}

//デストラクタ
SplashScene::~SplashScene()
{
}



//初期化
void SplashScene::Initialize()
{

	video.Initialize();


 //    video.InitializeVideo();
	///* video.LoadFile();*/
	// const wchar_t* filePath = L"TouhokuDenshi_splash.avi";
	// video.LoadFile(filePath);
	// 


	// video.Play();
	// video.WaitForCompletion();
	 


}


//更新
void SplashScene::Update()
{


}

//描画
void SplashScene::Draw()
{

}

//開放
void SplashScene::Release()
{
	
}

void SplashScene::Imgui_Window()
{
	
}

/*void SplashScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Splash"))
	{

		Setting_Transform(sos_Trans_, -1.0f, 1.0f, 365.0f, 5.0f, "SOS");
		//ここに東北電子ロゴ用のSetting_Transformを描く
		Setting_Transform(Denshi_Trams_, -1.0f, 1.0f, 365.0f, 5.0f, "DENSHI");

		ImGui::SliderInt("Startalpha", &alpha_, 0, 255);

		ImGui::SliderFloat("StaySecond", &limitTmp_, 0, 5);

		if (ImGui::Button("Start")) {
			//Initialize();
			Enter();
		}
			
			//updateStop_ = false;
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
		//sosロゴ用のセーブは書いたから、同じように東北電子用のロゴのセーブもする。ロードの順番と同じになるように注意
		float* save[] = { &sos_Trans_.position_.x, &sos_Trans_.position_.y, &sos_Trans_.position_.z,
						  &sos_Trans_.rotate_.x, &sos_Trans_.rotate_.y, &sos_Trans_.rotate_.z,
						  &sos_Trans_.scale_.x ,
						  &Denshi_Trams_.position_.x,& Denshi_Trams_.position_.y,& Denshi_Trams_.position_.z,
						  &Denshi_Trams_.rotate_.x,& Denshi_Trams_.rotate_.y,& Denshi_Trams_.rotate_.z,
						  &Denshi_Trams_.scale_.x, &tmp, &limitTmp_};

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

}*/
