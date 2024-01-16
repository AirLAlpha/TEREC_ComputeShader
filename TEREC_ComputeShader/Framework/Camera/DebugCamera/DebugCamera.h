/**********************************************
 *
 *  DebugCamera.h
 *  DebugCamera.cpp�̃w�b�_�[�t�@�C��
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/27
 *
 **********************************************/
#pragma once

#include "../Camera.h"

class DebugCamera : public Camera
{
private:
	float sensitivity;							//	�}�E�X���x

	DirectX::SimpleMath::Vector2 angle;			//	��]��
	DirectX::SimpleMath::Vector2 oldMousePos;	//	�O�񏈗����̃J�[�\�����W

	int wheelVal;								//	�z�C�[���̉�]��

private:
	void RotateUpdate(int x, int y);			//	��]�̍X�V����
	void MatrixUpdate();						//	�s��̍X�V����

public:
	DebugCamera();
	~DebugCamera();

	void Update();		//	�X�V����

};
