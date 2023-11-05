#include "Video.h"




Video::Video(HWND hwnd) : hwnd(hwnd), pGraphBuilder(nullptr), pMediaControl(nullptr) {
    CoInitialize(NULL);
}

bool Video::Initialize(const char* aviFilePath) {
    // グラフビルダーとメディアコントロールを作成
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraphBuilder);
    pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);

    // AVIファイルを開いてフィルタグラフに追加
    WCHAR wFileName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, aviFilePath, -1, wFileName, MAX_PATH);
    pGraphBuilder->RenderFile(wFileName, NULL);

    


    return true;
}

void Video::Play() {
    pMediaControl->Run();
}

void Video::Update() {
    // ビデオ再生の更新処理
    if (pMediaControl) {
        OAFilterState state;
        pMediaControl->GetState(0, &state);

        if (state == State_Stopped) {
            // ビデオ再生が終了したら再生を停止する（任意の処理を追加できます）
            pMediaControl->Stop();
        }
    }
}

