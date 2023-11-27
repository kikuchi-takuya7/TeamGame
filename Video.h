#pragma once

#include <Windows.h>
#include <dshow.h>
#include "Engine/GameObject.h"

class Video : public GameObject {
private:
    IGraphBuilder* pGraph;
    IMediaControl* pControl;
    IMediaEvent* pEvent;

public:
    void Initialize();
   

    // ユーザーが定義したコンストラクタ
    Video(GameObject* parent);
  // 既定のコンストラクタ
    Video();
   ~Video();
//
//    // 新しい関数を定義
//    bool InitializeVideo();
//    bool LoadFile(const wchar_t* filePath);
//    void Play();
//    void WaitForCompletion();
//
//private:
//    void ReleaseInterfaces();
};