/**********************************************
 *
 *  InputManager.h
 *  InputManager.cpp�̃w�b�_�[�t�@�C��
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public:
	using Keys = DirectX::Keyboard::Keys;

	enum class MouseButtons
	{
		LEFT,		//	��
		RIGHT,		//	�E
		MIDDLE,		//	�z�C�[��
	};

private:
	//	�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>							m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardStateTracker;

	//	�}�E�X
	std::unique_ptr<DirectX::Mouse>						m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_buttonStateTracker;

private:
	InputManager();		//	�R���X�g���N�^
	~InputManager();	//	�f�X�g���N�^

public:
	//	�R�s�[�R���X�g���N�^�A���[�u�R���X�g���N�^���폜
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static InputManager* GetInstance();		//	�C���X�^���X�̎擾

public:
	void Update();		//	���͂̍X�V�����@��Update���ň�x�������s����悤�ɁI

	DirectX::Keyboard*							GetKeyboard();								//	�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker*	GetKeyboardStateTracker();					//	�L�[�{�[�h�X�e�[�g�g���b�J�[�̎擾
	DirectX::Keyboard::State					GetKeyboardState();							//	�L�[�{�[�h�̓��͂��擾
	bool										GetKey		(Keys key);						//	�L�[���͂��擾
	bool										GetKeyDown	(Keys key);						//	�L�[�����͂��ꂽ�u�Ԃ��擾
	bool										GetKeyUp	(Keys key);						//	�L�[�������ꂽ�u�Ԃ��擾

	DirectX::Mouse*								GetMouse();									//	�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker*			GetMouseButtonStateTracker();				//	�}�E�X�{�^���X�e�[�g�g���b�J�[�̎擾
	bool										GetMouseButton		(MouseButtons button);	//	�}�E�X�̃{�^���̓��͂��擾
	bool										GetMouseButtonDown	(MouseButtons button);	//	�}�E�X�̃{�^�������͂��ꂽ�u�Ԃ��擾
	bool										GetMouseButtonUp	(MouseButtons button);	//	�}�E�X�̃{�^���������ꂽ�u�Ԃ��擾
};
