#pragma once
#include "Engine/GameObject.h"


class SplashScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SplashScene(GameObject* parent);
	~SplashScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hPict_;
	int alpha_;
	bool alphaFlag_;
};