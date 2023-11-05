#include "Video.h"




Video::Video(HWND hwnd) : hwnd(hwnd), pGraphBuilder(nullptr), pMediaControl(nullptr) {
    CoInitialize(NULL);
}

bool Video::Initialize(const char* aviFilePath) {
    // �O���t�r���_�[�ƃ��f�B�A�R���g���[�����쐬
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraphBuilder);
    pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);

    // AVI�t�@�C�����J���ăt�B���^�O���t�ɒǉ�
    WCHAR wFileName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, aviFilePath, -1, wFileName, MAX_PATH);
    pGraphBuilder->RenderFile(wFileName, NULL);

    


    return true;
}

void Video::Play() {
    pMediaControl->Run();
}

void Video::Update() {
    // �r�f�I�Đ��̍X�V����
    if (pMediaControl) {
        OAFilterState state;
        pMediaControl->GetState(0, &state);

        if (state == State_Stopped) {
            // �r�f�I�Đ����I��������Đ����~����i�C�ӂ̏�����ǉ��ł��܂��j
            pMediaControl->Stop();
        }
    }
}

