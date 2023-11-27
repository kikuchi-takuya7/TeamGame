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

void Video::Initialize()
{
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        // �������Ɏ��s
        // �G���[����
    }
    IMFSourceReader* pReader = nullptr;

    hr = MFCreateSourceReaderFromURL(L"TouhokuDenshi_splash.avi", nullptr, &pReader);
    if (FAILED(hr)) {
        // Source Reader �̍쐬�Ɏ��s
        // �G���[����
    }

    IMFMediaType* pMediaType = nullptr;

    hr = MFCreateMediaType(&pMediaType);
    if (SUCCEEDED(hr)) {
        hr = pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    }

    hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pMediaType);

    while (true) {
        DWORD dwFlags = 0;
        LONGLONG llTimeStamp = 0;
        IMFSample* pSample = nullptr;

        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, nullptr, &dwFlags, &llTimeStamp, &pSample);
        if (FAILED(hr)) {
            // �T���v���̓ǂݎ��Ɏ��s�܂��͏I��
            break;
        }

        if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
            // �t�@�C���̏I�[�ɓ��B
            break;
        }

        // �e�N�X�`���Ƀt���[����`�悷�鏈��
    }

    pReader->Release();
    pMediaType->Release();
    MFShutdown();

}


   









//#include "Video.h"
//#include <iostream>
//
//// ���[�U�[����`�����R���X�g���N�^
//Video::Video(GameObject* parent) :
//    pGraph(nullptr), pControl(nullptr), pEvent(nullptr) {}
//
//// ����̃R���X�g���N�^�[�̎���
//Video::Video() :
//    pGraph(nullptr), pControl(nullptr), pEvent(nullptr) {}
//
//    Video::~Video() {
//        ReleaseInterfaces();
//}
//
//
//    bool Video::InitializeVideo()
//    {
//        HRESULT hr = CoInitialize(NULL);
//        //�G���[�\��
//        if (FAILED(hr)) {
//            std::cout << "ERROR - Could not initialize COM library" << std::endl;
//            return false;
//        }
//
//        hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
//        //�G���[�\��
//        if (FAILED(hr)) {
//            std::cout << "ERROR - Could not create the Filter Graph Manager." << std::endl;
//            return false;
//        }
//
//        hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
//        //�G���[�\��
//        if (FAILED(hr)) {
//            std::cout << "ERROR - Could not obtain IMediaControl interface." << std::endl;
//            return false;
//        }
//
//        hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
//        //�G���[�\��
//        if (FAILED(hr)) {
//            std::cout << "ERROR - Could not obtain IMediaEvent interface." << std::endl;
//            return false;
//        }
//
//        return true;
//    }
//
//    bool Video::LoadFile(const wchar_t* filePath)
//    {
//        HRESULT hr = pGraph->RenderFile(filePath, NULL);
//        return SUCCEEDED(hr);
//    }
//
//    void Video::Play() {
//        pControl->Run();
//    }
//
//    void Video::WaitForCompletion() {
//        long evCode;
//        pEvent->WaitForCompletion(INFINITE, &evCode);
//    }
//
//    void Video::ReleaseInterfaces() {
//        if (pControl) {
//            pControl->Release();
//            pControl = nullptr;
//        }
//
//        if (pEvent) {
//            pEvent->Release();
//            pEvent = nullptr;
//        }
//
//        if (pGraph) {
//            pGraph->Release();
//            pGraph = nullptr;
//        }
//
//        CoUninitialize();
//    }

