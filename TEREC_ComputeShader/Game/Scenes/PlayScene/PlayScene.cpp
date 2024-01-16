/**********************************************
 *
 *  PlayScene.cpp
 *  �C���Q�[�������̏������L�q
 *
 *  ����ҁF���ە��m
 *  ������F2023/03/25
 *
 **********************************************/
#include "pch.h"
#include <random>
#include "PlayScene.h"
#include "Utilities/ReadData.h"

using namespace DirectX;


//	�R���X�g���N�^
PlayScene::PlayScene(SceneManager* sceneManager):
	Scene(sceneManager),
	m_results{}
{
}
//	�f�X�g���N�^
PlayScene::~PlayScene()
{
}

//--------------------------------------------------------------------------------
// ����������
//--------------------------------------------------------------------------------
void PlayScene::Initialize()
{
	//	�X�v���C�g�o�b�`�̍쐬
	m_spriteBatch = std::make_unique<SpriteBatch>(
		UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
	);
	//	�X�v���C�g�t�H���g�̍쐬
	m_spriteFont = std::make_unique<SpriteFont>(
		UserResources::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);

	//	�V�F�[�_�[�ƃo�b�t�@�̍쐬
	CreateShaderAndBuffers();
	//	�v�Z�̎��s
	Calculate();
}

//--------------------------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------------------------
void PlayScene::Update()
{
}

//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void PlayScene::Render()
{
	std::string str;
	for (int i = 0; i < QUESTION_NUM; i++)
	{
		str.clear();
		for (int j = 0; j < (i % 20); j++) str += "\n";
		str += std::to_string(m_questions[i].a) + "+" + std::to_string(m_questions[i].b) + "=" + std::to_string(m_results[i]);

		float x = static_cast<float>(i / 20) * 130.0f;

		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), str.c_str(), SimpleMath::Vector2(x, 0), Colors::White, 0.0f, SimpleMath::Vector2::Zero, 2.0f);
		m_spriteBatch->End();
	}
}

//--------------------------------------------------------------------------------
// �I������
//--------------------------------------------------------------------------------
void PlayScene::Finalize()
{

}


//--------------------------------------------------------------------------------
// �V�F�[�_�[�ƃo�b�t�@�̍쐬�i���̍쐬�j
//--------------------------------------------------------------------------------
void PlayScene::CreateShaderAndBuffers()
{
	ID3D11Device* device = UserResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//	�R���s���[�g�V�F�[�_�[�̍쐬
	{
		//	�V�F�[�_�[�f�[�^�̓ǂݍ���
		std::vector<uint8_t> csData = DX::ReadData(L"Resources/Shaders/Calc_CS.cso");
		//	�쐬
		DX::ThrowIfFailed(
			device->CreateComputeShader(csData.data(), csData.size(), nullptr, m_computeShader.ReleaseAndGetAddressOf())
		);
	}

	//	���̍쐬
	{
		//	A��B�ɗ����i0�`10�j�����蓖�Ă�
		for (int i = 0; i < QUESTION_NUM; i++)
		{
			m_questions[i].a = GetRandomNumber(1, 100);
			m_questions[i].b = GetRandomNumber(1, 100);
		}
	}

	//	���̃o�b�t�@�̍쐬
	{
		//	�쐬����o�b�t�@�̏��
		CD3D11_BUFFER_DESC desc
		{
			sizeof(Question) * QUESTION_NUM,			//	�o�b�t�@�̃T�C�Y�i������̃T�C�Y * ��萔�j
			D3D11_BIND_SHADER_RESOURCE,					//	�o�b�t�@��ShaderResource�Ƃ��Ďg�p����
			D3D11_USAGE_DEFAULT,						//	CPU��GPU�̃A�N�Z�X�̓f�t�H���g
			0,											//	CPU����̓A�N�Z�X���Ȃ�
			D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,		//	���\�[�X�̎�ނɍ\���̃o�b�t�@���g�p����
			sizeof(Question)							//	�\���̃o�b�t�@�̗v�f����̃T�C�Y���w�肷��
		};
		//	�o�b�t�@�̏����l
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = m_questions;
		//	�o�b�t�@�̍쐬
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_questionBuffer.ReleaseAndGetAddressOf())
		);
	}
	//	����SRV�̍쐬
	{
		//	�쐬����SRV�̏��
		CD3D11_SHADER_RESOURCE_VIEW_DESC desc
		{
			m_questionBuffer.Get(),						//	�Ή�������o�b�t�@
			DXGI_FORMAT_UNKNOWN,						//	�`���͕s���i�\���̃o�b�t�@�̂Ƃ��͕s���j
			0,											//	�ŏ��̗v�f�̈ʒu
			QUESTION_NUM								//	�v�f��
		};
		//	SRV�̍쐬
		DX::ThrowIfFailed(
			device->CreateShaderResourceView(m_questionBuffer.Get(), &desc, m_questionSRV.ReleaseAndGetAddressOf())
		);
	}

	//	���ʗp�̃o�b�t�@���쐬
	{
		//	�쐬����o�b�t�@�̏��
		CD3D11_BUFFER_DESC desc
		{
			sizeof(int) * QUESTION_NUM,				//	�o�b�t�@�̃T�C�Y�iint * ��萔�j
			D3D11_BIND_UNORDERED_ACCESS,			//	�o�b�t�@��UnorderedAccess�Ŏg�p����
			D3D11_USAGE_DEFAULT,					//	CPU��GPU�̃A�N�Z�X�̓f�t�H���g	
			D3D11_CPU_ACCESS_READ,					//	CPU����̓ǂݎ����g�p����
			D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,	//	���\�[�X�̎�ނɍ\���̃o�b�t�@���g�p����
			sizeof(int)								//	�\���̃o�b�t�@�̗v�f����̃T�C�Y���w�肷��
		};
		//	�o�b�t�@�̍쐬
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_resultBuffer.ReleaseAndGetAddressOf())
		);
	}
	//	���ʗpUAV�̍쐬
	{
		//	�쐬����UAV�̏��
		CD3D11_UNORDERED_ACCESS_VIEW_DESC desc
		{
			m_resultBuffer.Get(),					//	�Ή�������o�b�t�@	
			DXGI_FORMAT_UNKNOWN,					//	�`���͕s���i�\���̃o�b�t�@�̂Ƃ��͕s���j
			0,										//	�ŏ��̗v�f�̈ʒu
			QUESTION_NUM							//	�v�f��
		};
		//	UAV�̍쐬
		DX::ThrowIfFailed(
			device->CreateUnorderedAccessView(m_resultBuffer.Get(), &desc, m_resultUAV.ReleaseAndGetAddressOf())
		);
	}
}

