#include "RootObject.h"
#include "SceneManager.h"
#include "Input.h"


RootObject::RootObject():
	GameObject(nullptr, "RootObject"), conf_(false)
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

	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT)) {
		conf_ = true;
	}

	ImGui::SetNextWindowPos(ImVec2(900, 10), ImGuiCond_Once);//, ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
	ImGui::SetNextWindowSize(ImVec2(400, 1000), ImGuiCond_Once);
	ImGui::Begin("DataWindow");
	ImGui::Text("Shift + S: DataSave");

	if (conf_) {
		ImGui::Begin("SAVE OK");
		ImGui::Text("You pushed Shift + S");
		if (ImGui::Button("Close me"))
			conf_ = false;
		ImGui::End();
	}
	ImGui::End();
}
