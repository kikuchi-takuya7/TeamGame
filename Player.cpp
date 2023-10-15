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
    hModel_ = Model::Load("taikianime.fbx");
    assert(hModel_ >= 0);

    transform_.rotate_.y = 180;

    Model::SetAnimFrame(hModel_, 0, 120, 1);
}

//更新
void Player::Update()
{

#if 1

    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= 2.0f;
    }

    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += 2.0f;
    }

    ////出力のところに変数がどうなってるか表示
    //Debug::Log(transform_.position_.x, true);

    ////洗車の現在の位置をベクトル型に変換
    //XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    ////1フレームの移動ベクトル
    //XMVECTOR move = { 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m

    ////transform.rotate_.y度回転させる行列を作成
    //XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    ////移動ベクトルを変形 (洗車と同じ向きに回転) させる
    //move = XMVector3TransformCoord(move, rotY);

    ////Wキーが押されたら移動
    //if (Input::IsKey(DIK_W)) {
    //    //移動
    //    pos += move;

    //    //現在地をベクトルからいつものtransform.positionに戻す
    //    XMStoreFloat3(&transform_.position_, pos);

    //}

    //if (Input::IsKey(DIK_S)) {

    //    pos -= move;

    //    XMStoreFloat3(&transform_.position_, pos);

    //}

    //XMFLOAT3 camPos;

    //camPos = { transform_.position_ };
    //Camera::SetPosition(camPos);
    //XMFLOAT3 man;
    //XMStoreFloat3(&man, pos + move);
    //Camera::SetTarget(man);

    //if (Input::IsKey(DIK_SPACE) && transform_.position_.y <= 10.0f) {
    //    transform_.position_.y += 0.2f;
    //}
    //if (Input::IsKey(DIK_LSHIFT) && transform_.position_.y >= 0.0f || Input::IsKey(DIK_LSHIFT) && transform_.position_.y >= 0.0f) {
    //    transform_.position_.y -= 0.2f;
    //}


    //if (Input::IsKey(DIK_LEFTARROW)) {
    //    transform_.rotate_.y -= 1.0f;
    //}
    //if (Input::IsKey(DIK_RIGHTARROW)) {
    //    transform_.rotate_.y += 1.0f;
    //}

    ////transform.rotate_.y度回転させる行列を作成
    //XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //if (Input::IsKey(DIK_UPARROW) && transform_.rotate_.x <= 88) {
    //    transform_.rotate_.x += 1.0f;
    //}
    //if (Input::IsKey(DIK_DOWNARROW) && transform_.rotate_.x >= 0) {
    //    transform_.rotate_.x -= 1.0f;
    //}

    //XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    ////現在の位置をベクトル型に変換
    //XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    ////1フレームの移動ベクトル
    //XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m

    ////移動ベクトルを変形 (洗車と同じ向きに回転) させる
    //moveZ = XMVector3TransformCoord(moveZ, rotY);


    ////Wキーが押されたら移動
    //if (Input::IsKey(DIK_W)) {
    //    //移動
    //    pos += moveZ;

    //}

    //if (Input::IsKey(DIK_S)) {

    //    pos -= moveZ;

    //}
    //
    ////1フレームの移動ベクトル
    //XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //横に0.1m

    ////移動ベクトルを変形 (洗車と同じ向きに回転) させる
    //moveX = XMVector3TransformCoord(moveX, rotY);


    //if (Input::IsKey(DIK_A)) {

    //    pos -= moveX;

    //}

    //if (Input::IsKey(DIK_D)) {

    //    pos += moveX;

    //}

    ////現在地をベクトルからいつものtransform.positionに戻す
    //XMStoreFloat3(&transform_.position_, pos);

    ////ポジションを常に見る。
    //Camera::SetTarget(transform_.position_);

    ////カメラの位置は常にポジションの後ろ
    //XMVECTOR vCam = { 0,0,-10,0 };
    //vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    //Camera::SetPosition(pos + vCam);

#else

      //////////////////////////////////////////////////////////
     ///////////ここからFPS視点////////////////////////////////
    //////////////////////////////////////////////////////////

    //transform.rotate_.y度回転させる行列を作成
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //現在の位置をベクトル型に変換
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1フレームの移動ベクトル
    XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m
    //移動ベクトルを変形 (洗車と同じ向きに回転) させる
    moveZ = XMVector3TransformCoord(moveZ, rotY);

    //1フレームの移動ベクトル
    XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //横に0.1m
    //移動ベクトルを変形 (洗車と同じ向きに回転) させる
    moveX = XMVector3TransformCoord(moveX, rotY);


    //移動
    if (Input::IsKey(DIK_W)) {
        //移動
        pos += moveZ;

    }
    if (Input::IsKey(DIK_S)) {

        pos -= moveZ;

    }
    if (Input::IsKey(DIK_A)) {

        pos -= moveX;

    }
    if (Input::IsKey(DIK_D)) {

        pos += moveX;

    }

    //現在地をベクトルからいつものtransform.positionに戻す
    XMStoreFloat3(&transform_.position_, pos);

    //今の状態だとマウスが中心からずれてたら常に回るようになってるから直してね明日の俺
    //一人称視点じゃなかったら作業無駄無駄だから一旦やめとこ

    XMFLOAT3 mousePos = Input::GetMouseMove();

    //mousePos.x += Direct3D::screenWidth_ / 2;
    //mousePos.y += Direct3D::screenHeight_ / 2;

    transform_.rotate_.x += mousePos.x;
    transform_.rotate_.y += mousePos.y;

    //Input::SetMousePosition(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);

    //ポジションを常に見る。
    Camera::SetTarget(transform_.position_);

    //カメラの位置は常にポジションの後ろ
    //z軸－10のやつに回転行列をかけて常に後ろにいるようにしてるけどFPS視点だと不要かも

    //カメラの位置は常にポジションの後ろ
    XMVECTOR vCam = { 0,5,-5,0 };
    vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    Camera::SetPosition(pos + vCam);

#endif

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