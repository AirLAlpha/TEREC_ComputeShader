/**********************************************
 *
 *  SceneManager.h
 *  シーンの管理と更新を行う
 *
 *  製作者：牛丸文仁
 *  制作日：2023/08/16
 *
 **********************************************/
#pragma once
#include "pch.h"
#include "UserResources.h"

 //	各シーンのヘッダーファイル
#include "Scenes/PlayScene/PlayScene.h"

//	前方宣言
class Scene;

class SceneManager
{
private:
	//	ゲーム開始時のシーン
	using StartScene = PlayScene;


private:
	std::unique_ptr<Scene> m_currentScene;	//	現在のシーン

	//	終了フラグ
	bool m_isExit;
	
public:
	//	コンストラクタ
	SceneManager():
		m_currentScene{},
		m_isExit(false)
	{
	}
	//	デストラクタ
	~SceneManager()
	{
		if (m_currentScene)
			m_currentScene->Finalize();

		m_currentScene.reset();
	}

	//	初期化処理
	void Initialize()
	{
		//	ゲーム開始時のシーンを設定
#if _DEBUG
		ChangeScene<StartScene>();
#else
		ChangeScene<TitleScene>();
#endif

	}

	//	更新処理
	void Update()
	{
		//	現在のシーンの更新処理
		if (m_currentScene)
			m_currentScene->Update();

		//	終了フラグが有効 かつ Waveバンクが未使用な時 になったらゲームを終了する
		if (m_isExit)
		{
			Exit();
		}
	}

	//	描画処理
	void Render()
	{
		//	現在のシーンの描画処理
		if (m_currentScene)
			m_currentScene->Render();
	}

	//	終了処理
	void Finalize()
	{
		m_currentScene->Finalize();
		m_currentScene.reset();;
	}


public:
	//	シーンの切り替え処理
	template<typename T>
	void ChangeScene()
	{
		//	シーンが存在するときは終了処理を行い開放する
		if (m_currentScene)
		{
			m_currentScene->Finalize();
		}

		//	新しいシーンの作成
		m_currentScene.reset(new T(this));

		//	シーンが存在しないときはエラー
		assert(m_currentScene);

		//	遷移先のシーンの初期化処理
		m_currentScene->Initialize();
	};

	//	ゲームの終了フラグの有効化
	void ExitGame()
	{
		//	終了フラグの有効化
		m_isExit = true;
	}

	//	ゲームの終了処理
	void Exit()
	{
		//	メッセージの送信
		PostQuitMessage(0);
	}

};

