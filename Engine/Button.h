#pragma once
#include "GameObject.h"

enum NEXTSCENE {
	NONE = -1,
	SELECT
};

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	

	void Initialize() override;
	void Update() override;
	void Draw() override;
	
	bool Finished(); // Button���I�������true

	//�e��Z�b�g�֐�
	void SetImage(std::string normal);
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void SetAlphaNormal(float alpha);//�ʏ펞�\������摜�@
	void SetAlphaPush(float alpha);//������Ă���Œ��ɕ\������摜
	void SetNextScene(NEXTSCENE next);
	void SetIsFlash(bool flash);
	
	//pushed��ς���
	void Push(bool pushed);

	//�}�E�X���摜�͈͓̔���
	bool MouseInArea(XMFLOAT3 mousePos);
	
	
private:

	void ChangeAlpha();
	void ChangeScene();

	//�摜�ԍ�
	int hImage_;

	//�ꉞ2�ڂ̉摜�ԍ�
	int hPush_;
	
	//����͉摜�̏�Ƀ}�E�X�����邩
	bool pushed_;

	//���S�ƃT�C�Y
	XMFLOAT3 center_;
	XMFLOAT3 size_;

	//�摜�̓_�łɊւ���ϐ�
	int alpha_;//����Start�̓����x
	int changeLimit_;
	int tmpLimit_;
	bool alphaFlag_;
	bool startFlag_;//�N���b�N���ꂽ���̃t���O

	bool isFlash_;//�ҋ@��Ԃœ_�ł����邩�ǂ����Btrue�Ȃ�_��

	NEXTSCENE nextScene_;
};