/**********************************************
 *
 *  Camera.cpp
 *  ��{�I�ȃJ�����̏������L�q
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#include "pch.h"
#include "Camera.h"

#include "DeviceResources.h"
#include "StepTimer.h"
#include "../Utilities/UtilityFunction.h"

#include "UserResources.h"

using namespace DirectX;

Camera::Camera():
	m_fieldOfView(DEFAULT_FOV),
	m_nearPlane(DEFAULT_NEAR),
	m_farPlane(DEFAULT_FAR)
{
	CalculateProjectionMatrix();		//	�f�t�H���g�̎ˉe�s����v�Z
}

Camera::~Camera()
{
}

//--------------------------------------------------------------------------------
// �r���[�s��̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetView(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up)
{
	//	�e�l��ێ�
	this->m_pos = pos;
	this->m_target = target;
	this->m_up = up;

	//	�s����쐬
	m_view = SimpleMath::Matrix::CreateLookAt(pos, target, up);
}
//--------------------------------------------------------------------------------
// �r���[�s��̐ݒ�i�s��w��Łj
//--------------------------------------------------------------------------------
void Camera::SetView(DirectX::SimpleMath::Matrix view)
{
	this->m_view = view;
}

//--------------------------------------------------------------------------------
// �ˉe�s��̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetProjection(float fieldOfView, float nearPlane, float farPlane)
{
	//	�e�l��ێ�
	this->m_fieldOfView = fieldOfView;
	this->m_nearPlane = nearPlane;
	this->m_farPlane = farPlane;

	//	�A�X�y�N�g����v�Z
	auto deviceResources =  UserResources::GetInstance()->GetDeviceResources();
	LONG width = deviceResources->GetOutputSize().right;
	LONG height = deviceResources->GetOutputSize().bottom;
	float aspectRatio = (float)width / (float)height;

	//	�s��̍쐬
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}
//--------------------------------------------------------------------------------
// �ˉe�s��̐ݒ�i�s��w��Łj
//--------------------------------------------------------------------------------
void Camera::SetProjection(DirectX::SimpleMath::Matrix projection)
{
	this->m_projection = projection;
}

//--------------------------------------------------------------------------------
// �ˉe�s��̍Čv�Z
//--------------------------------------------------------------------------------
void Camera::CalculateProjectionMatrix()
{
	//	�A�X�y�N�g����v�Z
	auto deviceResources = UserResources::GetInstance()->GetDeviceResources();
	LONG width = deviceResources->GetOutputSize().right;
	LONG height = deviceResources->GetOutputSize().bottom;
	float aspectRatio = (float)width / (float)height;

	//	FOV�����W�A���ɕϊ�
	float radFov = XMConvertToRadians(m_fieldOfView);

	//	�s��̍쐬
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(radFov, aspectRatio, m_nearPlane, m_farPlane);
}

//--------------------------------------------------------------------------------
// ���W�̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	this->m_pos = pos;
}

//--------------------------------------------------------------------------------
// �����_�̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	this->m_target = target;
}

//--------------------------------------------------------------------------------
// �J�����O�����̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetCullingDist(float nearPlane, float farPlane)
{
	this->m_nearPlane = nearPlane;
	this->m_farPlane = farPlane;

	//	�s��̍X�V
	CalculateProjectionMatrix();
}

//--------------------------------------------------------------------------------
// ����̐ݒ�
//--------------------------------------------------------------------------------
void Camera::SetFov(float fieldOfView)
{
	this->m_fieldOfView = fieldOfView;
}

//--------------------------------------------------------------------------------
// ���W�̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Vector3 Camera::GetPosition()
{
	return m_pos;
}

//--------------------------------------------------------------------------------
// �����_�̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Vector3 Camera::GetTarget()
{
	return m_target;
}

//--------------------------------------------------------------------------------
// �r���[�s��̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Matrix Camera::GetView()
{
	return m_view;
}

//--------------------------------------------------------------------------------
// �ˉe�s��̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Matrix Camera::GetProjection()
{
	return m_projection;
}

//--------------------------------------------------------------------------------
// ���ʂ̌����x�N�g���̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Vector3 Camera::GetForward()
{
	SimpleMath::Vector3 ret;
	ret = m_target - m_pos;
	ret.Normalize();

	return ret;
}

//--------------------------------------------------------------------------------
// �E�����x�N�g���̎擾
//--------------------------------------------------------------------------------
DirectX::SimpleMath::Vector3 Camera::GetRight()
{
	SimpleMath::Vector3 forward;
	forward = GetForward();

	return SimpleMath::Vector3(-forward.z, 0.0f, forward.x);
}
