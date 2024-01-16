/**********************************************
 *
 *  Scene.h
 *  各シーンの既定となるクラスを記述
 *
 *  製作者：牛丸文仁
 *  制作日：2023/03/25
 *
 **********************************************/
#pragma once
#include "UserResources.h"

//	前方宣言
class SceneManager;

class Scene
{
private:
	SceneManager*			m_sceneManager;		//	シーンマネージャー

public:
	//	コンストラクタ
	Scene(SceneManager* sceneManager) :
		m_sceneManager(sceneManager)
	{
	};

	virtual ~Scene() {};				//	デストラクタ

	virtual void Initialize()	= 0;	//	初期化処理
	virtual void Update()		= 0;	//	更新処理
	virtual void Render()		= 0;	//	描画処理
	virtual void Finalize()		= 0;	//	終了処理

public:
	SceneManager* GetSceneManager()				const { return m_sceneManager; }	//	シーンマネージャーの取得

};
