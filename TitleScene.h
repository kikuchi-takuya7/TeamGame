#pragma once
#include "Engine/GameObject.h"
#include "Engine/Button.h"

class TitleScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);
	~TitleScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window() override;

private:
	Transform title_Transform_;//Kumoの位置を調整するための変数
	int hhaikei_; //画像番号(背景)
	int hTitle_;  //画像番号(雲)
	bool titleMovingUp_;   //上に移動中かどうかのフラグ
	float titleMoveSpeed_; //上下移動速度

	HANDLE hFile_;        //ファイルのハンドル

	void ChangeAlpha();
	void ChangeScene();

	Transform start_Transform_;//Startの位置を調整する為の変数
	int hStart_; //画像番号(start)
	int hBrackStart_; //画像番号(黒いstart)
	int alpha_;//黒いStartの透明度
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;//クリックされたかのフラグ

	Button* start_;
};