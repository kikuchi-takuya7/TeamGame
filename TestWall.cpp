#include "TestWall.h"
#include "Engine/Model.h"

//�R���X�g���N�^
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),objectID_('N')
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
	}
	ImGui::End();

}
