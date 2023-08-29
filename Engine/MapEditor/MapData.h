#pragma once
#include "../GameObject.h"
#include <vector>


//�����V�[�����Ǘ�����N���X
class MapData : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MapData(GameObject* parent);

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

	std::vector<int> hModel_;
	std::vector<std::string> fileName_;
	int changeModel_;
};