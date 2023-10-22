#include "Video.h"





Video::Video(GameObject* parent) : pGraphBuilder(nullptr), pMediaControl(nullptr), pMediaEvent(nullptr), hwnd(nullptr), GameObject(parent, "Video") {
    CoInitialize(nullptr);
}

Video::~Video() {
    Release();
    CoUninitialize();
}

void Video::Initialize(HWND hwnd) {
    this->hwnd = hwnd;

   

    // 動画を再生
    PlayVideo(L"TouhokuDenshi_splash.avi");

   
    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraphBuilder);
    if (FAILED(hr)) {
        return;
    }

    pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
    pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&pMediaEvent);
}


//更新
void Video::Update()
{
    // 動画の再生状態を確認
    if (pMediaEvent) {
        long eventCode;
        LONG_PTR param1, param2;
        while (SUCCEEDED(pMediaEvent->GetEvent(&eventCode, &param1, &param2, 0))) {
            if (eventCode == EC_COMPLETE) {
                // 動画が終了した場合、シーンを切り替え
                SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                pSceneManager->ChangeScene(SCENE_ID_TITLE);
            }
            pMediaEvent->FreeEventParams(eventCode, param1, param2);
        }
    }
}

//描画
void Video::Draw()
{

    
}


void Video::PlayVideo(const wchar_t* videoFileName) {
    if (pGraphBuilder && pMediaControl) {
        pGraphBuilder->RenderFile(videoFileName, NULL);
        pMediaControl->Run();
    }
}

void Video::StopVideo() {
    if (pMediaControl) {
        pMediaControl->Stop();
    }
}

void Video::Release() {
    if (pMediaControl) {
        pMediaControl->StopWhenReady();
        pMediaControl->Release();
        pMediaControl = nullptr;
    }

    if (pMediaEvent) {
        pMediaEvent->Release();
        pMediaEvent = nullptr;
    }

    if (pGraphBuilder) {
        pGraphBuilder->Release();
        pGraphBuilder = nullptr;
    }

}
