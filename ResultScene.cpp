#include "ResultScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Timer.h"

static const int FPS = 60;

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_(-1), pText(nullptr)
{
    //GameObject* Timer = new GameObject();
}

//������
void ResultScene::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load("ReBack.png");
    assert(hPict_ >= 0);

    pText = new Text;
    pText->Initialize("charkodomo.png", 48, 48, 10);
}

//�X�V
void ResultScene::Update()
{
    if (Input::IsMouseButtonDown(0)) 
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

//�`��
void ResultScene::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);

    pText->SetScale(1.8f);
    pText->Draw(130, 450, sec);  //0:00:00
}

//�J��
void ResultScene::Release()
{
    pText->Release();
}