#include "MapData.h"
#include "../Model.h"
#include "../Input.h"
#include "../../TestWall.h"
#include "../SaveManager/SaveManager.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../Global.h"



//�R���X�g���N�^
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END),isSave_(false),beginCreateObjSize_(0)
{

    
}

//������
void MapData::Initialize()
{
    //�t�@�C���̒��ɓ����Ă邷�ׂĂ�fbx�t�@�C���̖��O�̎擾
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileName�̌����̗v�f�����m��
    hModel_.assign(fileName_.size(),-1);

    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }
    
    SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Load("SaveFile/SaveTest.json");

    beginCreateObjSize_ = createObjectList_.size();
}

//�X�V
void MapData::Update()
{
    
    CheckDeleteObject();

    //���N���b�N���ꂽ
    if (Input::IsMouseButtonDown(0))
    {
        //���炩�̏���
        CreateObject();
    }
}

//�`��
void MapData::Draw()
{
    for (int x = 0; x < 15; x++) {
        for (int z = 0; z < 15; z++) {
            Transform blockTrans;
            blockTrans.position_.z = z;
            blockTrans.position_.x = x;
            Model::SetTransform(hModel_[0], blockTrans);
            Model::Draw(hModel_[0]);
        }
    }
    Transform objPos;
    objPos.position_.y = 1.0f;

    if (selecting_object == PATTERN_END)
        return;

    //�}�E�X�̈ʒu�ɃI�u�W�F�N�g�����ŕ\��������
    Model::SetTransform(hModel_[selecting_object], objPos);
    Model::Draw(hModel_[selecting_object]);

}

//�J��
void MapData::Release()
{
}

void MapData::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
        if (ImGui::TreeNode("Object")){//Object�̃c���[���N���b�N�����

            int tmp = selecting_object;
            for (int i = 0; i < fileName_.size(); i++) { //fileName���������̖��O�̃��W�I�{�^�����o��悤�ɁBi��selecting_object����v�����炻�������I���ł���
                ImGui::RadioButton(fileName_.at(i).c_str(), &tmp, i);
            }

            ImGui::RadioButton("stay", &tmp, PATTERN_END);//�����I�����Ă��Ȃ���Ԃɂ��������p
            selecting_object = static_cast<FBXPATTERN>(tmp);//int����enum��
            ImGui::TreePop();
        }

        
        if (ImGui::Button("Save"))
            isSave_ = true;

        //Save�������ꂽ�炱�����\�������
        if (isSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("SaveOk?");
            if (ImGui::Button("Save")) {
                
                SaveManager* pSaveManager = Instantiate<SaveManager>(this);
                pSaveManager->Save("SaveTest", createObjectList_);
                isSave_ = false;
            }
            ImGui::End();
        }
    }


    //�����Ɋe�I�u�W�F�N�g��Transform�Ƃ��܂Ƃ߂ď����������������ǁAlist��GameObject�^�����炻�ꂼ���isDelete_�ƃA�N�Z�X�ł��Ȃ�����U��߂�
    //if (ImGui::CollapsingHeader("ObjectData"))
    //{
    //    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
    //        std::string str = GetObjectName() + GetObjectID();
    //        const char* windowName = str.c_str();

    //        if (ImGui::CollapsingHeader(windowName))
    //        {
    //            Setting_Transform((*itr)->GetTransform(), -100.0f, 100.0f, 365.0f, 5.0f, GetObjectName() + GetObjectID());

    //            if (ImGui::Button("Delete")) {

    //            }

    //            if (isDelete_) {
    //                ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
    //                ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
    //                ImGui::Begin("DeleteOk?");
    //                if (ImGui::Button("Delete")) {
    //                    KillMe();
    //                }
    //                ImGui::End();
    //            }

    //        }
    //        ImGui::End();
    //    }

    //}
    ImGui::End();
}

GameObject* MapData::CreateObject()
{

    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����
    switch (selecting_object)
    {
    case TESTFLOOR: {
        break;
    }
    case TESTWALL: {
        TestWall* pTestWall = Instantiate<TestWall>(this);
        int c = beginCreateObjSize_ + 1;
        beginCreateObjSize_++;
        char ID = c + '0'; //�����R�[�h�I��0�𑫂��Ƃ��傤��c�̐�����\����ɂȂ��Ă����
        AddCreateObject(pTestWall);
        pTestWall->SetObjectID(ID); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
        return pTestWall;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // �w��̃N���X������
}

void MapData::AddCreateObject(GameObject* object)
{
    createObjectList_.push_back(object);
}

std::vector<std::string> MapData::get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
{
    HANDLE hFind;
    WIN32_FIND_DATA win32fd;//defined at Windwos.h
    std::vector<std::string> file_names;

    //�g���q�̐ݒ�
    std::string search_name = dir_name + "*." + extension;

    hFind = FindFirstFile(search_name.c_str(), &win32fd);

    if (hFind == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("file not found");
    }

    do {
        if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        }
        else {
            file_names.push_back(win32fd.cFileName);
            printf("%s\n", file_names.back().c_str());

        }
    } while (FindNextFile(hFind, &win32fd));

    FindClose(hFind);

    return file_names;
}

void MapData::CheckDeleteObject()
{

    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end();) {
        if ((*itr)->IsDead()) {
            itr = createObjectList_.erase(itr);
        }
        else {
            itr++;
        }
    }

}
