#include "StoreScene.h"
#include "Engine/Image.h"

StoreScene::StoreScene(GameObject* parent)
	:GameObject(parent, "StoreScene"), hPict_(-1)
{
}

StoreScene::~StoreScene()
{
}

void StoreScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Store.png");
	assert(hPict_ >= 0);
}

void StoreScene::Update()
{
}

void StoreScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void StoreScene::Release()
{
}
