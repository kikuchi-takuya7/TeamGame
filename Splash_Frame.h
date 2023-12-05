#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class Splash_Frame : public GameObject
{
private:
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Splash_Frame(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;


};

