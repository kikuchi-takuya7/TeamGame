#include "Camera.h"

namespace Camera {
	//�ϐ�
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
	XMMATRIX billBoard_;
}

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), target_ - position_, XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	SetPosition(XMLoadFloat3(&position));
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() 
{ 
	XMFLOAT3 f;

	XMStoreFloat3(&f, position_);
	return f;
}

//�œ_���擾
XMFLOAT3 Camera::GetTarget()
{
	XMFLOAT3 f;

	XMStoreFloat3(&f, target_);
	return f;
}


//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	//return XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	//return XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);
	return projMatrix_;
}

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() 
{
	return billBoard_; 
}