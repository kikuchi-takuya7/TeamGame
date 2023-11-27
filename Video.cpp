#include "Video.h"
#include <iostream>






// ユーザーが定義したコンストラクタ
Video::Video(GameObject* parent) :
    pGraph(nullptr), pControl(nullptr), pEvent(nullptr) {}

// 既定のコンストラクターの実装
Video::Video() :
    pGraph(nullptr), pControl(nullptr), pEvent(nullptr) {}

   
   

    Video::~Video() {
        ReleaseInterfaces();
}


    bool Video::InitializeVideo()
    {
        HRESULT hr = CoInitialize(NULL);
        //エラー表示
        if (FAILED(hr)) {
            std::cout << "ERROR - Could not initialize COM library" << std::endl;
            return false;
        }

        hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
        //エラー表示
        if (FAILED(hr)) {
            std::cout << "ERROR - Could not create the Filter Graph Manager." << std::endl;
            return false;
        }

        hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
        //エラー表示
        if (FAILED(hr)) {
            std::cout << "ERROR - Could not obtain IMediaControl interface." << std::endl;
            return false;
        }

        hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
        //エラー表示
        if (FAILED(hr)) {
            std::cout << "ERROR - Could not obtain IMediaEvent interface." << std::endl;
            return false;
        }

        return true;
    }

    bool Video::LoadFile(const wchar_t* filePath)
    {
        HRESULT hr = pGraph->RenderFile(filePath, NULL);
        return SUCCEEDED(hr);
    }

    void Video::Play() {
        pControl->Run();
    }

    void Video::WaitForCompletion() {
        long evCode;
        pEvent->WaitForCompletion(INFINITE, &evCode);
    }

    void Video::ReleaseInterfaces() {
        if (pControl) {
            pControl->Release();
            pControl = nullptr;
        }

        if (pEvent) {
            pEvent->Release();
            pEvent = nullptr;
        }

        if (pGraph) {
            pGraph->Release();
            pGraph = nullptr;
        }

        CoUninitialize();
    }

