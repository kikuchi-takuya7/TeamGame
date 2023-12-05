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

	int hCircle2_a_;
	int hCircle2_b_;

	Transform netA1;
	Transform netAR;
	Transform netAG;
	Transform netAB;
	Transform netB;

	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//一年生が決める何秒とどまるかってやつ
	int limit_;//フレームに変換する
	int time_;
	// 描画ループ内での透明度の変更
	float alphaValue = 255; // 最大の透明度（不透明）
	float alphaIncrement = -10; // 透明度の変化量
	float alphaIncrementFin = -5; // 透明度の変化量


	int count = 0;
	int time = 0;

	bool flag;
	bool flag2 = true;
	
	enum
	{
		START = 0,
		MOVE,
		FLASH,
		FINISH
	};

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