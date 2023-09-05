#include "TestWall.h"
#include "Engine/Model.h"

//コンストラクタ
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),isDelete_(false),isClose_(false)
{
}

//デストラクタ
TestWall::~TestWall()
{
}

//初期化
void TestWall::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Map/testWall.fbx");
    assert(hModel_ >= 0);
}

//更新
void TestWall::Update()
{
}

//描画
void TestWall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TestWall::Release()
{
}

void TestWall::Imgui_Window()
{

	ImGui::Begin("DataWindow");
	Data_Edit();

}

void TestWall::Data_Edit()
{
	std::string str = GetObjectName() + GetObjectID();
	const char* windowName = str.c_str();

	if (ImGui::CollapsingHeader(windowName))
	{
		Setting_Transform(transform_, -100.0f, 100.0f, 365.0f, 5.0f, GetObjectName() + GetObjectID());

		std::string s = "delete";
		str = s + GetObjectID();
		const char* deleteName = str.c_str();
		if (ImGui::Button(deleteName)) {
			isDelete_ = true;
		}

		if (isDelete_) {
			ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
			ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
			std::string tmp = "OK?";
			tmp = tmp + s + GetObjectID();
			const char* deleteName = tmp.c_str();
			ImGui::Begin(deleteName, &isDelete_);
			if (ImGui::Button(deleteName)) {

				KillMe();
			}
			ImGui::End();	
		}
	}
	ImGui::End();
}

bool TestWall::IsKillCheck()
{
	return isDelete_;
}

void TestWall::DeleteMe()
{
	isDelete_ = true;
}

void TestWall::DeleteStop()
{
	isDelete_ = false;
}
