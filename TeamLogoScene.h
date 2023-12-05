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

	Transform netA1;
	Transform netAR;
	Transform netAG;
	Transform netAB;
	Transform netB;

	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//��N�������߂鉽�b�Ƃǂ܂邩���Ă��
	int limit_;//�t���[���ɕϊ�����
	int time_;
	// �`�惋�[�v���ł̓����x�̕ύX
	float alphaValue = 255; // �ő�̓����x�i�s�����j
	float alphaIncrement = -10; // �����x�̕ω���
	float alphaIncrementFin = -5; // �����x�̕ω���


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