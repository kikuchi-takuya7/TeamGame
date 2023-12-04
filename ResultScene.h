#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class ResultScene : public GameObject
{
private:
    int hPict_;    //�摜�ԍ�
	Text* pText;
	int sec = 0;  //MainGame���玝���Ă���H
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};