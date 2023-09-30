#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

class SelectScene : public GameObject
{
private:
	int hPict_;    //画像番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SelectScene(GameObject* parent);
	~SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};