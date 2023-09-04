#include "MapData.h"
#include "../Model.h"
#include "../Input.h"
#include "../../TestWall.h"
#include "../SaveManager/SaveManager.h"
#include <vector>
#include <string>
#include <stdexcept>



//コンストラクタ
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),selecting_object(PATTERN_END)
{

    
}

//初期化
void MapData::Initialize()
{
    //ファイルの中に入ってるすべてのfbxファイルの名前の取得
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileNameの個数分の要素数を確保
    hModel_.assign(fileName_.size(),-1);

    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }
    
    SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Load("SaveFile/SaveTest.json");

}

//更新
void MapData::Update()
{
    XMFLOAT3 mousePos = Input::GetMousePosition();

    //左クリックされた
    if (Input::IsMouseButtonDown(0))
    {
        //何らかの処理
        CreateObject();
    }
}

//描画
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

    //マウスの位置にオブジェクトを仮で表示したい
    Model::SetTransform(hModel_[selecting_object], objPos);
    Model::Draw(hModel_[selecting_object]);

}

//開放
void MapData::Release()
{
}

void MapData::Imgui_Window()
{
    ImGui::Begin("DataWindow");
    if (ImGui::CollapsingHeader("MapEditor"))
    {
        if (ImGui::TreeNode("Object")){//Objectのツリーをクリックすると

            int tmp = selecting_object;
            for (int i = 0; i < fileName_.size(); i++) { //fileName分だけその名前のラジオボタンが出るように。iとselecting_objectが一致したらそこだけ選択できる
                ImGui::RadioButton(fileName_.at(i).c_str(), &tmp, i);
            }

            ImGui::RadioButton("stay", &tmp, PATTERN_END);//何も選択していない状態にしたい時用
            selecting_object = static_cast<FBXPATTERN>(tmp);//intからenumに
            ImGui::TreePop();
        }

        if (ImGui::Button("Save")) {
            SaveManager* pSaveManager = Instantiate<SaveManager>(this);
            pSaveManager->Save("SaveTest",createObjectList_);
        }
    }
    ImGui::End();
}

GameObject* MapData::CreateObject()
{

    //forで回してFBXPATTERNとfilenameの要素の順番が一致したところでオブジェクトを作るのも想定したけどobjectNameとかがめんどくさくなるから無し
    //対応したenum型の数字になったらそのオブジェクトを作成してcreateObjectにプッシュバックする
    switch (selecting_object)
    {
    case TESTFLOOR: {
        break;
    }
    case TESTWALL: {
        TestWall* pTestWall = Instantiate<TestWall>(this);
        AddCreateObject(pTestWall);
        int c = createObjectList_.size();
        char ID = c + '0'; //文字コード的に0を足すとちょうどcの数字を表すやつになってくれる
        pTestWall->GetobjectID(ID); //作ったオブジェクト順に識別するためのIDを付ける
        return pTestWall;
    }
    case PATTERN_END: {
        break;
    }
    default:
        break;
    }

    return NULL;   // 指定のクラスが無い
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

    //拡張子の設定
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