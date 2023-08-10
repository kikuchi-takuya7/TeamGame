#pragma once
#include "GameObject.h"


//-----------------------------------------------------------
//一番トップに来るオブジェクト
//すべてのオブジェクトは、これの子孫になる
//-----------------------------------------------------------
class RootObject :	public GameObject
{
public:
	RootObject();
	~RootObject();

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
	bool conf_;
};

