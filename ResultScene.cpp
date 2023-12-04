#include "ResultScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Timer.h"
#include <string>

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

    s = sec % 60;
    m = sec / 60;
    //std::string sam = (std::string)s;
    //std::string mam = m;

   
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
    pText->Draw(210, 500,m);  //0:00:00
    pText->Draw(260, 500, ":");  //0:00:00
    pText->Draw(330, 500,s);  //0:00:00
    
}

//�J��
void ResultScene::Release()
{
    pText->Release();
}