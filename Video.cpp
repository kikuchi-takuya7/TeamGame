#include "Video.h"





Video::Video(GameObject* parent) : pGraphBuilder(nullptr), pMediaControl(nullptr), pMediaEvent(nullptr), hwnd(nullptr), GameObject(parent, "Video") {
    CoInitialize(nullptr);
}

Video::~Video() {
    Release();
    CoUninitialize();
}

void Video::Initialize() {
   

   

    // “®‰æ‚ðÄ¶
    PlayVideo(L"TouhokuDenshi_splash.avi");

   

    HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraphBuilder);
    if (FAILED(hr)) {
       // return false;
    }

    pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
    pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&pMediaEvent);

    //return true;
}

//XV
void Video::Update()
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    pSceneManager->ChangeScene(SCENE_ID_TITLE);
}

//•`‰æ
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
