#include "TestWall.h"
#include "Engine/Model.h"

//�R���X�g���N�^
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),isDelete_(false),isClose_(false)
{
}

//�f�X�g���N�^
TestWall::~TestWall()
{
}

//������
void TestWall::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Map/testWall.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void TestWall::Update()
{
}

//�`��
void TestWall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
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
			ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
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
