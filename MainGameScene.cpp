#include "MainGameScene.h"
#include "Player.h"
#include "StageMap.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//デストラクタ
MainGameScene::~MainGameScene()
{
}

//初期化
void MainGameScene::Initialize()
{
	Player* pPlayer = Instantiate<Player>(this);
	//StageMap* pStageMap = Instantiate<StageMap>(this);
}

//更新
void MainGameScene::Update()
{
}

//描画
void MainGameScene::Draw()
{
}

//開放
void MainGameScene::Release()
{
}