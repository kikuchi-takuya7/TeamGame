#include "sceneManager.h"

#include "../SplashScene.h"
#include "../TitleScene.h"
#include "../SelectScene.h"
#include "../MainGameScene.h"
#include "../GameClearScene.h"
#include "../GameOverScene.h"
#include "../ResultScene.h"
#include "../DevelopSelectScene.h"
#include "../StoreScene.h"
#include "../Splash_Frame.h"
#include "MapEditor/MapEditorScene.h"
#include "../TeamLogoScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"


//コンストラクタ
SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_DEVELOP_SELECT;
	nextSceneID_ = currentSceneID_;
	Instantiate<DevelopSelectScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_SELECT: Instantiate<SelectScene>(this); break;
		case SCENE_ID_MAIN: Instantiate<MainGameScene>(this); break;
		case SCENE_ID_GAMECLEAR: Instantiate<GameClearScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_MAPEDITOR: Instantiate<MapEditorScene>(this); break;
		case SCENE_ID_DEVELOP_SELECT: Instantiate<DevelopSelectScene>(this); break;
		case SCENE_ID_STORE: Instantiate<StoreScene>(this); break;
		case SCENE_ID_TEAMLOGO: Instantiate<TeamLogoScene>(this); break;
		case SCENE_ID_SPLASHFRAME: Instantiate<Splash_Frame>(this); break;

		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}