#pragma once
#include "Engine/GameObject.h"

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
	int hhaikei_; //画像番号(背景)
	int hKumo_;  //画像番号(雲)
	int hMoji_;  //画像番号(文字)

	HANDLE hFile_;        //ファイルのハンドル

	void ChangeAlpha();
	void ChangeScene();

	Transform start_Transform_;
	int hStart_; //画像番号(start)
	int hBrackStart_; //画像番号(黒いstart)
	int alpha_;
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;
};