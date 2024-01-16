/**********************************************
 *
 *  PlayScene.h
 *  PlayScene.cpp�̃w�b�_�[�t�@�C��
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#pragma once
#include "../Scene.h"
#include "SpriteFont.h"

class PlayScene : public Scene
{
public:
	//	�R���X�g���N�^
	PlayScene(SceneManager* sceneManager);
	//	�f�X�g���N�^
	~PlayScene();


	void Initialize()	override;		//	����������
	void Update()		override;		//	�X�V����
	void Render()		override;		//	�`�揈��
	void Finalize()		override;		//	�I������


private:
	//	�V�F�[�_�[�ƃo�b�t�@�̍쐬�i���̍쐬�j
	void CreateShaderAndBuffers();
	//	�v�Z�̎��s�i�R���s���[�g�V�F�[�_�[�̎��s�j
	void Calculate();

	//	�����̎擾
	int GetRandomNumber(int min, int max);

private:
	//	��萔
	static const UINT QUESTION_NUM = 8;

	//	������̍\����
	struct Question
	{
		int a = 0;
		int b = 0;
	};


private:
	//	���̔z��
	Question		m_questions[QUESTION_NUM];
	//	���ʂ̔z��
	int				m_results[QUESTION_NUM];


	//	�R���s���[�g�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11ComputeShader>			m_computeShader;

	//	���̃o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_questionBuffer;
	//	����ShaderResourceView
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_questionSRV;

	//	���ʂ̃o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_resultBuffer;
	//	���ʂ�UnorderedAccessView
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	m_resultUAV;


	//	�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>				m_spriteBatch;
	//	�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont>				m_spriteFont;

};