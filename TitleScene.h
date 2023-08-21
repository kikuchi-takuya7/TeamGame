#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);
	~TitleScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window() override;

private:
	Transform kumo_Transform_;//Kumo�̈ʒu�𒲐����邽�߂̕ϐ�
	int hhaikei_; //�摜�ԍ�(�w�i)
	int hKumo_;  //�摜�ԍ�(�_)
	int hMoji_;  //�摜�ԍ�(����)
	bool kumoMovingUp_;   //��Ɉړ������ǂ����̃t���O
	float kumoMoveSpeed_; //�㉺�ړ����x

	Transform moji_Transform_;
	bool mojiMovingUp_;     // ��Ɉړ������ǂ����̃t���O
	float mojiMoveSpeed_;   // �㉺�ړ����x

	HANDLE hFile_;        //�t�@�C���̃n���h��

	void ChangeAlpha();
	void ChangeScene();

	Transform start_Transform_;//Start�̈ʒu�𒲐�����ׂ̕ϐ�
	int hStart_; //�摜�ԍ�(start)
	int hBrackStart_; //�摜�ԍ�(����start)
	int alpha_;//����Start�̓����x
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;//�N���b�N���ꂽ���̃t���O
};