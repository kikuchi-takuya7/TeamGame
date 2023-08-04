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
				sos_Trans_.position_.x = std::stof(tmp);
				break;
			case 1:
				sos_Trans_.position_.y = std::stof(tmp);
				break;
			case 2:
				sos_Trans_.position_.z = std::stof(tmp);
				break;
			case 3:
				sos_Trans_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				sos_Trans_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				sos_Trans_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				sos_Trans_.scale_.x = std::stof(tmp);
				sos_Trans_.scale_.y = std::stof(tmp);
				sos_Trans_.scale_.z = std::stof(tmp);
				break;
				//���k�d�q���S�p�̃��[�h����R�[�h��`���B��ɏ������悤�ɏ����΍s����͂�
			case 7:
				Denshi_Trams_.position_.x = std::stof(tmp);
				break;
			case 8:
				Denshi_Trams_.position_.y = std::stof(tmp);
				break;
			case 9:
				Denshi_Trams_.position_.z = std::stof(tmp);
				break;
			case 10:
				Denshi_Trams_.rotate_.x = std::stof(tmp);
				break;
			case 11:
				Denshi_Trams_.rotate_.y = std::stof(tmp);
				break;
			case 12:
				Denshi_Trams_.rotate_.z = std::stof(tmp);
				break;
			case 13:
				Denshi_Trams_.scale_.x = std::stof(tmp);
				Denshi_Trams_.scale_.y = std::stof(tmp);
				Denshi_Trams_.scale_.z = std::stof(tmp);
				break;
			case 14:
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
	//Transform rogTransform_;

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
	Image::SetTransform(hsos_logo_, sos_Trans_);
	Image::Draw(hsos_logo_);

	Image::SetTransform(hdenshi_logo_, Denshi_Trams_);//���k�d�q���S�p��Transform�ϐ��ɕς���
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

		Setting_Transform(sos_Trans_, -1.0f, 1.0f, 365.0f, 5.0f, "SOS");
		//�����ɓ��k�d�q���S�p��Setting_Transform��`��
		Setting_Transform(Denshi_Trams_, -1.0f, 1.0f, 365.0f, 5.0f, "DENSHI");

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
		//sos���S�p�̃Z�[�u�͏���������A�����悤�ɓ��k�d�q�p�̃��S�̃Z�[�u������B���[�h�̏��ԂƓ����ɂȂ�悤�ɒ���
		float* SosSave[] = { &sos_Trans_.position_.x, &sos_Trans_.position_.y, &sos_Trans_.position_.z,
						  &sos_Trans_.rotate_.x, &sos_Trans_.rotate_.y, &sos_Trans_.rotate_.z,
						  &sos_Trans_.scale_.x , &tmp};

		float* DensiSave[] = { &Denshi_Trams_.position_.x, &Denshi_Trams_.position_.y, &Denshi_Trams_.position_.z,
						  & Denshi_Trams_.rotate_.x, & Denshi_Trams_.rotate_.y, & Denshi_Trams_.rotate_.z,
						  & Denshi_Trams_.scale_.x , &tmp };
		const int Sosize = sizeof(SosSave) / sizeof(SosSave[0]);
		const int Desize = sizeof(DensiSave) / sizeof(DensiSave[0]);
		
		std::string s[Sosize];
		std::string d[Desize];
		

		for (int i = 0; i < Sosize; i++) {
			s[i] = std::to_string(*SosSave[i]) + " ";
		}

		
		DWORD dwBytes = 0;  //�������݈ʒu

		for (int i = 0; i < Sosize; i++) {

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
