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
	int hCircle1_;
	int hCircle1_2_;

	int hDot_a_;
	int hDot_b_;
	int hDot_c_;

	int hBack_;


	Transform netA1;
	Transform netAR;
	Transform netAG;
	Transform netAB;
	Transform netB;
	Transform cir1_;
	Transform cir1_2_;
	Transform dot_c_;
	Transform back_;

	
	// 描画ループ内での透明度の変更
	float alphaValue = 255; // 最大の透明度（不透明）
	float alphaValueCir = 255; // 最大の透明度（不透明）
	float alphaIncrement = -10; // 透明度の変化量
	float alphaIncrementCir = -20; // 透明度の変化量
	float alphaIncrementFin = -5; // 透明度の変化量
	float alphaIncrementDot = -30; // 透明度の変化量

	float cir1_2_xyz = 0.2f;

	int wCount = 0;
	int dCount = 0;
	int dCount2 = 0;
	int count = 0;
	int eCount = 0;
	int TmTime = WAIT;

	bool flagDot;
	bool flag;
	bool flagFin = true;
	bool flagEra = true;
	
	enum
	{
		WAIT = 0,
		START,
		MARK,
		DOT,
		PREPARATION,
		MOVE,
		FLASH,
		FINISH,
		ERASE,
		END
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