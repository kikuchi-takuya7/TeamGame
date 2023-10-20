#pragma once
#include "Engine/GameObject.h"
#include "PlayerState/PlayerState.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

private:

    enum PLAYERSTATE {
        IDLE = 0,
        MOVE,
        ACTION,
        ANIMATIOIN
    };

    enum ANIMATIONSTATE {
        APPLAUSE = 0,//拍手
        BOW,//お辞儀
        NONE
    };

    PLAYERSTATE currentPlayerState_;
    PLAYERSTATE nextPlayerState_;

    ANIMATIONSTATE currentAnimationState_;
    ANIMATIONSTATE nextAnimationState_;

    int hModel_;

private:

    //stateを変更
    void ChangePlayerState(PLAYERSTATE nextState);

    //State毎の初期化と解放処理
    void OnEnterPlayerState(PLAYERSTATE state);
    void OnLeavePlayerState(PLAYERSTATE state);

    //animationstateを変更
    void ChangeAnimationState(ANIMATIONSTATE nextState);

    //animationState毎の初期化と解放処理
    void OnEnterAnimationState(ANIMATIONSTATE state);
    void OnLeaveAnimationState(ANIMATIONSTATE state);


    void Idle_Update();
    void Move_Update();
    void Move_Player();
    void Move_Camera();
    void Action_Update();
    void Animation_Update();
};