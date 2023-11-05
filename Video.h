#pragma once

#include <windows.h>
#include <dshow.h>
#include <d3d9.h>
#include <Vmr9.h>
#include "Engine/SceneManager.h"
#pragma comment(lib, "strmiids.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "strmiids.lib")

class Video : public GameObject {
public:
    Video(HWND hwnd);
    bool Initialize(const char* aviFilePath);
    void Play();
    void Update();

   

private:
    IGraphBuilder* pGraphBuilder;
    IMediaControl* pMediaControl;
    IMediaEvent* pMediaEvent;
    HWND hwnd;
};