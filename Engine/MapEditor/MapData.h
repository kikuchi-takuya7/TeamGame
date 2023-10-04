#pragma once
#include "../GameObject.h"
#include <vector>


//�V�����t�@�C����ǉ�������A������CreateObject�ɗv�f���蓮�Œǉ�����
enum FBXPATTERN {
	ROOM_1,
	STAGE,//���ō�������炱��Ə�̓z�̓N���b�N���Ȃ������ǂ�
	TESTFLOOR,
	TESTWALL,
	PATTERN_END
};

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

	std::list<GameObject*> GetCreateObjectList() { return createObjectList_; }

	/// <summary>
	/// selecting_object�ɑΉ������I�u�W�F�N�g���쐬����
	/// </summary>
	/// <returns>�쐬�����I�u�W�F�N�g</returns>
	GameObject* CreateObject();

	//createObjectList�ɓ����
	void AddCreateObject(GameObject* object);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

	//createObject�̒���delete���ꂽ�I�u�W�F�N�g�����邩
	void CheckDeleteObject();

	//�I�u�W�F�N�g�̈ʒu�iCreateList�j����ɏグ��
	void ChengeUp(GameObject* pTarget);
	void ChengeDown(GameObject* pTarget);

	//���[�h�������ׂĂ�ID�𒲂ׂčő�l��m���Ă���
	int MaxObjectId();

private:

	std::vector<int> hModel_;
	
	//Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
	std::vector<std::string> fileName_;
	
	//imgui�őI������Ă���I�u�W�F�N�g
	FBXPATTERN selecting_object;

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<GameObject*> createObjectList_;

	//�Z�[�u���邩�̃t���O
	bool isSave_;

	int nextObjectId_;



};