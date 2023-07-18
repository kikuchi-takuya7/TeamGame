#pragma once
#include "Engine/GameObject.h"

class SelectScene : public GameObject
{
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