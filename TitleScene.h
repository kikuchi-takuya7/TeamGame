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

private:
	int hhaikei_; //�摜�ԍ�(�w�i)
	int hKumo_;  //�摜�ԍ�(�_)
	int hMoji_;  //�摜�ԍ�(����)
};