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

private:
	int hhaikei_; //画像番号(背景)
	int hKumo_;  //画像番号(雲)
	int hMoji_;  //画像番号(文字)
};