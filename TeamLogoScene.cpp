#include "TeamLogoScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
TeamLogoScene::TeamLogoScene(GameObject* parent)
	: GameObject(parent, "TeamLogoScene"),
    hNetWork_a1_(-1),hNetWork_aR_(-1), hNetWork_aG_(-1), hNetWork_aB_(-1), hNetWork_b_(-1),
    hCircle2_a_(-1), hCircle2_b_(-1)
{
}

//������
void TeamLogoScene::Initialize()
{   
    //�摜�f�[�^�̃��[�h
    hNetWork_a1_ = Image::Load("./tdlogo/network_a.png");
    assert(hNetWork_a1_ >= 0);

    hNetWork_aR_ = Image::Load("./tdlogo/network_aR.png");
    assert(hNetWork_aR_ >= 0);

    hNetWork_aG_ = Image::Load("./tdlogo/network_aG.png");
    assert(hNetWork_aG_ >= 0);

    hNetWork_aB_ = Image::Load("./tdlogo/network_aB.png");
    assert(hNetWork_aB_ >= 0);

    hNetWork_b_ = Image::Load("./tdlogo/network_b.png");
    assert(hNetWork_b_ >= 0);

    hCircle2_a_ = Image::Load("./tdlogo/circle2_a.png");
    assert(hCircle2_a_ >= 0);
    
    hCircle2_b_ = Image::Load("./tdlogo/circle2_b.png");
    assert(hCircle2_b_ >= 0);

    netA1.position_.x = 0.145f;
    netAR.position_.x = 0.145f;
    netAG.position_.x = -0.1;
    netAB.position_.x = -0.1;

    Image::SetAlpha(hNetWork_a1_, 150);
    Image::SetAlpha(hNetWork_aR_, 150);
    Image::SetAlpha(hNetWork_aG_, 150);
    Image::SetAlpha(hNetWork_aB_, 150);
    Image::SetAlpha(hNetWork_b_, 0);

    Image::SetAlpha(hCircle2_a_, 0);
    Image::SetAlpha(hCircle2_b_, 0);
}

//�X�V
void TeamLogoScene::Update()
{ 
    switch (TmTime)
    {
    case START:
        // �^�C�~���O������ɉ����ē����x��ύX����
        alphaValue += alphaIncrement;

        // �����x�����͈̔͂𒴂����ꍇ�A�ω��ʂ𔽓]������
        if (alphaValue <= 0 || alphaValue >= 255) {
            alphaIncrement *= -1;
        }


        // �����x��ύX������ASetAlpha �֐����Ăяo���Ď��ۂ̓����x��ݒ肷��
        Image::SetAlpha(hNetWork_a1_, alphaValue);
        Image::SetAlpha(hNetWork_aR_, alphaValue);
        Image::SetAlpha(hNetWork_aG_, alphaValue);
        Image::SetAlpha(hNetWork_aB_, alphaValue);

        
        netA1.position_.x -= 0.001f;
        
        if (netAR.position_.x >= 0.045f)
            netAR.position_.x -= 0.003f;

        if (netAB.position_.x <= 0.045f)
            netAB.position_.x += 0.003f;

        if(netAG.position_.x <= 0.045f)
            netAG.position_.x += 0.004f;
       
        if (netA1.position_.x <= 0.045f)
        {
            netA1.position_.x = 0.045f;
            Image::SetAlpha(hNetWork_a1_, 150);
            Image::SetAlpha(hNetWork_aR_, 0);
            Image::SetAlpha(hNetWork_aG_, 0);
            Image::SetAlpha(hNetWork_aB_, 0);
            TmTime = FLASH;
        }
        break;

    case FLASH:
        // �^�C�~���O������ɉ����ē����x��ύX����
        alphaValue += alphaIncrement;

        // �����x�����͈̔͂𒴂����ꍇ�A�ω��ʂ𔽓]������
        if (alphaValue <= 0 || alphaValue >= 255) {
            alphaIncrement *= -1; 
        }
        else
        {
            count++;
        }
      
      
        if(count < 20)
        {
            Image::SetAlpha(hCircle2_a_, alphaValue);
        }
        else
        {
            Image::SetAlpha(hCircle2_a_, 0);
            flag = true;
        }

        if (flag)
        {
            if (count < 50)
            {
                Image::SetAlpha(hCircle2_b_, alphaValue);
            }
            else
            {
                Image::SetAlpha(hCircle2_b_, 0);
                Image::SetAlpha(hNetWork_a1_, 0);
                TmTime = FINISH; 
            }
        }       
        break;

    case FINISH:
        // �^�C�~���O������ɉ����ē����x��ύX����
        
        if(flagFin)
        {
            alphaValue += alphaIncrementFin;
            if (alphaValue <= 0 || alphaValue >= 255) {
                alphaIncrementFin *= -1;
            }
            else
            {
                count++;
            }

            Image::SetAlpha(hNetWork_b_, alphaValue);
        }

        if (alphaValue >= 255 && count > 60)
        {
            Image::SetAlpha(hNetWork_b_, 255);
            flagFin = false;
            ECount++;
            if(ECount > 100)
                TmTime = ERASE;
        }
        

        break;

    case ERASE:
        alphaValue += alphaIncrementFin;

        if (alphaValue <= 0 || alphaValue >= 255) {
            alphaIncrementFin *= -1;
        }
        else
        {
            count++;
        }

        if (alphaValue <= 0)
        {
            Image::SetAlpha(hNetWork_b_, 0);
            TmTime = END;
        }
        break;

    case END:
        break;
    }
    
}

//�`��
void TeamLogoScene::Draw()
{
    Image::SetTransform(hNetWork_a1_, netA1);
    Image::Draw(hNetWork_a1_);
   
    Image::SetTransform(hNetWork_aR_, netAR);
    Image::Draw(hNetWork_aR_);
    
    Image::SetTransform(hNetWork_aG_, netAG);
    Image::Draw(hNetWork_aG_);
    
    Image::SetTransform(hNetWork_aB_, netAB);
    Image::Draw(hNetWork_aB_);
    
    Image::SetTransform(hNetWork_b_, transform_);
    Image::Draw(hNetWork_b_);

    Image::SetTransform(hCircle2_a_, transform_);
    Image::Draw(hCircle2_a_);

    Image::SetTransform(hCircle2_b_, transform_);
    Image::Draw(hCircle2_b_);
   
}

//�J��
void TeamLogoScene::Release()
{
}