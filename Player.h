#pragma once
#include "Engine/GameObject.h"
#include "PlayerState/PlayerState.h"

//���������Ǘ�����N���X
class Player : public GameObject
{

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:

    enum PLAYERSTATE {
        IDLE = 0,
        MOVE,
        ACTION,
        ANIMATIOIN
    };

    enum ANIMATIONSTATE {
        APPLAUSE = 0,//����
        BOW,//�����V
        NONE
    };

    PLAYERSTATE currentPlayerState_;
    PLAYERSTATE nextPlayerState_;

    ANIMATIONSTATE currentAnimationState_;
    ANIMATIONSTATE nextAnimationState_;

    int hModel_;

private:

    //state��ύX
    void ChangePlayerState(PLAYERSTATE nextState);

    //State���̏������Ɖ������
    void OnEnterPlayerState(PLAYERSTATE state);
    void OnLeavePlayerState(PLAYERSTATE state);

    //animationstate��ύX
    void ChangeAnimationState(ANIMATIONSTATE nextState);

    //animationState���̏������Ɖ������
    void OnEnterAnimationState(ANIMATIONSTATE state);
    void OnLeaveAnimationState(ANIMATIONSTATE state);


    void Idle_Update();
    void Move_Update();
    void Move_Player();
    void Move_Camera();
    void Action_Update();
    void Animation_Update();
};