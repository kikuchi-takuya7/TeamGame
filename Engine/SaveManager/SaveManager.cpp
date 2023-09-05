#include "SaveManager.h"
#include <iostream>
#include "../json-develop/include/nlohmann/json.hpp"
#include "../../TestWall.h"
#include <fstream>

using json = nlohmann::json;
using string = std::string;


//コンストラクタ
SaveManager::SaveManager(GameObject* parent)
    :GameObject(parent, "SaveManager")
{
}

//デストラクタ
SaveManager::~SaveManager()
{
}

//初期化
void SaveManager::Initialize()
{

}

//更新
void SaveManager::Update()
{

}

void SaveManager::Draw()
{
}

//開放
void SaveManager::Release()
{
    //m_SaveObjctList_.clear();
}

void SaveManager::Save(std::string fileName,std::list<GameObject*> list)
{

    int listSize = list.size();
        
    //ファイル作成の準備
    string prevPath = "SaveFile/";
    string filename = fileName;
    string Extension = ".json";
    filename = prevPath + filename + Extension;

    //ファイルを開く
    std::ofstream writing_file;
    writing_file.open(filename, std::ios::out);

    for (auto itr = list.begin(); itr != list.end();itr++) {

        //要素が空のjson変数を作る
        

        XMFLOAT3 pos = (*itr)->GetPosition();
        XMFLOAT3 rot = (*itr)->GetRotate();
        XMFLOAT3 sca = (*itr)->GetScale();

        float arr[9] = { pos.x,pos.y,pos.z,
                         rot.x,rot.y,rot.z,
                         sca.x,sca.y,sca.z };

        json m_json = {
                {"objectName",(*itr)->GetObjectName()},
                {"Transform",arr},
                {"objectID",(*itr)->GetobjectID()}
        };

        writing_file << m_json.dump() << std::endl;

    }
        
    writing_file.close();
}

void SaveManager::AddSaveObj(GameObject* obj)
{
    //m_SaveObjctList_.push_back(obj);
}

void SaveManager::Load(std::string fileName)
{

    //読み込みに失敗した場合はエラーを表示する
    std::ifstream ifs(fileName.c_str());

    //eofが上手く使えないからファイルの行数分だけ先にいただく
    int fileLine = 0;

    //読み込めなかったら返す
    if (!ifs)
        return;

    while (true)
    {
        string line;
        // 1行読み取る。
        getline(ifs, line);
        fileLine++;

        // ファイルが終端まで来たらbreak 
        if (ifs.eof())
            break;
    }

    //一回ファイル読み込みを回したから一旦閉じる
    ifs.close();

    //入力の時に改行してるから一つ減らす
    fileLine--;

    ifs.open(fileName.c_str(), std::ios::in);

    //ファイルのラインの数だけ回す
    for (int i = 0; i < fileLine;i++) {
        json m_json;
        ifs >> m_json;

        GameObject* object = CreateObj(m_json["objectName"]);
            
        //読み込んだデータをオブジェクトに入れる
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

        char ID = m_json["objectID"];

        object->SetobjectID(m_json["objectID"]);
    }


    ifs.close();
}

GameObject* SaveManager::CreateObj(std::string className)
{

    if (className == "TestWall") {
        TestWall* Player = Instantiate<TestWall>(this->GetParent());
        return Player;
    }

    return NULL;   // 指定のクラスが無い
}

