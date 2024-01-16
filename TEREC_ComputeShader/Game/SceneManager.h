/**********************************************
 *
 *  SceneManager.h
 *  �V�[���̊Ǘ��ƍX�V���s��
 *
 *  ����ҁF���ە��m
 *  ������F2023/08/16
 *
 **********************************************/
#pragma once
#include "pch.h"
#include "UserResources.h"

 //	�e�V�[���̃w�b�_�[�t�@�C��
#include "Scenes/PlayScene/PlayScene.h"

//	�O���錾
class Scene;

class SceneManager
{
private:
	//	�Q�[���J�n���̃V�[��
	using StartScene = PlayScene;


private:
	std::unique_ptr<Scene> m_currentScene;	//	���݂̃V�[��

	//	�I���t���O
	bool m_isExit;
	
public:
	//	�R���X�g���N�^
	SceneManager():
		m_currentScene{},
		m_isExit(false)
	{
	}
	//	�f�X�g���N�^
	~SceneManager()
	{
		if (m_currentScene)
			m_currentScene->Finalize();

		m_currentScene.reset();
	}

	//	����������
	void Initialize()
	{
		//	�Q�[���J�n���̃V�[����ݒ�
#if _DEBUG
		ChangeScene<StartScene>();
#else
		ChangeScene<TitleScene>();
#endif

	}

	//	�X�V����
	void Update()
	{
		//	���݂̃V�[���̍X�V����
		if (m_currentScene)
			m_currentScene->Update();

		//	�I���t���O���L�� ���� Wave�o���N�����g�p�Ȏ� �ɂȂ�����Q�[�����I������
		if (m_isExit)
		{
			Exit();
		}
	}

	//	�`�揈��
	void Render()
	{
		//	���݂̃V�[���̕`�揈��
		if (m_currentScene)
			m_currentScene->Render();
	}

	//	�I������
	void Finalize()
	{
		m_currentScene->Finalize();
		m_currentScene.reset();;
	}


public:
	//	�V�[���̐؂�ւ�����
	template<typename T>
	void ChangeScene()
	{
		//	�V�[�������݂���Ƃ��͏I���������s���J������
		if (m_currentScene)
		{
			m_currentScene->Finalize();
		}

		//	�V�����V�[���̍쐬
		m_currentScene.reset(new T(this));

		//	�V�[�������݂��Ȃ��Ƃ��̓G���[
		assert(m_currentScene);

		//	�J�ڐ�̃V�[���̏���������
		m_currentScene->Initialize();
	};

	//	�Q�[���̏I���t���O�̗L����
	void ExitGame()
	{
		//	�I���t���O�̗L����
		m_isExit = true;
	}

	//	�Q�[���̏I������
	void Exit()
	{
		//	���b�Z�[�W�̑��M
		PostQuitMessage(0);
	}

};

