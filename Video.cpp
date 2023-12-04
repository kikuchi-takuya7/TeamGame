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
    // �r�f�I�t���[�����������A�e�N�X�`���ɕ`�悷�邽�߂̃R�[�h�������ɒǉ��i��: �o�b�t�@�̎擾�Ə����j
    IMFMediaBuffer* pBuffer = nullptr;
    HRESULT hr = pSample->GetBufferByIndex(0, &pBuffer);
    if (SUCCEEDED(hr)) {
        // �o�b�t�@����������i��: �e�N�X�`���ɃR�s�[����Ȃǁj
        // ...

        pBuffer->Release();
    }
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
        MFShutdown();
    }

    IMFMediaType* pMediaType = nullptr;

    hr = MFCreateMediaType(&pMediaType);
    if (SUCCEEDED(hr)) {
        hr = pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    }

    hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pMediaType);

    if (FAILED(hr)) {
        // ���݂̃��f�B�A�^�C�v�̐ݒ�Ɏ��s
        // �G���[����
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
            // �T���v���̓ǂݎ��Ɏ��s�܂��͏I��
            // �G���[�����܂��̓X�g���[���̏I������
            break;
        }
        // �r�f�I�t���[�����������A�e�N�X�`���ɕ`�悷��i��: ProcessVideoFrame�֐����Ăяo���j
        ProcessVideoFrame(pSample);
        // �T���v���̉��
        pSample->Release();
    }

    pReader->Release();
    pMediaType->Release();
    MFShutdown();

}


   









