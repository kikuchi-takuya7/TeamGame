#include "SaveManager.h"
#include <iostream>
#include "../json-develop/include/nlohmann/json.hpp"
#include "../../TestWall.h"
#include "../MapEditor/MapData.h"
#include <fstream>

using json = nlohmann::json;
using string = std::string;


//�R���X�g���N�^
SaveManager::SaveManager(GameObject* parent)
    :GameObject(parent, "SaveManager")
{
}

//�f�X�g���N�^
SaveManager::~SaveManager()
{
}

//������
void SaveManager::Initialize()
{

}

//�X�V
void SaveManager::Update()
{

}

void SaveManager::Draw()
{
}

//�J��
void SaveManager::Release()
{
    //m_SaveObjctList_.clear();
}

void SaveManager::Save(std::string fileName,std::list<GameObject*> list)
{

    int listSize = list.size();
        
    //�t�@�C���쐬�̏���
    string prevPath = "SaveFile/";
    string filename = fileName;
    string Extension = ".json";
    filename = prevPath + filename + Extension;

    //�t�@�C�����J��
    std::ofstream writing_file;
    writing_file.open(filename, std::ios::out);

    int i = 1;
    for (auto itr = list.begin(); itr != list.end();itr++) {


        //���ꂼ���Transform���������ē����
        XMFLOAT3 pos = (*itr)->GetPosition();
        XMFLOAT3 rot = (*itr)->GetRotate();
        XMFLOAT3 sca = (*itr)->GetScale();

        float arr[9] = { pos.x,pos.y,pos.z,
                         rot.x,rot.y,rot.z,
                         sca.x,sca.y,sca.z };

        json m_json = {
                {"objectName",(*itr)->GetObjectName()},
                {"Transform",arr},
                {"objectID",i} //ID�͂�����1������͂��Ȃ��Ƃ������ɍs�����Ƃ���ID��2�Ƃ��Ŕ�鎞������
        };

        //��s������
        writing_file << m_json.dump() << std::endl;

        i++;
    }
        
    writing_file.close();
}

void SaveManager::AddSaveObj(GameObject* obj)
{
    //m_SaveObjctList_.push_back(obj);
}

void SaveManager::Load(std::string fileName)
{

    //�ǂݍ��݂Ɏ��s�����ꍇ�̓G���[��\������
    std::ifstream ifs(fileName.c_str());

    //eof����肭�g���Ȃ�����t�@�C���̍s����������ɂ�������
    int fileLine = 0;

    //�ǂݍ��߂Ȃ�������Ԃ�
    if (!ifs)
        return;

    while (true)
    {
        string line;
        // 1�s�ǂݎ��B
        getline(ifs, line);
        fileLine++;

        // �t�@�C�����I�[�܂ŗ�����break 
        if (ifs.eof())
            break;
    }

    //���t�@�C���ǂݍ��݂��񂵂������U����
    ifs.close();

    //���͂̎��ɉ��s���Ă邩�����炷
    fileLine--;

    ifs.open(fileName.c_str(), std::ios::in);

    //�t�@�C���̃��C���̐�������
    for (int i = 0; i < fileLine;i++) {
        json m_json;
        ifs >> m_json;

        //�v�f������Ȃ��߂�
        if (m_json["objectName"].empty() || m_json["Transform"].empty() || m_json["objectID"].empty())
            continue;

        GameObject* object = CreateObj(m_json["objectName"]);
            
        //�ǂݍ��񂾃f�[�^���I�u�W�F�N�g�ɓ����
        Transform objTrans;
        objTrans.position_.x = m_json["Transform"].at(0);
        objTrans.position_.y = m_json["Transform"].at(1);
        objTrans.position_.z = m_json["Transform"].at(2);
        objTrans.rotate_.x = m_json["Transform"].at(3);
        objTrans.rotate_.y = m_json["Transform"].at(4);
        objTrans.rotate_.z = m_json["Transform"].at(5);
        objTrans.scale_.x = m_json["Transform"].at(6);
        objTrans.scale_.y = m_json["Transform"].at(7);
        objTrans.scale_.z = m_json["Transform"].at(8);

        object->SetTransform(objTrans);

        //char�^�̐����𐮐��^�œǂݍ����char�^��0�𑫂��Ƃ��傤�ǂ��̐����ɂȂ�
        int tmp = m_json["objectID"];

        char ID = (char)tmp + '0';

        //strcpy_s(ID, tmp.size() + 1, tmp.c_str());

        object->SetObjectID(ID);
    }


    ifs.close();
}

GameObject* SaveManager::CreateObj(std::string className)
{
    //���[�h����objectName�ɑΉ�����I�u�W�F�N�g���쐬���AMapData��createObject�ɓ����
    if (className == "TestWall") {
        TestWall* Player = Instantiate<TestWall>(this->GetParent());
        ((MapData*)this->GetParent())->AddCreateObject(Player);
        return Player;
    }

    return NULL;   // �w��̃N���X������
}

