#include "DevelopSelectScene.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
DevelopSelectScene::DevelopSelectScene(GameObject* parent)
	: GameObject(parent, "DevelopSelectScene"),scene_(NONE)
{
}

//������
void DevelopSelectScene::Initialize()
{
}

//�X�V
void DevelopSelectScene::Update()
{
	switch (scene_)
	{
	case NONE:
		break;

	case SPLASH: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
		break;
	}

	case TITLE: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
		break;
	}

	case SELECT: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
		break;
	}

	case MAIN: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAIN);
		break;
	}

	case GAMECLEAR: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
		break;
	}

	case GAMEOVER: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		break;
	}

	case MAPEDITOR: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAPEDITOR);
		break;
	}

	default:
		break;
	}
}

//�`��
void DevelopSelectScene::Draw()
{
}

//�J��
void DevelopSelectScene::Release()
{
}

void DevelopSelectScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Let's Go SelectScene"))
	{
		if (ImGui::Button("Splash"))
			scene_ = SPLASH;

		if (ImGui::Button("Title"))
			scene_ = TITLE;

		if (ImGui::Button("Select"))
			scene_ = SELECT;

		if (ImGui::Button("MainGame"))
			scene_ = MAIN;

		if (ImGui::Button("GameClear"))
			scene_ = GAMECLEAR;

		if (ImGui::Button("GameOver"))
			scene_ = GAMEOVER;

		if (ImGui::Button("MapEditor"))
			scene_ = MAPEDITOR;

	}
	ImGui::End();
}
