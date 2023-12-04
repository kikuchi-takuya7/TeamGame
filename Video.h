#pragma once

#include <Windows.h>
#include <dshow.h>
#include "Engine/GameObject.h"

class Video : public GameObject {
private:
    // DirectX�f�o�C�X�̍쐬
    ID3D11Device* pD3DDevice;
    ID3D11DeviceContext* pImmediateContext;
    // �X���b�v�`�F�[���̍쐬
    IDXGISwapChain* pSwapChain;

public:
    void Initialize();
   

    // ���[�U�[����`�����R���X�g���N�^
    Video(GameObject* parent);
  // ����̃R���X�g���N�^
    Video();
   ~Video();
   void  ProcessVideoFrame(IMFSample* pSample);
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