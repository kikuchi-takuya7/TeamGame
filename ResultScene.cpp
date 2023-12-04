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
}

//������
void ResultScene::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load("ReBack.png");
    assert(hPict_ >= 0);

    pText = new Text;
    pText->Initialize("charkodomo.png", 48, 48, 10);

    seconds = sec % 60;
    minuts = sec / 60;
   
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
    pText->Draw(210, 500,m);  
    pText->Draw(260, 500, ":");  
    pText->Draw(330, 500,s);  
    
}

//�J��
void ResultScene::Release()
{
    pText->Release();
}