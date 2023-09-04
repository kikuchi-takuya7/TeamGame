#include "TestWall.h"
#include "Engine/Model.h"

//�R���X�g���N�^
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),objectID_('N'),isDelete_(false)
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
	if (ImGui::CollapsingHeader("TestWall"))
	{
		Setting_Transform(transform_, -100.0f, 100.0f, 365.0f, 5.0f, GetObjectName() + objectID_);

		if (ImGui::Button("Delete")) {
			isDelete_ = true;
		}

		if (isDelete_) {
			ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
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
