#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Button.h"

class SelectScene : public GameObject
{
private:
	int hPict_;    //�摜�ԍ�
	Transform exit_Transform_;//Exit�̈ʒu�𒲐����邽�߂̕ϐ�
	int hExit_;    //exit�̉摜�ԍ�
	Transform play_Transform_;
	int hPlay_;    //play�̉摜
	Transform store_Transform_;
	int hStore_;   //store�̉摜�ԍ�
	Transform volume_Transform_;
	int hVolume_;   //volume�̉摜�ԍ�
	bool log;       //�_�C�A���O�̃t���O
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SelectScene(GameObject* parent);
	~SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};
