/**********************************************
 *
 *  Grid.cpp
 *  �O���b�h�̕`��N���X
 *
 *  ����ҁF���ە��m
 *  ������F2023/06/12
 *
 **********************************************/
#include "pch.h"
#include "Grid.h"

#include "UserResources.h"
#include "DebugDraw/DebugDraw.h"

using namespace DirectX;

//	�R���X�g���N�^
Grid::Grid(const DirectX::SimpleMath::Vector2& size) :
	m_size(size)
{
	ID3D11Device*			device	= UserResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	ID3D11DeviceContext*	context = UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�x�[�V�b�N�G�t�F�N�g�̍쐬
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexType>>(context);

	//	�C���v�b�g���C�A�E�g�̍쐬
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexType>(device, m_basicEffect.get(), m_inputLayout.ReleaseAndGetAddressOf())
	);
}


//--------------------------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------------------------
void Grid::Render(const SimpleMath::Matrix& view, const SimpleMath::Matrix& proj)
{
	//	�K�v�ȃ��\�[�X���擾
	auto context = UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�s��̍쐬
	SimpleMath::Matrix world;
	world = SimpleMath::Matrix::CreateScale(SimpleMath::Vector3(m_size.x / 2.0f, 0.0f, m_size.y / 2.0f));

	//	�s��̐ݒ�
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	//	�C���v�b�g���C�A�E�g�̐ݒ�
	context->IASetInputLayout(m_inputLayout.Get());

	//	�O���b�h���̕`��
	m_primitiveBatch->Begin();

	DX::DrawGrid(
		m_primitiveBatch.get(),
		SimpleMath::Vector3::Right, 
		SimpleMath::Vector3::Forward, 
		SimpleMath::Vector3::Zero, 
		static_cast<size_t>(m_size.x),
		static_cast<size_t>(m_size.y)
	);

	m_primitiveBatch->End();
}