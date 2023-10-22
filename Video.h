#pragma once

#include <windows.h>
#include <dshow.h>
#include "Engine/SceneManager.h"
#pragma comment(lib, "strmiids.lib")

class Video : public GameObject {
public:
    //�R���X�g���N�^
//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
    Video(GameObject* parent);
  
    ~Video();

    void Initialize(HWND hwnd);
    void Update();
    void PlayVideo(const wchar_t* videoFileName);
    void Draw();
    void StopVideo();
    void Release();

private:
    IGraphBuilder* pGraphBuilder;
    IMediaControl* pMediaControl;
    IMediaEvent* pMediaEvent;
    HWND hwnd;
};