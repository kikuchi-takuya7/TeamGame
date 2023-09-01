#pragma once
#include "Engine/GameObject.h"



//◆◆◆を管理するクラス
class SaveManager : public GameObject
{

public:
    //コンストラクタ
    SaveManager(GameObject* parent);

    //デストラクタ
    ~SaveManager();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

