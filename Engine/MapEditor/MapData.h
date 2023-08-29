#pragma once
#include "../GameObject.h"
#include <vector>


//■■シーンを管理するクラス
class MapData : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MapData(GameObject* parent);

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

	std::vector<int> hModel_;
	std::vector<std::string> fileName_;
	int changeModel_;
};