#include "MapData.h"
#include "../Model.h"
#include "../Input.h"
#include "../Camera.h"
#include "../SaveManager/SaveManager.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../Global.h"
#include "../../TestWall.h"
#include "../../TestFloor.h"
#include "../../Room1.h"


//�R���X�g���N�^
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END),isSave_(false),nextObjectId_(0)
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

    CheckDeleteObject();
    nextObjectId_ = MaxObjectId();
    nextObjectId_++;
}

//�X�V
void MapData::Update()
{
    //����`�F�b�N���Ȃ��ƃf���[�g�����^�C�~���O�ŃG���[�o��B����RootObject��Update�ŏ����ꂽ���ǂ����m�F���Ă邩��
    CheckDeleteObject();

    //�����ƃZ�[�u�����̂Ƀ��[�h�ł��Ȃ��B�Ȃ�ł�˂�
    //Model::AllRelease()���g���΍s���������Ă�������

    //float w = (float)(Direct3D::screenWidth_ / 2.0f);
    //float h = (float)(Direct3D::screenHeight_ / 2.0f);
    //float offsetX = 0;
    //float offsetY = 0;
    //float minZ = 0;
    //float maxZ = 1;

    ////�r���[�|�[�g�쐬
    //XMMATRIX vp =
    //{
    //    w                ,0                ,0           ,0,
    //    0                ,-h               ,0           ,0,
    //    0                ,0                ,maxZ - minZ ,0,
    //    offsetX + w      ,offsetY + h      ,minZ        ,1
    //};

    ////�r���[�|�[�g���t�s���
    //XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    ////�v���W�F�N�V�����ϊ�
    //XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
    ////�т�[�ϊ�
    //XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

    //XMFLOAT3 mousePosFront = Input::GetMousePosition();
    //mousePosFront.z = 0.0;
    //XMFLOAT3 mousePosBack = Input::GetMousePosition();
    //mousePosBack.z = 1.0f;

    ////1,mousePosFront���x�N�g���ɕϊ�
    //XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
    ////2. 1��invVP,invPrj,invView��������
    //vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
    ////3,mousePosBack���x�N�g���ɕϊ�
    //XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
    ////4,3��invVP,invPrj,invVeew��������
    //vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
    ////5,2����4�Ɍ������ă��C��łi�Ƃ肠�����j

    //int changeX = 0;
    //int	changeZ = 0;
    //float minDist = 9999;


    //RayCastData data;
    //XMStoreFloat3(&data.start, vMouseFront);
    //XMStoreFloat3(&data.dir, vMouseBack - vMouseFront);

    //Model::RayCast(hModel_[0], &data);

    //if (data.hit) {
    //    data.hit = false;

    //}

    //Transform objPos;
    //objPos.position_.y = 1.0f;

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

    if (selecting_object == PATTERN_END)
        return;

    Transform objPos;
    objPos.position_.y = 1.0f;

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

        
        if (ImGui::Button("Save")) {
            isSave_ = true;
        }

        //Save�������ꂽ�炱�����\�������
        if (isSave_) {
            ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
            ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
            ImGui::Begin("SaveOk?",&isSave_);
            if (ImGui::Button("Save")) {
                //CheckDeleteObject();
                SaveManager* pSaveManager = Instantiate<SaveManager>(this);
                pSaveManager->Save("SaveTest", createObjectList_);
                isSave_ = false;
            }
            ImGui::End();
        }
    }


    //�����Ɋe�I�u�W�F�N�g��Transform�Ƃ��܂Ƃ߂ď����������������ǁAlist��GameObject�^�����炻�ꂼ���isDelete_�ƃA�N�Z�X�ł��Ȃ�����U��߂�
    if (ImGui::CollapsingHeader("ObjectData"))
    {
        if (ImGui::TreeNode("Data")) {//Object�̃c���[���N���b�N�����
            for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
            
            

                (*itr)->Imgui_Data_Edit();
                
            }

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

GameObject* MapData::CreateObject()
{

    //for�ŉ񂵂�FBXPATTERN��filename�̗v�f�̏��Ԃ���v�����Ƃ���ŃI�u�W�F�N�g�����̂��z�肵������objectName�Ƃ����߂�ǂ������Ȃ邩�疳��
    //�Ή�����enum�^�̐����ɂȂ����炻�̃I�u�W�F�N�g���쐬����createObject�Ƀv�b�V���o�b�N����
    switch (selecting_object)
    {
    case ROOM_1: {
        Room1* pRoom = Instantiate<Room1>(this);
        AddCreateObject(pRoom);
        pRoom->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
        return pRoom;
        break;
    }
    case TESTFLOOR: {
        TestFloor* pTestFloor = Instantiate<TestFloor>(this);
        AddCreateObject(pTestFloor);
        pTestFloor->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
        return pTestFloor;
        break;
    }
    case TESTWALL: {
        TestWall* pTestWall = Instantiate<TestWall>(this);
        AddCreateObject(pTestWall);
        pTestWall->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
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
    //CheckDeleteObject();
    createObjectList_.push_back(object);
    nextObjectId_++;
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

void MapData::ChengeUp(GameObject* pTarget)
{

    auto itr = createObjectList_.begin();

    //���ɐ擪�Ȃ�
    if ((*itr) == pTarget)
        return;

    for (itr ; itr != createObjectList_.end(); itr++) {
        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, -1), createObjectList_, itr);
            break;
        }
    }

    //isUp_ = true;

    /*SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Save("SaveFile/SaveTest.json", createObjectList_);*/
    /*KillAllChildren();
    createObjectList_.clear();
    SaveManager* pSaveManager2 = Instantiate<SaveManager>(this);
    pSaveManager2->Load("SaveFile/SaveTest.json");*/

    //���̊֐����q����Ăяo���Ă�̂�KillAllChildren�łԂ��E���Ă邩��G���[�ɂȂ�
    //bool�^�ϐ��������true�Ȃ炱������UpDate���ɏ�̏���������z���l�������ǃt�@�C���̃��[�h����肭�ł��ĂȂ������B�v���W�F�N�g���s���̓t�@�C�����������Ă����s���ɂ͐V�����f�[�^�����[�h�ł��Ȃ��H
}

void MapData::ChengeDown(GameObject* pTarget)
{

    auto itr = createObjectList_.end();

    itr--;
    //���Ɉ�Ԍ��Ȃ�
    if ((*itr) == pTarget)
        return;

    while(itr!=createObjectList_.begin()) {

        itr--;

        if ((*itr) == pTarget) {
            createObjectList_.splice(std::next(itr, 2), createObjectList_, itr);
            break;
        }
    }

}

int MapData::MaxObjectId()
{
    int ID = 0;
    for (auto itr = createObjectList_.begin(); itr != createObjectList_.end(); itr++) {
        int tmp = (*itr)->GetObjectID();
        if (ID < tmp) {
            ID = tmp;
        }
    }

    return ID;
}
