#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);
	~GameOverScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};