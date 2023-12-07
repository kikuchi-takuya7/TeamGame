#pragma once
#include "global.h"
#include "GameObject.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_SPLASH = 0,
	SCENE_ID_TITLE,
	SCENE_ID_SELECT,
	SCENE_ID_MAIN,
	SCENE_ID_GAMECLEAR,
	SCENE_ID_GAMEOVER,
	SCENE_ID_RESULT,
	SCENE_ID_MAPEDITOR,
	SCENE_ID_DEVELOP_SELECT,
	SCENE_ID_STORE,
	SCENE_ID_TEAMLOGO,
	SCENE_ID_SPLASHFRAME
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

private:
	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン

};