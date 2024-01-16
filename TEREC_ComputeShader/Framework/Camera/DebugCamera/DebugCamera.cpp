/**********************************************
 *
 *  DebugCamera.cpp
 *  �f�o�b�O�p�̃J�����̏������L�q
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/27
 *
 **********************************************/
#include "pch.h"
#include "DebugCamera.h"

#include "UserResources.h"
#include "InputManager/InputManager.h"

using namespace DirectX;

const float DEFAULT_SENSITIVITY = 20.0f;
const float DEFAULT_DISTANCE = 2.0f;

DebugCamera::DebugCamera() :
	sensitivity(DEFAULT_SENSITIVITY),
	wheelVal(0)
{
	angle.x = XM_PI / 6 * 2;
	angle.y = 0;

}

DebugCamera::~DebugCamera()
{
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void DebugCamera::Update()
{
	//	�}�E�X�̓��͂��擾
	auto mouseState = InputManager::GetInstance()->GetMouse()->GetState();
	

	if (mouseState.leftButton)
		RotateUpdate(mouseState.x, mouseState.y);

	//	�z�C�[���̉�]�ʂ�ێ�
	wheelVal = mouseState.scrollWheelValue;
	if (mouseState.scrollWheelValue > 0)
	{
		wheelVal = 0;
		InputManager::GetInstance()->GetMouse()->ResetScrollWheelValue();
	}

	//	�s��̍X�V����
	MatrixUpdate();

	//	�}�E�X�̍��W��ێ�
	oldMousePos.x = static_cast<float>(mouseState.x);
	oldMousePos.y = static_cast<float>(mouseState.y);
}


//--------------------------------------------------------------------------------
// ��]�̍X�V����
//--------------------------------------------------------------------------------
void DebugCamera::RotateUpdate(int x, int y)
{
	//	�}�E�X�̈ړ��ʂ��v�Z
	float deltaTime = static_cast<float>(UserResources::GetInstance()->GetStepTimer()->GetElapsedSeconds());
	float dx = (x - oldMousePos.x) * sensitivity * deltaTime;
	float dy = (y - oldMousePos.y) * sensitivity * deltaTime;

	//	��]�ʂ��v�Z
	float angleX = dy * XM_PI / 180.0f;
	float angleY = dx * XM_PI / 180.0f;

	//	��]�ʂ����Z
	angle += SimpleMath::Vector2(angleX, angleY);
}

//--------------------------------------------------------------------------------
// �s��̍X�V����
//--------------------------------------------------------------------------------
void DebugCamera::MatrixUpdate()
{
	//	��]�s��̍쐬
	SimpleMath::Matrix rot =
		SimpleMath::Matrix::CreateRotationY(angle.y) *
		SimpleMath::Matrix::CreateRotationX(angle.x);

	//	�v�Z�p�̕ϐ����쐬
	SimpleMath::Vector3 pos = SimpleMath::Vector3(0, 0, 1);
	SimpleMath::Vector3 up = SimpleMath::Vector3::Up;

	//	�s����g���Ĉړ�������
	pos = SimpleMath::Vector3::Transform(pos, rot.Invert());
	pos *= DEFAULT_DISTANCE - wheelVal / 100;
	up = SimpleMath::Vector3::Transform(up, rot.Invert());

	////	�ړ��������ϐ���K��
	//this->m_pos = pos;
	//this->m_up = up;

	SimpleMath::Vector3 target = GetTarget();
	//	�r���[�s��̍X�V
	SetView(target + pos, target, up);
}
