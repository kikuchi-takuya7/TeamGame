#include "TestWall.h"
#include "Engine/Model.h"

//コンストラクタ
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),objectID_('N'),isDelete_(false)
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
	if (ImGui::CollapsingHeader("TestWall"))
	{
		Setting_Transform(transform_, -100.0f, 100.0f, 365.0f, 5.0f, GetObjectName() + objectID_);

		if (ImGui::Button("Delete")) {
			isDelete_ = true;
		}

		if (isDelete_) {
			ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
			ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Once);
			ImGui::Begin("DeleteOk?");
			if (ImGui::Button("Delete")) {
				KillMe();
			}
			ImGui::End();
		}

	}
	ImGui::End();

}
