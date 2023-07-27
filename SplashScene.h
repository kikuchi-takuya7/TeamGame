#pragma once
#include "Engine/GameObject.h"


class SplashScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SplashScene(GameObject* parent);
	~SplashScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window() override;

private:

	HANDLE hFile_;        //�t�@�C���̃n���h��
	int hPict_;
	int alpha_;
	bool alphaFlag_;
	
};