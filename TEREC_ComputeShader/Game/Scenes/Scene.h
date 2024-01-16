/**********************************************
 *
 *  Scene.h
 *  �e�V�[���̊���ƂȂ�N���X���L�q
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#pragma once
#include "UserResources.h"

//	�O���錾
class SceneManager;

class Scene
{
private:
	SceneManager*			m_sceneManager;		//	�V�[���}�l�[�W���[

public:
	//	�R���X�g���N�^
	Scene(SceneManager* sceneManager) :
		m_sceneManager(sceneManager)
	{
	};

	virtual ~Scene() {};				//	�f�X�g���N�^

	virtual void Initialize()	= 0;	//	����������
	virtual void Update()		= 0;	//	�X�V����
	virtual void Render()		= 0;	//	�`�揈��
	virtual void Finalize()		= 0;	//	�I������

public:
	SceneManager* GetSceneManager()				const { return m_sceneManager; }	//	�V�[���}�l�[�W���[�̎擾

};
