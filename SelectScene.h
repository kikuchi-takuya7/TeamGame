#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

class SelectScene : public GameObject
{
private:
	int hPict_;    //�摜�ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SelectScene(GameObject* parent);
	~SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};