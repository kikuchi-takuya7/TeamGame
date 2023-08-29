#include "MapData.h"
#include "../Model.h"
#include <vector>
#include <string>
#include <stdexcept>

//ディレクトリ内の指定した識別子のファイルネームを獲得
std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

//コンストラクタ
MapData::MapData(GameObject* parent)
	: GameObject(parent, "MapData"),changeModel_(0)
{

    
}

//初期化
void MapData::Initialize()
{
    fileName_ = get_file_path_in_dir("./Map/", "fbx");
    
    //fileNameの個数分の要素数を確保
    hModel_.assign(fileName_.size(),-1);


    for (int i = 0; i < hModel_.size(); i++) {
        std::string dir = "Map/";
        hModel_.at(i) = Model::Load(dir + fileName_.at(i));
        assert(hModel_.at(i) >= 0);
    }
    
}

//更新
void MapData::Update()
{
}

//描画
void MapData::Draw()
{
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
        if (ImGui::TreeNode("Object")){
            for (int i = 0; i < fileName_.size(); i++) {
                ImGui::RadioButton(fileName_.at(i).c_str(), &changeModel_, i);
            }

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
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