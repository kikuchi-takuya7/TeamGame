#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Splash_Frame.h"


const LPCSTR fileName = "SaveFile\\SplashSaveData";

//Splash_Frame* Splashframe;

namespace {
	float startX;//�ړ��J�nX���W
	float endX;//�ړ��I��X���W
	float totalTime;//�ړ�����
	float currentTime;//���݂̎���
	int seq_line;//�����s���Ă���s
	float seq_time;//�V�[�P���X�����s���Ă��鎞��
	enum ACT {//��邱�Ƃ��R�}���h��
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct  Sequence {
		float time;//����
		ACT action;//��邱��
		float param;//�K�v�Ȓl
	};
	//����������Ă���
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN,-5.0f},//�X���C�h�C��
		{3.0f,A_WAIT,0.0f},//�P�b�҂��Ă���
		{4.0f,A_SLIDEOUT,5.0f},//�X���C�h�A�E�g
		{5.0f,A_END,0.0f}//�����ŏ�����
	};
	ACT currentAction;
	bool canMove;
};

//�R���X�g���N�^
SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"), /*hdenshi_logo_(-1), hsos_logo_(-1),*/ alpha_(0), alphaFlag_(false), countDown_(false), limitTmp_(2.0), limit_(0), time_(0)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
}

//�f�X�g���N�^
SplashScene::~SplashScene()
{
}

//������
void SplashScene::Initialize()
{
	hImage_ = Image::Load("sos_logo_b.png");
	assert(hImage_ >= 0);
	startX = 5.0f;
	endX = 0;
	totalTime = 8.0f;
	currentTime = 0.0f;
	transform_.position_.x = startX;  // ����X���W��ݒ�

	
	heye_ = Image::Load("sos_logo_a.png");
	assert(heye_ >= 0);
	hframe_ = Image::Load("sos_logo_e.png");
	assert(hframe_ >= 0);

	
	
}
float easeInCubic(float x) {
	return x * x * x;
}


//�X�V
void SplashScene::Update()
{
	seq_time += 1.0f / 60.0f;//���Ԃ�i�߂�
	if (seq_time >= tbl[seq_line + 1].time) {//���̍s�����s����
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDEOUT:

			startX = transform_.position_.x;
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;

			//���S������
			Image::SetAlpha(heye_, 0);
			Image::SetAlpha(hframe_, 0);
			break;

		}
		//���̍s�̎��s������

	}
	currentTime += 1.0f / 60.0f;//�P�t���[�����̎��Ԃ�i�܂���
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//������0.0�`1.0�͈̔͂ɂ���
	float val = easeInCubic(t);
	transform_.position_.x = val * (endX - startX) + startX;

	

}

//�`��
void SplashScene::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);

	Image::SetTransform(heye_, heye_Trans_);
	Image::Draw(heye_);

	Image::SetTransform(hframe_, hframe_Trans_);
	Image::Draw(hframe_);

	

	
	//Image::SetTransform(hdenshi_logo_, Denshi_Trams_);//���k�d�q���S�p��Transform�ϐ��ɕς���
	//Image::Draw(hdenshi_logo_);

	

	
}
bool SplashScene::Finished()
{
	return seq_line >= sizeof(tbl) / sizeof(tbl[0]) - 1;
	return canMove;
	if (currentTime >= totalTime)
		return true;
	return false;
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

}



