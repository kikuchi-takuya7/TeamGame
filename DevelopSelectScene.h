#pragma once
#include "Engine/GameObject.h"


enum SCENESELECT {
	NONE = -1,
	SPLASH,
	TITLE,
	SELECT,
	MAIN,
	GAMECLEAR,
	GAMEOVER,
	MAPEDITOR,
};

//■■シーンを管理するクラス
class DevelopSelectScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	DevelopSelectScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Imgui_Window() override;

private:
	SCENESELECT scene_;
};