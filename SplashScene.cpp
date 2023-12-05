#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Splash_Frame.h"


const LPCSTR fileName = "SaveFile\\SplashSaveData";

//Splash_Frame* Splashframe;

namespace {
	float startX;//移動開始X座標
	float endX;//移動終了X座標
	float totalTime;//移動時間
	float currentTime;//現在の時間
	int seq_line;//今実行している行
	float seq_time;//シーケンスを実行している時間
	enum ACT {//やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct  Sequence {
		float time;//時間
		ACT action;//やること
		float param;//必要な値
	};
	//流れを書いていく
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN,-5.0f},//スライドイン
		{3.0f,A_WAIT,0.0f},//１秒待ってから
		{4.0f,A_SLIDEOUT,5.0f},//スライドアウト
		{5.0f,A_END,0.0f}//ここで消える
	};
	ACT currentAction;
	bool canMove;
};

//コンストラクタ
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), /*hdenshi_logo_(-1), hsos_logo_(-1),*/ alpha_(0), alphaFlag_(false), countDown_(false), limitTmp_(2.0), limit_(0), time_(0)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
}

//デストラクタ
SplashScene::~SplashScene()
{
}

//初期化
void SplashScene::Initialize()
{
	hImage_ = Image::Load("sos_logo_b.png");
	assert(hImage_ >= 0);
	startX = 5.0f;
	endX = 0;
	totalTime = 8.0f;
	currentTime = 0.0f;
	transform_.position_.x = startX;  // 初期X座標を設定

	
	heye_ = Image::Load("sos_logo_a.png");
	assert(heye_ >= 0);
	hframe_ = Image::Load("sos_logo_e.png");
	assert(hframe_ >= 0);

	
	
}
float easeInCubic(float x) {
	return x * x * x;
}


//更新
void SplashScene::Update()
{
	seq_time += 1.0f / 60.0f;//時間を進める
	if (seq_time >= tbl[seq_line + 1].time) {//次の行を実行する
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDEOUT:

			startX = transform_.position_.x;
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;

			//ロゴ透明化
			Image::SetAlpha(heye_, 0);
			Image::SetAlpha(hframe_, 0);
			break;

		}
		//その行の実行をする

	}
	currentTime += 1.0f / 60.0f;//１フレーム分の時間を進ませる
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//ここを0.0～1.0の範囲にする
	float val = easeInCubic(t);
	transform_.position_.x = val * (endX - startX) + startX;

	

}

//描画
void SplashScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);

	Image::SetTransform(heye_, heye_Trans_);
	Image::Draw(heye_);

	Image::SetTransform(hframe_, hframe_Trans_);
	Image::Draw(hframe_);

	

	
	//Image::SetTransform(hdenshi_logo_, Denshi_Trams_);//東北電子ロゴ用のTransform変数に変える
	//Image::Draw(hdenshi_logo_);

	

	
}
bool SplashScene::Finished()
{
	return seq_line >= sizeof(tbl) / sizeof(tbl[0]) - 1;
	return canMove;
	if (currentTime >= totalTime)
		return true;
	return false;
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

}



