#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("goburin.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{

    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 2.0f;
    }

    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 2.0f;
    }

    //出力のところに変数がどうなってるか表示
    Debug::Log(transform_.position_.x, true);

    //洗車の現在の位置をベクトル型に変換
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1フレームの移動ベクトル
    XMVECTOR move = { 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m

    //transform.rotate_.y度回転させる行列を作成
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //移動ベクトルを変形 (洗車と同じ向きに回転) させる
    move = XMVector3TransformCoord(move, rotY);

    //Wキーが押されたら移動
    if (Input::IsKey(DIK_W)) {
        //移動
        pos += move;

        //現在地をベクトルからいつものtransform.positionに戻す
        XMStoreFloat3(&transform_.position_, pos);

    }

    if (Input::IsKey(DIK_S)) {

        pos -= move;

        XMStoreFloat3(&transform_.position_, pos);

    }

    XMFLOAT3 camPos;

    camPos = { transform_.position_ };
    Camera::SetPosition(camPos);
    XMFLOAT3 man;
    XMStoreFloat3(&man, pos + move);
    Camera::SetTarget(man);
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}