#pragma once
#include "Engine/GameObject.h"


class SplashScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SplashScene(GameObject* parent);
	~SplashScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window();
	//void Imgui_Window() override;
	bool Finished();//Readyが終わったらtrue
	
	
private:
	int hImage_;//ロゴ本体
	int heye_;//ロゴの目
	int hframe_;//ロゴの枠
	
	int hsos_logo_; //sosロゴ画像番号
	int hdenshi_logo_; //東北電子ロゴ画像番号

	Transform sos_Trans_; //sosロゴ画像のTransform
	Transform Denshi_Trams_; //東北電子ロゴのTransform

	Transform heye_Trans_; //sosロゴ画像のTransform
	Transform hframe_Trans_; //東北電子ロゴのTransform

	HANDLE hFile_;        //ファイルのハンドル
	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//一年生が決める何秒とどまるかってやつ
	int limit_;//フレームに変換する
	int time_;
	
};


