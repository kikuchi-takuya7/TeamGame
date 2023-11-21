#include "ResultScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_(-1), pText(nullptr)
{
}

//������
void ResultScene::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load("ReBack.png");
    assert(hPict_ >= 0);

    //Text::Initialize("char_kodomo.png", 64, 64, 16);
    pText = new Text;
    pText->Initialize("charkodomo.png", 48, 48, 10);

}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
    pText->Draw(30, 30, "0:26:95");
    //Text.cpp��67��scale�������H
}

//�J��
void ResultScene::Release()
{
    pText->Release();
}