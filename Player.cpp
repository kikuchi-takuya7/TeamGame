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
    hModel_ = Model::Load("goburin.fbx");
    assert(hModel_ >= 0);
}

//�X�V
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

    //�o�͂̂Ƃ���ɕϐ����ǂ��Ȃ��Ă邩�\��
    Debug::Log(transform_.position_.x, true);

    //��Ԃ̌��݂̈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR move = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m

    //transform.rotate_.y�x��]������s����쐬
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    move = XMVector3TransformCoord(move, rotY);

    //W�L�[�������ꂽ��ړ�
    if (Input::IsKey(DIK_W)) {
        //�ړ�
        pos += move;

        //���ݒn���x�N�g�����炢����transform.position�ɖ߂�
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