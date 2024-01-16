/**********************************************
 *
 *  PlayScene.cpp
 *  インゲーム部分の処理を記述
 *
 *  製作者：牛丸文仁
 *  制作日：2023/03/25
 *
 **********************************************/
#include "pch.h"
#include <random>
#include "PlayScene.h"
#include "Utilities/ReadData.h"

using namespace DirectX;


//	コンストラクタ
PlayScene::PlayScene(SceneManager* sceneManager):
	Scene(sceneManager),
	m_results{}
{
}
//	デストラクタ
PlayScene::~PlayScene()
{
}

//--------------------------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------------------------
void PlayScene::Initialize()
{
	//	スプライトバッチの作成
	m_spriteBatch = std::make_unique<SpriteBatch>(
		UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
	);
	//	スプライトフォントの作成
	m_spriteFont = std::make_unique<SpriteFont>(
		UserResources::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);

	//	シェーダーとバッファの作成
	CreateShaderAndBuffers();
	//	計算の実行
	Calculate();
}

//--------------------------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------------------------
void PlayScene::Update()
{
}

//--------------------------------------------------------------------------------
// 描画処理
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
// 終了処理
//--------------------------------------------------------------------------------
void PlayScene::Finalize()
{

}


//--------------------------------------------------------------------------------
// シェーダーとバッファの作成（問題の作成）
//--------------------------------------------------------------------------------
void PlayScene::CreateShaderAndBuffers()
{
	ID3D11Device* device = UserResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//	コンピュートシェーダーの作成
	{
		//	シェーダーデータの読み込み
		std::vector<uint8_t> csData = DX::ReadData(L"Resources/Shaders/Calc_CS.cso");
		//	作成
		DX::ThrowIfFailed(
			device->CreateComputeShader(csData.data(), csData.size(), nullptr, m_computeShader.ReleaseAndGetAddressOf())
		);
	}

	//	問題の作成
	{
		//	AとBに乱数（0～10）を割り当てる
		for (int i = 0; i < QUESTION_NUM; i++)
		{
			m_questions[i].a = GetRandomNumber(1, 100);
			m_questions[i].b = GetRandomNumber(1, 100);
		}
	}

	//	問題のバッファの作成
	{
		//	作成するバッファの情報
		CD3D11_BUFFER_DESC desc
		{
			sizeof(Question) * QUESTION_NUM,			//	バッファのサイズ（問題一つ分のサイズ * 問題数）
			D3D11_BIND_SHADER_RESOURCE,					//	バッファをShaderResourceとして使用する
			D3D11_USAGE_DEFAULT,						//	CPUとGPUのアクセスはデフォルト
			0,											//	CPUからはアクセスしない
			D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,		//	リソースの種類に構造体バッファを使用する
			sizeof(Question)							//	構造体バッファの要素一つ分のサイズを指定する
		};
		//	バッファの初期値
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = m_questions;
		//	バッファの作成
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_questionBuffer.ReleaseAndGetAddressOf())
		);
	}
	//	問題のSRVの作成
	{
		//	作成するSRVの情報
		CD3D11_SHADER_RESOURCE_VIEW_DESC desc
		{
			m_questionBuffer.Get(),						//	対応させるバッファ
			DXGI_FORMAT_UNKNOWN,						//	形式は不明（構造体バッファのときは不明）
			0,											//	最初の要素の位置
			QUESTION_NUM								//	要素数
		};
		//	SRVの作成
		DX::ThrowIfFailed(
			device->CreateShaderResourceView(m_questionBuffer.Get(), &desc, m_questionSRV.ReleaseAndGetAddressOf())
		);
	}

	//	結果用のバッファを作成
	{
		//	作成するバッファの情報
		CD3D11_BUFFER_DESC desc
		{
			sizeof(int) * QUESTION_NUM,				//	バッファのサイズ（int * 問題数）
			D3D11_BIND_UNORDERED_ACCESS,			//	バッファをUnorderedAccessで使用する
			D3D11_USAGE_DEFAULT,					//	CPUとGPUのアクセスはデフォルト	
			D3D11_CPU_ACCESS_READ,					//	CPUからの読み取りを使用する
			D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,	//	リソースの種類に構造体バッファを使用する
			sizeof(int)								//	構造体バッファの要素一つ分のサイズを指定する
		};
		//	バッファの作成
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_resultBuffer.ReleaseAndGetAddressOf())
		);
	}
	//	結果用UAVの作成
	{
		//	作成するUAVの情報
		CD3D11_UNORDERED_ACCESS_VIEW_DESC desc
		{
			m_resultBuffer.Get(),					//	対応させるバッファ	
			DXGI_FORMAT_UNKNOWN,					//	形式は不明（構造体バッファのときは不明）
			0,										//	最初の要素の位置
			QUESTION_NUM							//	要素数
		};
		//	UAVの作成
		DX::ThrowIfFailed(
			device->CreateUnorderedAccessView(m_resultBuffer.Get(), &desc, m_resultUAV.ReleaseAndGetAddressOf())
		);
	}
}

//--------------------------------------------------------------------------------
// 計算の実行（コンピュートシェーダーの実行）
//--------------------------------------------------------------------------------
void PlayScene::Calculate()
{
	ID3D11DeviceContext* context = UserResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	使用するコンピュートシェーダーの設定
	context->CSSetShader(m_computeShader.Get(), nullptr, 0);
	//	コンピュートシェーダーに問題を設定
	context->CSSetShaderResources(0, 1, m_questionSRV.GetAddressOf());
	//	コンピュートシェーダーに結果用のバッファを設定
	context->CSSetUnorderedAccessViews(0, 1, m_resultUAV.GetAddressOf(), 0);
	//	コンピュートシェーダーの実行（引数はスレッドグループ数のX, Y, Z）
	context->Dispatch(1, 1, 1);


	//	結果を取り出す
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	//	マップ（GPUからのアクセスを拒否して、安全にアクセスする）
	context->Map(m_resultBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
	//	値を配列にコピーする
	int* mappedResults = static_cast<int*>(mapped.pData);
	memcpy(m_results, mappedResults, sizeof(int) * QUESTION_NUM);
	//	アンマップ（GPUからのアクセスを再度有効にする）
	context->Unmap(m_resultBuffer.Get(), 0);


	//	コンピュートシェーダーの解除
	context->CSSetShader(nullptr, nullptr, 0);
	//	コンピュートシェーダーのバッファを解除
	ID3D11ShaderResourceView* srvDummy = nullptr;
	context->CSSetShaderResources(0, 1, &srvDummy);
	ID3D11UnorderedAccessView* uavDummy = nullptr;
	context->CSSetUnorderedAccessViews(0, 1, &uavDummy, 0);
}


//--------------------------------------------------------------------------------
// 乱数の取得
//--------------------------------------------------------------------------------
int PlayScene::GetRandomNumber(int min, int max)
{
	std::random_device randDevice;
	std::mt19937 randEngine(randDevice());
	std::uniform_int_distribution<> dist(min, max);
	return dist(randEngine);
}
