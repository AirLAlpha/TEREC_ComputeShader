/**********************************************
 *
 *  PlayScene.h
 *  PlayScene.cppのヘッダーファイル
 *
 *  製作者：牛丸文仁
 *  制作日：2023/03/25
 *
 **********************************************/
#pragma once
#include "../Scene.h"
#include "SpriteFont.h"

class PlayScene : public Scene
{
public:
	//	コンストラクタ
	PlayScene(SceneManager* sceneManager);
	//	デストラクタ
	~PlayScene();


	void Initialize()	override;		//	初期化処理
	void Update()		override;		//	更新処理
	void Render()		override;		//	描画処理
	void Finalize()		override;		//	終了処理


private:
	//	シェーダーとバッファの作成（問題の作成）
	void CreateShaderAndBuffers();
	//	計算の実行（コンピュートシェーダーの実行）
	void Calculate();

	//	乱数の取得
	int GetRandomNumber(int min, int max);

private:
	//	問題数
	static const UINT QUESTION_NUM = 8;

	//	問題一つ分の構造体
	struct Question
	{
		int a = 0;
		int b = 0;
	};


private:
	//	問題の配列
	Question		m_questions[QUESTION_NUM];
	//	結果の配列
	int				m_results[QUESTION_NUM];


	//	コンピュートシェーダー
	Microsoft::WRL::ComPtr<ID3D11ComputeShader>			m_computeShader;

	//	問題のバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_questionBuffer;
	//	問題のShaderResourceView
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_questionSRV;

	//	結果のバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_resultBuffer;
	//	結果のUnorderedAccessView
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	m_resultUAV;


	//	スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>				m_spriteBatch;
	//	スプライトフォント
	std::unique_ptr<DirectX::SpriteFont>				m_spriteFont;

};