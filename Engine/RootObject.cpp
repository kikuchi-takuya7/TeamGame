#include "RootObject.h"
#include "SceneManager.h"


RootObject::RootObject():
	GameObject(nullptr, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}

void RootObject::Imgui_Window()
{
	ImGui::SetNextWindowPos(ImVec2(900, 10), ImGuiCond_Once);//, ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
	ImGui::SetNextWindowSize(ImVec2(400, 1000), ImGuiCond_Once);
	ImGui::Begin("DataWindow");
	ImGui::Text("Shift + S: DataSave");
	ImGui::End();
}
