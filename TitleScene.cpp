#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

const LPCSTR fileName = "SaveFile\\TitleSaveData";

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hhaikei_(-1), hTitle_(-1),  hStart_(-1), hBrackStart_(-1), alpha_(0), changeLimit_(0),tmpLimit_(0), alphaFlag_(false), startFlag_(false)
{
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
}

//������
void TitleScene::Initialize()
{
	hFile_ = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_READ,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);

	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile_, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	ReadFile(
		hFile_,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j


	char* tmp = new char[fileSize];
	int c = 0, sw = 0;

	//�V�������[�h����f�[�^�𑝂₵�����ꍇ��case������₵�Ă��̕ϐ���tmp�̓��e��stof�Ȃ�œ����΂���
	for (DWORD i = 0; i < fileSize; i++) {

		if (data[i] == ' ') {
			switch (sw)
			{
			case 0:
				start_Transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				start_Transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				start_Transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				start_Transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				start_Transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				start_Transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				start_Transform_.scale_.x = std::stof(tmp);
				start_Transform_.scale_.y = std::stof(tmp);
				start_Transform_.scale_.z = std::stof(tmp);
				break;
			default:
				break;
			}
			sw++;
			c = 0;
			continue;
		}
		tmp[c] = data[i];
		c++;
	}
	delete[] tmp;
	delete[] data;

	CloseHandle(hFile_);

	

	//�w�i�摜�̃��[�h
	hhaikei_ = Image::Load("haikei.png");
	assert(hhaikei_ >= 0);

	hTitle_ = Image::Load("Title.png");
	assert(hTitle_ >= 0);

	title_Transform_.position_.y = 0.1f;

	titleMovingUp_ = true;       //�ŏ��͏�Ɉړ�
	titleMoveSpeed_ = 0.001f;    //�ړ����x

	hStart_ = Image::Load("Start.png");
	assert(hStart_ >= 0);

	hBrackStart_ = Image::Load("BrackStart.png");
	assert(hBrackStart_ >= 0);
}

//�X�V
void TitleScene::Update()
{
	//title�̈ʒu���X�V
	if (titleMovingUp_) {
		title_Transform_.position_.y += titleMoveSpeed_;
	}
	else {
		title_Transform_.position_.y -= titleMoveSpeed_;
	}
	
	//���͈̔͂Ŕ��]������
	if (title_Transform_.position_.y > 0.1f) {
		titleMovingUp_ = false;
	}
	else if (title_Transform_.position_.y < -0.1f) {
		titleMovingUp_ = true;
	}

	//START�̓_�ł��Ǘ�
	if (!startFlag_) {
		ChangeAlpha();
	}
	else {
		ChangeScene();
	}

	//�}�E�X�J�[�\���̈ʒu
	XMFLOAT3 mouse;
	mouse = Input::GetMousePosition();
	mouse.x -= 480;
	mouse.y -= 570;

	//�}�E�X�̏����ʒu������ŐF�X��₱���������̂ŁA�N���b�N�����͂��艟���Œǉ�
	if (mouse.x > 0 && mouse.y > 0 && mouse.x < 300 && mouse.y < 200 && startFlag_ == false) {
		alpha_ = 255;
		if (Input::IsMouseButtonDown(0)) {
			startFlag_ = true;
			alphaFlag_ = false;
		}
	}

	

	Image::SetAlpha(hStart_, alpha_);

}

//�`��
void TitleScene::Draw()
{

	Image::SetTransform(hhaikei_, transform_);
	Image::Draw(hhaikei_);

	Image::SetTransform(hTitle_, title_Transform_);
	Image::Draw(hTitle_);

	Image::SetTransform(hStart_, start_Transform_);
	Image::Draw(hStart_);

	Image::SetTransform(hBrackStart_, start_Transform_);
	//Image::Draw(hBrackStart_);

}

//�J��
void TitleScene::Release()
{
}

void TitleScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Title"))
	{
		//Setting_Transform(start_Transform_, -1, 1, 0, 10, "Title");
		
	}
	ImGui::End();

	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT)) {

		//Save_Transform_File(hFile_, fileName);

		hFile_ = CreateFile(
			fileName,                 //�t�@�C����
			GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
			0,                      //���L�i�Ȃ��j
			NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
			CREATE_ALWAYS,           //�쐬���@
			FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
			NULL);                  //�g�������i�Ȃ�


		float* save[] = { &start_Transform_.position_.x, &start_Transform_.position_.y, &start_Transform_.position_.z,
						  &start_Transform_.rotate_.x, &start_Transform_.rotate_.y, &start_Transform_.rotate_.z,
						  &start_Transform_.scale_.x };

		const int size = sizeof(save) / sizeof(save[0]);

		std::string s[size];


		for (int i = 0; i < size; i++) {
			s[i] = std::to_string(*save[i]) + " ";
		}


		DWORD dwBytes = 0;  //�������݈ʒu

		for (int i = 0; i < size; i++) {

			WriteFile(
				hFile_,                   //�t�@�C���n���h��
				s[i].c_str(),                  //�ۑ�����f�[�^�i������j
				(DWORD)strlen(s[i].c_str()),   //�������ޕ�����
				&dwBytes,                //�������񂾃T�C�Y������ϐ�
				NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

		}



		CloseHandle(hFile_);

	}
}

void TitleScene::ChangeAlpha()
{
	if (!alphaFlag_) {
		alpha_ += 3;
	}
	else {
		alpha_ -= 3;
	}

	if (alpha_ >= 255)
		alphaFlag_ = true;

	if (alpha_ <= 0)
		alphaFlag_ = false;
}

void TitleScene::ChangeScene()
{
	changeLimit_++;

	if (changeLimit_ % 30 == 1) {
		alphaFlag_ = false;
	}

	if (tmpLimit_ > 15)
		alphaFlag_ = true;

	if (alphaFlag_) {
		alpha_ = 255;
		tmpLimit_ = 0;
	}
	else {
		alpha_ = 0;
		tmpLimit_++;
	}
		
	if (changeLimit_ > 120) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}
