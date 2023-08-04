#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

const LPCSTR fileName = "SaveFile\\SplashSaveData";

//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hdenshi_logo_(-1), hsos_logo_(-1), alpha_(255), alphaFlag_(false)
{
}

//�f�X�g���N�^
SplashScene::~SplashScene()
{
}

//������
void SplashScene::Initialize()
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
				transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				transform_.scale_.x = std::stof(tmp);
				transform_.scale_.y = std::stof(tmp);
				transform_.scale_.z = std::stof(tmp);
				break;
			case 7:
				alpha_ = std::stoi(tmp);
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

	//�N���X�ϐ��ɐ錾 
	Transform rogTransform_;

	//Setting_Transform(rogTransform_, );//-0.413,0,0,0,1.0f,255
	
	//sos�摜�f�[�^�̃��[�h
	hsos_logo_ = Image::Load("sos_logo.png");
	assert(hsos_logo_ >= 0);
	//���k�d�q�摜�f�[�^�̃��[�h
	hdenshi_logo_ = Image::Load("Tohokudenshi_logo.png");
	assert(hdenshi_logo_ >= 0);
}

//�X�V
void SplashScene::Update()
{

#if 0
	if (alpha_ >= 300)//������Ƃ��������c��
		alphaFlag_ = true;

	if(alphaFlag_ == false)
		alpha_ += 3;

	if (alphaFlag_ == true)
		alpha_ -= 3;

	if (alpha_ < 0) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
#endif

	Image::SetAlpha(hsos_logo_, alpha_);
	Image::SetAlpha(hdenshi_logo_, alpha_);


}

//�`��
void SplashScene::Draw()
{
	Image::SetTransform(hsos_logo_, transform_);
	Image::Draw(hsos_logo_);

	Image::SetTransform(hdenshi_logo_, transform_);
	Image::Draw(hdenshi_logo_);

	

	
}

//�J��
void SplashScene::Release()
{
}

void SplashScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Splash"))
	{

		Setting_Transform(transform_, -1.0f, 1.0f, 365.0f, 5.0f, "Splash");
		ImGui::SliderInt("alpha", &alpha_, 0, 255);
	}
	ImGui::End();


	if (Input::IsKey(DIK_S) && Input::IsKey(DIK_LSHIFT) || Input::IsKey(DIK_S) && Input::IsKey(DIK_RSHIFT) ) {

		//Save_Transform_File(hFile_, fileName);
		
		hFile_ = CreateFile(
			fileName,                 //�t�@�C����
			GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
			0,                      //���L�i�Ȃ��j
			NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
			CREATE_ALWAYS,           //�쐬���@
			FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
			NULL);                  //�g�������i�Ȃ�

		float tmp = alpha_;

		//�V�����ϐ����Z�[�u�������ꍇ�͂����̌��ɕϐ�������t���ē���邾���B���[�h���Y�ꂸ��
		float* save[] = { &transform_.position_.x, &transform_.position_.y, &transform_.position_.z,
						  &transform_.rotate_.x, &transform_.rotate_.y, &transform_.rotate_.z,
						  &transform_.scale_.x , &tmp};
		
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
