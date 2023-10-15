#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("taikianime.fbx");
    assert(hModel_ >= 0);

    transform_.rotate_.y = 180;

    Model::SetAnimFrame(hModel_, 0, 120, 1);
}

//�X�V
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

    ////�o�͂̂Ƃ���ɕϐ����ǂ��Ȃ��Ă邩�\��
    //Debug::Log(transform_.position_.x, true);

    ////��Ԃ̌��݂̈ʒu���x�N�g���^�ɕϊ�
    //XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    ////1�t���[���̈ړ��x�N�g��
    //XMVECTOR move = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m

    ////transform.rotate_.y�x��]������s����쐬
    //XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    ////�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    //move = XMVector3TransformCoord(move, rotY);

    ////W�L�[�������ꂽ��ړ�
    //if (Input::IsKey(DIK_W)) {
    //    //�ړ�
    //    pos += move;

    //    //���ݒn���x�N�g�����炢����transform.position�ɖ߂�
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

    ////transform.rotate_.y�x��]������s����쐬
    //XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //if (Input::IsKey(DIK_UPARROW) && transform_.rotate_.x <= 88) {
    //    transform_.rotate_.x += 1.0f;
    //}
    //if (Input::IsKey(DIK_DOWNARROW) && transform_.rotate_.x >= 0) {
    //    transform_.rotate_.x -= 1.0f;
    //}

    //XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    ////���݂̈ʒu���x�N�g���^�ɕϊ�
    //XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    ////1�t���[���̈ړ��x�N�g��
    //XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m

    ////�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    //moveZ = XMVector3TransformCoord(moveZ, rotY);


    ////W�L�[�������ꂽ��ړ�
    //if (Input::IsKey(DIK_W)) {
    //    //�ړ�
    //    pos += moveZ;

    //}

    //if (Input::IsKey(DIK_S)) {

    //    pos -= moveZ;

    //}
    //
    ////1�t���[���̈ړ��x�N�g��
    //XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //����0.1m

    ////�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    //moveX = XMVector3TransformCoord(moveX, rotY);


    //if (Input::IsKey(DIK_A)) {

    //    pos -= moveX;

    //}

    //if (Input::IsKey(DIK_D)) {

    //    pos += moveX;

    //}

    ////���ݒn���x�N�g�����炢����transform.position�ɖ߂�
    //XMStoreFloat3(&transform_.position_, pos);

    ////�|�W�V��������Ɍ���B
    //Camera::SetTarget(transform_.position_);

    ////�J�����̈ʒu�͏�Ƀ|�W�V�����̌��
    //XMVECTOR vCam = { 0,0,-10,0 };
    //vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    //Camera::SetPosition(pos + vCam);

#else

      //////////////////////////////////////////////////////////
     ///////////��������FPS���_////////////////////////////////
    //////////////////////////////////////////////////////////

    //transform.rotate_.y�x��]������s����쐬
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

    //���݂̈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m
    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    moveZ = XMVector3TransformCoord(moveZ, rotY);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //����0.1m
    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    moveX = XMVector3TransformCoord(moveX, rotY);


    //�ړ�
    if (Input::IsKey(DIK_W)) {
        //�ړ�
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

    //���ݒn���x�N�g�����炢����transform.position�ɖ߂�
    XMStoreFloat3(&transform_.position_, pos);

    //���̏�Ԃ��ƃ}�E�X�����S���炸��Ă����ɉ��悤�ɂȂ��Ă邩�璼���Ă˖����̉�
    //��l�̎��_����Ȃ��������Ɩ��ʖ��ʂ������U��߂Ƃ�

    XMFLOAT3 mousePos = Input::GetMouseMove();

    //mousePos.x += Direct3D::screenWidth_ / 2;
    //mousePos.y += Direct3D::screenHeight_ / 2;

    transform_.rotate_.x += mousePos.x;
    transform_.rotate_.y += mousePos.y;

    //Input::SetMousePosition(Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2);

    //�|�W�V��������Ɍ���B
    Camera::SetTarget(transform_.position_);

    //�J�����̈ʒu�͏�Ƀ|�W�V�����̌��
    //z���|10�̂�ɉ�]�s��������ď�Ɍ��ɂ���悤�ɂ��Ă邯��FPS���_���ƕs�v����

    //�J�����̈ʒu�͏�Ƀ|�W�V�����̌��
    XMVECTOR vCam = { 0,5,-5,0 };
    vCam = XMVector3TransformCoord(vCam, rotX * rotY);
    Camera::SetPosition(pos + vCam);

#endif

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}