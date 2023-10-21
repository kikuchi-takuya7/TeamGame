#pragma once

#include <windows.h>
#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

class Video {
public:
    Video();
    ~Video();

    bool Initialize(HWND hwnd);
    void PlayVideo(const wchar_t* videoFileName);
    void StopVideo();
    void Release();

private:
    IGraphBuilder* pGraphBuilder;
    IMediaControl* pMediaControl;
    IMediaEvent* pMediaEvent;
    HWND hwnd;
};