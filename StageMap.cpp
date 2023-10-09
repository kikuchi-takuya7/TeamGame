#include "StageMap.h"
#include "Engine/SaveManager/SaveManager.h"

//コンストラクタ
StageMap::StageMap(GameObject* parent)
    :GameObject(parent, "StageMap")
{
}

//デストラクタ
StageMap::~StageMap()
{
}

//初期化
void StageMap::Initialize()
{
    SaveManager* pSaveManager = Instantiate<SaveManager>(this);
    pSaveManager->Load("SaveFile/SaveTest.json");
}

//更新
void StageMap::Update()
{
}

//描画
void StageMap::Draw()
{
}

//開放
void StageMap::Release()
{
}