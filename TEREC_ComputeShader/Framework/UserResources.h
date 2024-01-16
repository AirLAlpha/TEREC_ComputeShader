/**********************************************
 *
 *  UserResources.h
 *  �e���\�[�X�̃��b�v�N���X�i�V���O���g���j
 *
 *  ����ҁF���ە��m
 *  ������F2023/05/22
 *
 **********************************************/
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"

class UserResources
{
private:
	DX::DeviceResources*	m_deviceResources;		//	DeviceResources
	
	DX::StepTimer*			m_stepTimer;			//	StepTimer

	DirectX::CommonStates*	m_commonStates;			//	CommonStates

private:
	//	�R���X�g���N�^
	UserResources():
		m_deviceResources(nullptr),
		m_stepTimer(nullptr),
		m_commonStates(nullptr)
	{};
	//	�f�X�g���N�^
	~UserResources() = default;

public:
	UserResources(const UserResources&) = delete;
	UserResources& operator=(const UserResources&) = delete;
	UserResources(const UserResources&&) = delete;
	UserResources& operator=(const UserResources&&) = delete;

	//	�V���O���g���C���X�^���X�̎擾
	static UserResources* GetInstance()
	{
		static UserResources instance;
		return &instance;
	}

public:
	//	DeviceResources
	void SetDeviceResources(DX::DeviceResources* deviceResources)	{ m_deviceResources = deviceResources; }
	DX::DeviceResources* GetDeviceResources()						{ return m_deviceResources; }

	//	StepTimer
	void SetStepTimer(DX::StepTimer* stepTimer)						{ m_stepTimer = stepTimer; }
	DX::StepTimer* GetStepTimer()									{ return m_stepTimer; }

	//	CommonStates
	void SetCommonStates(DirectX::CommonStates* commonStates)		{ m_commonStates = commonStates; }
	DirectX::CommonStates* GetCommonStates()						{ return m_commonStates; }
};
