/**********************************************
 *
 *  Grid.h
 *  Grid.cpp�̃w�b�_�[�t�@�C��
 *
 *  ����ҁF���ە��m
 *  ������F2023/06/12
 *
 **********************************************/
#pragma once

class Grid
{
private:
	//	�g�p���钸�_�^�C�v
	using VertexType = DirectX::VertexPositionColor;

	//	�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>				m_inputLayout;
	//	�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect>					m_basicEffect;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<VertexType>>	m_primitiveBatch;

	//	�O���b�h�̑傫��
	DirectX::SimpleMath::Vector2							m_size;

public:
	Grid(const DirectX::SimpleMath::Vector2& size);
	~Grid() = default;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

};