//--------------------------------------------------------------------------------
// �v�Z�̎��s�i�R���s���[�g�V�F�[�_�[�̎��s�j
//--------------------------------------------------------------------------------
void PlayScene::Calculate()
{
	ID3D11DeviceContext* context = UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�g�p����R���s���[�g�V�F�[�_�[�̐ݒ�
	context->CSSetShader(m_computeShader.Get(), nullptr, 0);
	//	�R���s���[�g�V�F�[�_�[�ɖ���ݒ�
	context->CSSetShaderResources(0, 1, m_questionSRV.GetAddressOf());
	//	�R���s���[�g�V�F�[�_�[�Ɍ��ʗp�̃o�b�t�@��ݒ�
	context->CSSetUnorderedAccessViews(0, 1, m_resultUAV.GetAddressOf(), 0);
	//	�R���s���[�g�V�F�[�_�[�̎��s�i�����̓X���b�h�O���[�v����X, Y, Z�j
	context->Dispatch(1, 1, 1);


	//	���ʂ����o��
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	//	�}�b�v�iGPU����̃A�N�Z�X�����ۂ��āA���S�ɃA�N�Z�X����j
	context->Map(m_resultBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
	//	�l��z��ɃR�s�[����
	int* mappedResults = static_cast<int*>(mapped.pData);
	memcpy(m_results, mappedResults, sizeof(int) * QUESTION_NUM);
	//	�A���}�b�v�iGPU����̃A�N�Z�X���ēx�L���ɂ���j
	context->Unmap(m_resultBuffer.Get(), 0);


	//	�R���s���[�g�V�F�[�_�[�̉���
	context->CSSetShader(nullptr, nullptr, 0);
	//	�R���s���[�g�V�F�[�_�[�̃o�b�t�@������
	ID3D11ShaderResourceView* srvDummy = nullptr;
	context->CSSetShaderResources(0, 1, &srvDummy);
	ID3D11UnorderedAccessView* uavDummy = nullptr;
	context->CSSetUnorderedAccessViews(0, 1, &uavDummy, 0);
}


//--------------------------------------------------------------------------------
// �����̎擾
//--------------------------------------------------------------------------------
int PlayScene::GetRandomNumber(int min, int max)
{
	std::random_device randDevice;
	std::mt19937 randEngine(randDevice());
	std::uniform_int_distribution<> dist(min, max);
	return dist(randEngine);
}
