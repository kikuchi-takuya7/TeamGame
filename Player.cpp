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
    //hModel_ = Model::Load("goburin.fbx");
    hModel_ = Model::Load("taikianime.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = -2;

    Model::SetAnimFrame(hModel_, 0, 120, 1);

    
}

//更新
void Player::Update()
{

    Move_Character();
    Move_Camera();
    

    /*XMFLOAT3 mousePos = Input::GetMousePosition();

    mousePos.x += Direct3D::screenWidth_ / 2;
    mousePos.y += Direct3D::screenHeight_ / 2;

    transform_.rotate_.x += mousePos.x;
    transform_.rotate_.y += mousePos.y;*/

    //Input::SetMousePosition(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);

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

void Player::Move_Character()
{
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    if (Input::IsKey(DIK_A))
    {
        fMove.x = -0.1f;
    }
    if (Input::IsKey(DIK_D))
    {
        fMove.x = 0.1f;
    }
    if (Input::IsKey(DIK_W))
    {
        fMove.z = 0.1f;
    }
    if (Input::IsKey(DIK_S))
    {
        fMove.z = -0.1f;
    }

    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMLoadFloat3(&fMove);
    //vMove = XMVector3Normalize(vMove);


    XMStoreFloat3(&fMove, vMove);

    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;


    
}

void Player::Move_Camera()
{

    //transform.rotate_.y度回転させる行列を作成
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //現在の位置をベクトル型に変換
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //カメラの位置は常にポジションの後ろ
    XMVECTOR vCam = { 0,5,-9,0 };
    vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    Camera::SetPosition(pos + vCam);


    /////////////////////////////////////////////////////////////////
    // ⓵　現在のカメラの注視点と視点を使って、XZ平面上での、
    //      注視点から視点までのベクトル(toCameraPosXZ)と長さ(toCameraPosXZLen)を求める。
    /////////////////////////////////////////////////////////////////
    XMFLOAT3 camPos = Camera::GetPosition();
    XMFLOAT3 camTar = Camera::GetTarget();
    XMVECTOR toCameraPosXZ = camPos - camTar;

    float height = XMVectorGetY(toCameraPosXZ);      //視点へのY方向の高さは、後で使うのでバックアップしておく。
    toCameraPosXZ = XMVectorSetY(toCameraPosXZ, 0);  //XZ平面にするので、Yは0にする。
    float toCameraPosXZLen = Length(toCameraPosXZ); //XZ平面上での視点と注視点の距離を求める。
    XMVECTOR toCamPosNormalize = XMVector3Normalize(toCameraPosXZ);          //単位ベクトル化。
    
    /////////////////////////////////////////////////////////////////
    // ⓶　新しい注視点をアクターの座標から決める。
    /////////////////////////////////////////////////////////////////
    XMVECTOR target = XMLoadFloat3(&transform_.position_);
    target += XMVectorSetY(target, 5.0f);
    target += XMVectorSetX(target, -5.0f);
    XMFLOAT3 floatTarget = transform_.position_;
    floatTarget.y += 5.0f;
    floatTarget.z += -5.0f;

    /////////////////////////////////////////////////////////////////
    // ⓷　新しい注視点と現在のカメラの視点を使って、XZ平面上での、
    //     注視点から視点までのベクトル(toNewCameraPos)を求める。
    /////////////////////////////////////////////////////////////////
    XMVECTOR toNewCameraPos = transform_.position_ - floatTarget; //新しい注視点からカメラの始点へ向かうベクトルを求める。
    toNewCameraPos = XMVectorSetY(toNewCameraPos, 0.0f);              //XZ平面にするので、Yは0にする。
    XMVECTOR toNewCamPosNormalize = XMVector3Normalize(toNewCameraPos);         //単位ベクトル化。

    /////////////////////////////////////////////////////////////////
    // ⓸　１と２と３で求めた情報を使って、新しい視点を決定する。
    /////////////////////////////////////////////////////////////////
    //ちょっとづつ追尾。
    float weight = 0.7f;  //このウェイトの値は0.0～1.0の値をとる。1.0に近づくほど追尾が強くなる。
    toNewCamPosNormalize = toNewCamPosNormalize * weight + toCameraPosXZ * (1.0f - weight);
    toNewCamPosNormalize = XMVector3Normalize(toNewCamPosNormalize);
    toNewCamPosNormalize *= toCameraPosXZLen;
    toNewCamPosNormalize = XMVectorSetY(toNewCamPosNormalize, height);              //高さを戻す。
    XMVECTOR newCamPos = target + toCamPosNormalize;  //これで新しい視点が決定。

    /////////////////////////////////////////////////////////////////
    // ⓹　視点と注視点をカメラに設定して終わり。
    /////////////////////////////////////////////////////////////////
    Camera::SetPosition(newCamPos);
    Camera::SetTarget(floatTarget);

}
