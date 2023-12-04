#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class TeamLogoScene : public GameObject
{
private:
	int hNetWork_a1_;
	int hNetWork_aR_;
	int hNetWork_aG_;
	int hNetWork_aB_;
	int hNetWork_b_;

	Transform netA1;
	Transform netAR;
	Transform netAG;
	Transform netAB;

	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//一年生が決める何秒とどまるかってやつ
	int limit_;//フレームに変換する
	int time_;
	// 描画ループ内での透明度の変更
	float alphaValue = 255; // 最大の透明度（不透明）
	float alphaIncrement = -5; // 透明度の変化量

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TeamLogoScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};