#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class ResultScene : public GameObject
{
private:
    int hPict_;    //画像番号
	Text* pText;
	int sec = 210;  //MainGameから持ってくる？
	int minuts;
	int seconds;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};