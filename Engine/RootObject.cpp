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
	ImGui::SetNextWindowPos(ImVec2(900, 10), ImGuiCond_Once);//, ImGuiCond_FirstUseEver‚±‚ê‚ğ•t‚¯‚é‚Æ‰‚ß‚ÄÀs‚µ‚½‚Æ‚«‚¾‚¯‚±‚Ì‘å‚«‚³‚Éİ’è‚³‚ê‚ÄB‚»‚êˆÈ~‚Íimgui.ini‚É•Û‘¶‚³‚ê‚é
	ImGui::SetNextWindowSize(ImVec2(400, 1000), ImGuiCond_Once);
	ImGui::Begin("DataWindow");
	ImGui::Text("Shift + S: DataSave");
	ImGui::End();
}
