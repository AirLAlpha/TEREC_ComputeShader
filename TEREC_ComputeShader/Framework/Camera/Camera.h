/**********************************************
 *
 *  Camera.h
 *  Camera.cpp�̃w�b�_�[�t�@�C��
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#pragma once

class Camera
{
private:
	//	�f�t�H���g�̒l�i�萔�j
	const float DEFAULT_FOV = 45.0f;		//	�f�t�H���g�̎���p
	const float DEFAULT_NEAR = 1.0f;		//	�f�t�H���g�̃J�����O�����i��O�j
	const float DEFAULT_FAR = 100.0f;		//	�f�t�H���g�̃J�����O�����i���j

private:
	//	View
	DirectX::SimpleMath::Vector3	m_pos;				//	���W
	DirectX::SimpleMath::Vector3	m_target;			//	�����_

	DirectX::SimpleMath::Vector3	m_up;				//	��Ƃ������

	//	Projection
	float							m_fieldOfView;		//	����p
	float							m_nearPlane;		//	�J�����O�����i��O�j
	float							m_farPlane;			//	�J�����O�����i���j

	//	�s��
	DirectX::SimpleMath::Matrix		m_view;				//	�r���[�s��
	DirectX::SimpleMath::Matrix		m_projection;		//	�ˉe�s��

public:
	Camera();
	virtual ~Camera();

	//	�r���[�s��̐ݒ�
	void SetView(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::Up);
	void SetView(DirectX::SimpleMath::Matrix view);

	//	�ˉe�s��̐ݒ�
	void SetProjection(float fieldOfView, float nearPlane, float farPlane);
	void SetProjection(DirectX::SimpleMath::Matrix projection);

	//	�ˉe�s��̍Čv�Z
	void CalculateProjectionMatrix();

	//	���W�̐ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	//	�����_�̐ݒ�
	void SetTarget(DirectX::SimpleMath::Vector3 target);
	//	�J�����O�����̐ݒ�
	void SetCullingDist(float nearPlane, float farPlane);
	//	����p�̐ݒ�
	void SetFov(float fieldOfView);

	//	���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition();
	//	�����_�̎擾
	DirectX::SimpleMath::Vector3 GetTarget();

	//	�r���[�s��̎擾
	DirectX::SimpleMath::Matrix GetView();
	//	�ˉe�s��̎擾
	DirectX::SimpleMath::Matrix GetProjection();

	//	���ʃx�N�g���̎擾
	DirectX::SimpleMath::Vector3 GetForward();
	//	�E�����x�N�g���̎擾
	DirectX::SimpleMath::Vector3 GetRight();
};

