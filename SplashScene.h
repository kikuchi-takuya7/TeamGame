#pragma once
#include "Engine/GameObject.h"


class SplashScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	SplashScene(GameObject* parent);
	~SplashScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Imgui_Window();
	//void Imgui_Window() override;
	bool Finished();//Ready���I�������true
	
	
private:
	int hImage_;//���S�{��
	int heye_;//���S�̖�
	int hframe_;//���S�̘g
	
	int hsos_logo_; //sos���S�摜�ԍ�
	int hdenshi_logo_; //���k�d�q���S�摜�ԍ�

	Transform sos_Trans_; //sos���S�摜��Transform
	Transform Denshi_Trams_; //���k�d�q���S��Transform

	Transform heye_Trans_; //sos���S�摜��Transform
	Transform hframe_Trans_; //���k�d�q���S��Transform

	HANDLE hFile_;        //�t�@�C���̃n���h��
	int alpha_;
	bool alphaFlag_;
	bool countDown_;
	float limitTmp_;//��N�������߂鉽�b�Ƃǂ܂邩���Ă��
	int limit_;//�t���[���ɕϊ�����
	int time_;
	
};


