#include "MainGameScene.h"
#include "Player.h"
#include "StageMap.h"

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//�f�X�g���N�^
MainGameScene::~MainGameScene()
{
}

//������
void MainGameScene::Initialize()
{
	Player* pPlayer = Instantiate<Player>(this);
	//StageMap* pStageMap = Instantiate<StageMap>(this);
}

//�X�V
void MainGameScene::Update()
{
}

//�`��
void MainGameScene::Draw()
{
}

//�J��
void MainGameScene::Release()
{
}