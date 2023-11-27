#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Video.h"





//const LPCSTR fileName = "SaveFile\\SplashSaveData";
Video video;


//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), hdenshi_logo_(-1), hsos_logo_(-1), alpha_(0), alphaFlag_(false), countDown_(false), limitTmp_(2.0), limit_(0), time_(0)
{
}

//�f�X�g���N�^
SplashScene::~SplashScene()
{
}



//������
void SplashScene::Initialize()
{

	video.Initialize();


 //    video.InitializeVideo();
	///* video.LoadFile();*/
	// const wchar_t* filePath = L"TouhokuDenshi_splash.avi";
	// video.LoadFile(filePath);
	// 


	// video.Play();
	// video.WaitForCompletion();
	 


}


//�X�V
void SplashScene::Update()
{


}

//�`��
void SplashScene::Draw()
{

}

//�J��
void SplashScene::Release()
{
	
}

void SplashScene::Imgui_Window()
{
	
}

/*void SplashScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Splash"))
	{

		Setting_Transform(sos_Trans_, -1.0f, 1.0f, 365.0f, 5.0f, "SOS");
		//�����ɓ��k�d�q���S�p��Setting_Transform��`��
		Setting_Transform(Denshi_Trams_, -1.0f, 1.0f, 365.0f, 5.0f, "DENSHI");

		ImGui::SliderInt("Startalpha", &alpha_, 0, 255);

		ImGui::SliderFloat("StaySecond", &limitTmp_, 0, 5);

		if (ImGui::Button("Start")) {
			//Initialize();
			Enter();
		}
			
			//updateStop_ = false;
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
		float* save[] = { &sos_Trans_.position_.x, &sos_Trans_.position_.y, &sos_Trans_.position_.z,
						  &sos_Trans_.rotate_.x, &sos_Trans_.rotate_.y, &sos_Trans_.rotate_.z,
						  &sos_Trans_.scale_.x ,
						  &Denshi_Trams_.position_.x,& Denshi_Trams_.position_.y,& Denshi_Trams_.position_.z,
						  &Denshi_Trams_.rotate_.x,& Denshi_Trams_.rotate_.y,& Denshi_Trams_.rotate_.z,
						  &Denshi_Trams_.scale_.x, &tmp, &limitTmp_};

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

}*/
