#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
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

	
	// �`�惋�[�v���ł̓����x�̕ύX
	float alphaValue = 255; // �ő�̓����x�i�s�����j
	float alphaValueCir = 255; // �ő�̓����x�i�s�����j
	float alphaIncrement = -10; // �����x�̕ω���
	float alphaIncrementCir = -20; // �����x�̕ω���
	float alphaIncrementFin = -5; // �����x�̕ω���
	float alphaIncrementDot = -30; // �����x�̕ω���

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
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TeamLogoScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};