#pragma once
#include "Engine/GameObject.h"


enum SCENESELECT {
	NONE = -1,
	SPLASH,
	TITLE,
	SELECT,
	MAIN,
	GAMECLEAR,
	GAMEOVER,
	MAPEDITOR,
};

//�����V�[�����Ǘ�����N���X
class DevelopSelectScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	DevelopSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Imgui_Window() override;

private:
	SCENESELECT scene_;
};