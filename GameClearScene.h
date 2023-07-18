#pragma once
#include "Engine/GameObject.h"

class GameClearScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameClearScene(GameObject* parent);
	~GameClearScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};