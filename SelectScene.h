#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Button.h"

class SelectScene : public GameObject
{
private:
	int hPict_;    //画像番号
	int hStore_;   //storeの画像番号
	Transform volume_Transform_;
	int hVolume_;   //volumeの画像番号
	bool Dlog_;
	int buttonId;  //ボタンのID取得
	int hSound_;   //サウンド番号
	float currentVolume;

	Button* play_;
	Button* store_;
	Button* exit_;
	Button* exitz_;
	Button* playz_;
	Button* storez_;
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SelectScene(GameObject* parent);
	~SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	bool GetDlog() const;
	void SetDlog(bool log);
	BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};
