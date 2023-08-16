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
	int hhaikei_; //�摜�ԍ�(�w�i)
	int hKumo_;  //�摜�ԍ�(�_)
	int hMoji_;  //�摜�ԍ�(����)

	HANDLE hFile_;        //�t�@�C���̃n���h��

	void ChangeAlpha();
	void ChangeScene();

	Transform start_Transform_;
	int hStart_; //�摜�ԍ�(start)
	int hBrackStart_; //�摜�ԍ�(����start)
	int alpha_;
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;
};