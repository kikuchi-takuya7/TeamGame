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
   

    // ���[�U�[����`�����R���X�g���N�^
    Video(GameObject* parent);
  // ����̃R���X�g���N�^
    Video();
   ~Video();
//
//    // �V�����֐����`
//    bool InitializeVideo();
//    bool LoadFile(const wchar_t* filePath);
//    void Play();
//    void WaitForCompletion();
//
//private:
//    void ReleaseInterfaces();
};