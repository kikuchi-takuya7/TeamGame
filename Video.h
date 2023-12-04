#pragma once

#include <Windows.h>
#include <dshow.h>
#include "Engine/GameObject.h"

class Video : public GameObject {
private:
    // DirectXデバイスの作成
    ID3D11Device* pD3DDevice;
    ID3D11DeviceContext* pImmediateContext;
    // スワップチェーンの作成
    IDXGISwapChain* pSwapChain;

public:
    void Initialize();
   

    // ユーザーが定義したコンストラクタ
    Video(GameObject* parent);
  // 既定のコンストラクタ
    Video();
   ~Video();
   void  ProcessVideoFrame(IMFSample* pSample);
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