/**********************************************
 *
 *  InputManager.cpp
 *  ���͑S�ʂ̏������L�q
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#include "pch.h"
#include "InputManager.h"

using namespace DirectX;

InputManager::InputManager():
	m_keyboard{},
	m_keyboardStateTracker{},
	m_mouse{},
	m_buttonStateTracker{}
{
	//	�e�C���X�^���X�̍쐬
	m_keyboard				= std::make_unique<DirectX::Keyboard>();
	m_keyboardStateTracker	= std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	m_mouse					= std::make_unique<DirectX::Mouse>();
	m_buttonStateTracker	= std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

InputManager::~InputManager()
{
}


//--------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------------------------------------
InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

//--------------------------------------------------------------------------------
// ���͂̍X�V�����@��Update���ň�x�������s����悤�ɁI
//--------------------------------------------------------------------------------
void InputManager::Update()
{
	//	�L�[�{�[�h
	auto keyState = m_keyboard->GetState();
	m_keyboardStateTracker->Update(keyState);

	//	�}�E�X
	auto mouseState = m_mouse->GetState();
	m_buttonStateTracker->Update(mouseState);
}


//--------------------------------------------------------------------------------
// �L�[�{�[�h�̎擾
//--------------------------------------------------------------------------------
DirectX::Keyboard* InputManager::GetKeyboard()
{
	return m_keyboard.get();
}

//--------------------------------------------------------------------------------
// �L�[�{�[�h�X�e�[�g�g���b�J�[�̎擾
//--------------------------------------------------------------------------------
DirectX::Keyboard::KeyboardStateTracker* InputManager::GetKeyboardStateTracker()
{
	return m_keyboardStateTracker.get();
}

//--------------------------------------------------------------------------------
// �L�[�{�[�h�̓��͂��擾
//--------------------------------------------------------------------------------
DirectX::Keyboard::State InputManager::GetKeyboardState()
{
	return m_keyboard->GetState();
}

//--------------------------------------------------------------------------------
// �L�[���͂��擾
//--------------------------------------------------------------------------------
bool InputManager::GetKey(Keyboard::Keys key)
{
	return m_keyboard->GetState().IsKeyDown(key);
}

//--------------------------------------------------------------------------------
// �L�[�����͂��ꂽ�u�Ԃ��擾
//--------------------------------------------------------------------------------
bool InputManager::GetKeyDown(Keyboard::Keys key)
{
	return m_keyboardStateTracker->IsKeyPressed(key);
}

//--------------------------------------------------------------------------------
// �L�[�������ꂽ�u�Ԃ��擾
//--------------------------------------------------------------------------------
bool InputManager::GetKeyUp(Keyboard::Keys key)
{
	return m_keyboardStateTracker->IsKeyReleased(key);
}

//--------------------------------------------------------------------------------
// �}�E�X�̎擾
//--------------------------------------------------------------------------------
DirectX::Mouse* InputManager::GetMouse()
{
	return m_mouse.get();
}

//--------------------------------------------------------------------------------
// �}�E�X�{�^���X�e�[�g�g���b�J�[�̎擾
//--------------------------------------------------------------------------------
DirectX::Mouse::ButtonStateTracker* InputManager::GetMouseButtonStateTracker()
{
	return m_buttonStateTracker.get();
}

//--------------------------------------------------------------------------------
// �}�E�X�̃{�^�����͂��擾
//--------------------------------------------------------------------------------
bool InputManager::GetMouseButton(MouseButtons button)
{
	auto state = m_mouse->GetState();

	switch (button)
	{
	case InputManager::MouseButtons::LEFT:
		return  state.leftButton;
	case InputManager::MouseButtons::RIGHT:
		return state.rightButton;
	case InputManager::MouseButtons::MIDDLE:
		return state.middleButton;

	default:
		return false;
	}
}

//--------------------------------------------------------------------------------
// �}�E�X�̃{�^�������͂��ꂽ�u�Ԃ��擾
//--------------------------------------------------------------------------------
bool InputManager::GetMouseButtonDown(MouseButtons button)
{
	auto state = m_buttonStateTracker.get();

	switch (button)
	{
	case InputManager::MouseButtons::LEFT:
		return state->leftButton == Mouse::ButtonStateTracker::PRESSED;

	case InputManager::MouseButtons::RIGHT:
		return state->rightButton == Mouse::ButtonStateTracker::PRESSED;

	case InputManager::MouseButtons::MIDDLE:
		return state->middleButton == Mouse::ButtonStateTracker::PRESSED;

	default:
		return false;
	}
}

//--------------------------------------------------------------------------------
// �}�E�X�̃{�^���������ꂽ�u�Ԃ��擾
//--------------------------------------------------------------------------------
bool InputManager::GetMouseButtonUp(MouseButtons button)
{
	auto state = m_buttonStateTracker.get();

	switch (button)
	{
	case InputManager::MouseButtons::LEFT:
		return state->leftButton == Mouse::ButtonStateTracker::RELEASED;

	case InputManager::MouseButtons::RIGHT:
		return state->rightButton == Mouse::ButtonStateTracker::RELEASED;

	case InputManager::MouseButtons::MIDDLE:
		return state->middleButton == Mouse::ButtonStateTracker::RELEASED;

	default:
		return false;
	}
}