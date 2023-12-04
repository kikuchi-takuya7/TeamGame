#include "Video.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")






Video::Video(GameObject* parent)
{
}

Video::Video()
{
}

Video::~Video()
{
}

void Video::ProcessVideoFrame(IMFSample* pSample)
{
    // ビデオフレームを処理し、テクスチャに描画するためのコードをここに追加（例: バッファの取得と処理）
    IMFMediaBuffer* pBuffer = nullptr;
    HRESULT hr = pSample->GetBufferByIndex(0, &pBuffer);
    if (SUCCEEDED(hr)) {
        // バッファを処理する（例: テクスチャにコピーするなど）
        // ...

        pBuffer->Release();
    }
}

void Video::Initialize()
{
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        // 初期化に失敗
        // エラー処理 
        
    }
    IMFSourceReader* pReader = nullptr;

    hr = MFCreateSourceReaderFromURL(L"TouhokuDenshi_splash.avi", nullptr, &pReader);
    if (FAILED(hr)) {
        // Source Reader の作成に失敗
        // エラー処理
        MFShutdown();
    }

    IMFMediaType* pMediaType = nullptr;

    hr = MFCreateMediaType(&pMediaType);
    if (SUCCEEDED(hr)) {
        hr = pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    }

    hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pMediaType);

    if (FAILED(hr)) {
        // 現在のメディアタイプの設定に失敗
        // エラー処理
        pReader->Release();
        pMediaType->Release();
        MFShutdown();
        return;
    }
    while (true) {
        DWORD dwFlags = 0;
        LONGLONG llTimeStamp = 0;
        IMFSample* pSample = nullptr;

        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, nullptr, &dwFlags, &llTimeStamp, &pSample);
        if (FAILED(hr) || (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM)) {
            // サンプルの読み取りに失敗または終了
            // エラー処理またはストリームの終了処理
            break;
        }
        // ビデオフレームを処理し、テクスチャに描画する（例: ProcessVideoFrame関数を呼び出す）
        ProcessVideoFrame(pSample);
        // サンプルの解放
        pSample->Release();
    }

    pReader->Release();
    pMediaType->Release();
    MFShutdown();

}


   









