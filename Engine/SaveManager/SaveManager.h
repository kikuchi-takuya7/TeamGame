#pragma once
#include "../GameObject.h"


//���������Ǘ�����N���X
class SaveManager : public GameObject
{

public:
    //�R���X�g���N�^
    SaveManager(GameObject* parent);

    //�f�X�g���N�^
    ~SaveManager();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Save(std::string fileName, std::list<GameObject*> list);

    void AddSaveObj(GameObject* obj);

    void Load(std::string fileName);

    GameObject* CreateObj(std::string className);     // �I�u�W�F�N�g����

private:

};

//namespace SaveManager
//{
//
//
//    //������
//    void Initialize();
//
//    //�X�V
//    void Update();
//
//    //�J��
//    void Release();
//
//    void Save(std::string fileName, std::list<GameObject*> list);
//
//    void AddSaveObj(GameObject* obj);
//
//    void Load(std::string fileName);
//
//    GameObject* CreateObj(std::string className);     // �I�u�W�F�N�g����
//
//};